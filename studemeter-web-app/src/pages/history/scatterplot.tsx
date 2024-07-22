import React, { useEffect, useState } from 'react';
import { Scatter } from 'react-chartjs-2';
import 'chart.js/auto';
import { ChartData, ChartOptions } from 'chart.js';
import { computeWindowedAverage } from './computeWindowedAverage';
import { Span } from 'next/dist/trace';

type DataPoint = {
  x: number;
  y: number;
};

const ScatterPlot: React.FC = () => {
  const [chartData, setChartData] = useState<ChartData<'scatter'>>({
    datasets: [
      {
        label: 'Focused',
        data: [] as DataPoint[],
        backgroundColor: '#0077cc',
      },
      {
        label: 'Distracted',
        data: [] as DataPoint[],
        backgroundColor: '#ff7f00',
      },
      {
        label: 'Indication',
        data: [] as DataPoint[],
        backgroundColor: '#808080',
        showLine: true,
        fill: false,
        borderWidth: 2,
        pointStyle: false,
      },
    ],
  });

  const [spanStatusAverage, setSpanStatusAverage] = useState(<span>Unknown Status</span>);
  const [spanStatusRecently, setSpanStatusRecently] = useState(<span>Unknown Status</span>);
  const [options, setOptions] = useState<ChartOptions<'scatter'>>();
  const SAMPLES_PER_SECOND = 1 / 12.8; // sample every 12.8ms

  const [refreshCount, setRefreshCount] = useState(0);

  useEffect(() => {
    const interval = setInterval(() => {
      setRefreshCount(prevCount => prevCount + 1);
    }, 300); // Every 300ms redraw

    // Cleanup the interval on component unmount
    return () => clearInterval(interval);
  }, []); // Empty dependency array ensures this runs only once


  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await fetch('/data.txt');
        const text: string = await response.text();
        const cleanedText = text.trim();
        const cleanedTextWithoutBrackets = cleanedText.replace(/^\[|\]$/g, '');
        const values = cleanedTextWithoutBrackets.split(',').map(Number);

        const average = values.reduce((sum, value) => sum + value, 0) / values.length;
        if (average < 0.5) {
          setSpanStatusAverage(<span className='text-primary'>Mostly focused</span>);
        } else if (average > 0.5) {
          setSpanStatusAverage(<span className='text-secondary'>Mostly distracted</span>);
        } else {
          setSpanStatusAverage(<span>Between distracted and focused</span>);
        }
        if (values.at(-1) === 1) {
          setSpanStatusRecently(<span className='text-primary'>Recently focused</span>);
        } else if (values.at(-1) === 0) {
          setSpanStatusRecently(<span className='text-secondary'>Recently distracted</span>);
        }

        const focusedData: DataPoint[] = values.map((value, index) => ({ x: index / SAMPLES_PER_SECOND, y: value === 1 ? 100 : NaN }));
        const distractedData: DataPoint[] = values.map((value, index) => ({ x: index / SAMPLES_PER_SECOND, y: value === 0 ? 0 : NaN }));
        let rawIndicationData: DataPoint[] = values.map((value, index) => ({ x: index / SAMPLES_PER_SECOND, y: value === 1 ? 100 : value === 0 ? 0 : NaN }));
        const indicationData = computeWindowedAverage(rawIndicationData, Math.max(1, Math.ceil(rawIndicationData.length / 2)));

        setChartData({
          datasets: [
            {
              label: 'Focused',
              data: focusedData.filter(point => !isNaN(point.y)),
              backgroundColor: '#0077cc',
            },
            {
              label: 'Distracted',
              data: distractedData.filter(point => !isNaN(point.y)),
              backgroundColor: '#ff7f00',
            },
            {
              label: 'Indication',
              data: indicationData.filter(point => !isNaN(point.y)),
              backgroundColor: '#808080',
              showLine: true,
              fill: false,
              borderWidth: 3,
              pointStyle: false,
            },
          ],
        });

      setOptions({
        scales: {
          x: {
            type: 'linear',
            position: 'bottom',
            min: 0,
            max: values.length / SAMPLES_PER_SECOND,
            title: {
              display: true,
              text: 'Time (seconds)',
            },
          },
          y: {
            title: {
              display: true,
              text: 'Focus Percentage (%)', // Optional y-axis title
            },
          },
        },
      });
      } catch (error) {
        console.error('Error fetching data:', error);
      }
    };

    fetchData();
  }, [refreshCount]);

  return (
    <div className="row justify-content-center p-3">
      <div className="col-12 text-center">
        {spanStatusAverage}
      </div>
      <div className="col-12 text-center mb-3">
        {spanStatusRecently}
      </div>
      <div className="col-12">
        <Scatter data={chartData} options={options} />
      </div>
    </div>
  );
};

export default ScatterPlot;
