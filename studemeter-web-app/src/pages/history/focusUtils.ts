export function calculateFocusStatus(values: number[]): string {
    if (values.length === 0) return 'Currently Distracted';
  
    // Filter out invalid values
    const filteredValues = values.filter(value => !isNaN(value));
  
    const total = filteredValues.length;
    const focusedCount = filteredValues.filter(value => value === 1).length;
    const averageFocus = focusedCount / total;
  
    console.log(filteredValues); // Log filtered values to debug
  
    return averageFocus >= 0.5 ? 'Currently Focused' : 'Currently Distracted';
  }
  