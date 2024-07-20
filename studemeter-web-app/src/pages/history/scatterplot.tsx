import React, { useEffect, useState } from 'react';
import { Scatter } from 'react-chartjs-2';
import 'chart.js/auto';
import { ChartData, ChartOptions } from 'chart.js';

const ScatterPlot: React.FC = () => {
  const [chartData, setChartData] = useState<ChartData<'scatter'>>({
    datasets: [
      {
        label: 'Focused',
        data: [],
        backgroundColor: '#0077cc',
      },
      {
        label: 'Distracted',
        data: [],
        backgroundColor: '#ff7f00',
      },
      {
        label: 'Indication',
        data: [],
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
        const text = await response.text();
        const values = text.split(',').map(Number);

        // Calculate average value
        const average = values.reduce((sum, value) => sum + value, 0) / values.length;

        // Update focus status based on average
        if (average > 0.5) {
          setFocusStatus('Currently Focused');
        } else {
          setFocusStatus('Currently Distracted');
        }

        // Generate the data points for focused, distracted, and indication
        const focusedData = values.map((value, index) => ({ x: index, y: value === 1 ? 1 : NaN }));
        const distractedData = values.map((value, index) => ({ x: index, y: value === 0 ? 0 : NaN }));
        const indicationData = values.map((value, index) => ({ x: index, y: value === 1 ? (index % 10) / 10 : NaN }));

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
      },
    },
  };

  return (
    <div className="row justify-content-center p-3">
      <div className="text-center mb-3">
        <h2>Karim Mohamed</h2>
        <p>Mostly Focused from 8:00 AM till now</p>
        <p style={{ color: focusStatus === 'Currently Focused' ? '#0077cc' : '#ff7f00' }}>
          {focusStatus}
        </p>
      </div>
      <Scatter data={chartData} options={options} />
    </div>
  );
};

export default ScatterPlot;
