import React, { useEffect, useState } from 'react';
import { Scatter } from 'react-chartjs-2';
import 'chart.js/auto';
import { ChartData, ChartOptions } from 'chart.js';
import { computeWindowedAverage } from './computeWindowedAverage';

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

  const [focusStatus, setFocusStatus] = useState<string>('Currently Distracted');

  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await fetch('/data.txt');
        const text: string = await response.text();
        const cleanedText = text.trim();
        const cleanedTextWithoutBrackets = cleanedText.replace(/^\[|\]$/g, '');
        const values = cleanedTextWithoutBrackets.split(',').map(Number);

        const average = values.reduce((sum, value) => sum + value, 0) / values.length;
        setFocusStatus(average > 0.5 ? 'Currently Focused' : 'Currently Distracted');

        // Group data into five-second intervals and calculate the average for each interval
        const groupedValues: number[] = [];
        for (let i = 0; i < values.length; i += 5) {
          const group = values.slice(i, i + 5);
          const groupAverage = group.reduce((sum, value) => sum + value, 0) / group.length;
          groupedValues.push(groupAverage);
        }

        const focusedData: DataPoint[] = groupedValues.map((value, index) => ({ x: index * 5, y: value === 1 ? 1 : NaN }));
        const distractedData: DataPoint[] = groupedValues.map((value, index) => ({ x: index * 5, y: value === 0 ? 0 : NaN }));
        let rawIndicationData: DataPoint[] = groupedValues.map((value, index) => ({ x: index * 5, y: value === 1 ? 1 : 0 }));
        const indicationData = computeWindowedAverage(rawIndicationData, rawIndicationData.length / 4);

        console.log(focusedData);
        console.log(distractedData);

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
              borderWidth: 2,
              pointStyle: false,
            },
          ],
        });
      } catch (error) {
        console.error('Error fetching data:', error);
      }
    };

    fetchData();
  }, []);

  const options: ChartOptions<'scatter'> = {
    scales: {
      x: {
        type: 'linear',
        position: 'bottom',
        title: {
          display: true,
          text: 'Time (seconds)',
        },
      },
      y: {
        title: {
          display: true,
          text: 'Focus Level', // Optional y-axis title
        },
      },
    },
  };

  return (
    <div className="row justify-content-center p-3">
      <div className="col-12 text-center mb-3">
        <p style={{ color: focusStatus === 'Currently Focused' ? '#0077cc' : '#ff7f00' }}>
          {focusStatus}
        </p>
      </div>
      <div className="col-12">
        <Scatter data={chartData} options={options} />
      </div>
    </div>
  );
};

export default ScatterPlot;
