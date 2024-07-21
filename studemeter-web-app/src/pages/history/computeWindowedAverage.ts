// Function to compute the windowed average

type DataPoint = {
    x: number;
    y: number;
  };

export function computeWindowedAverage(data: DataPoint[], windowSize: number): DataPoint[] {
    let windowedData: DataPoint[] = [];

    for (let i = 0; i < data.length; i++) {
        let sum = 0;
        let count = 0;

        for (let j = i; j < i + windowSize && j < data.length; j++) {
            sum += data[j].y;
            count++;
        }
        for (let j = i - windowSize; j < i; j++) {
            if (j < 0) {
                sum += 0.5;
            } else {
                sum += data[j].y;
            }
            count++;
        }

        let average = sum / count;
        windowedData.push({ x: data[i].x, y: average });
    }

    return windowedData;
}