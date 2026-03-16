// Source: https://leetcode.com/problems/statistics-from-a-large-sample/   |   Difficulty: Medium
//
// Problem Description:
// You are given a large sample of integers in the range [0, 255]. Since the sample is so large, it is represented by an array count where count[k] is the number of times that k appears in the sample.
//
// Calculate the following statistics:
//
//
// 	minimum: The minimum element in the sample.
// 	maximum: The maximum element in the sample.
// 	mean: The average of the sample, calculated as the total sum of all elements divided by the total number of elements.
// 	median:
// 	
// 		If the sample has an odd number of elements, then the median is the middle element once the sample is sorted.
// 		If the sample has an even number of elements, then the median is the average of the two middle elements once the sample is sorted.
// 	
// 	
// 	mode: The number that appears the most in the sample. It is guaranteed to be unique.
//
//
// Return the statistics of the sample as an array of floating-point numbers [minimum, maximum, mean, median, mode]. Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: count = [0,1,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
// Output: [1.00000,3.00000,2.37500,2.50000,3.00000]
// Explanation: The sample represented by count is [1,2,2,2,3,3,3,3].
// The minimum and maximum are 1 and 3 respectively.
// The mean is (1+2+2+2+3+3+3+3) / 8 = 19 / 8 = 2.375.
// Since the size of the sample is even, the median is the average of the two middle elements 2 and 3, which is 2.5.
// The mode is 3 as it appears the most in the sample.
//
// Constraints:
// count.length == 256
// 	0 <= count[i] <= 109
// 	1 <= sum(count) <= 109
// 	The mode of the sample that count represents is unique.
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} count
 * @return {number[]}
 */
var sampleStats = function(count) {
  let minimum = -1;
  let maximum = -1;
  let mean = 0;
  let median = 0;
  let mode = -1;
  
  let totalCount = 0;
  let totalSum = 0;
  
  for (let i = 0; i < count.length; i++) {
    if (count[i] > 0) {
      if (minimum === -1) {
        minimum = i;
      }
      maximum = i;
      
      totalCount += count[i];
      totalSum += count[i] * i;
      
      if (mode === -1 || count[i] > count[mode]) {
        mode = i;
      }
    }
  }
  
  mean = totalSum / totalCount;

  const mid1 = Math.floor((totalCount - 1) / 2);
  const mid2 = Math.floor(totalCount / 2);
  
  let cumulativeCount = 0;
  
  for (let i = 0; i < count.length; i++) {
    cumulativeCount += count[i];
    
    if (cumulativeCount > mid1 && median === 0) {
      median += i;
    }
    if (cumulativeCount > mid2) {
      median += i;
      break;
    }
  }
  
  median /= (mid1 === mid2) ? 1 : 2;

  return [minimum, maximum, mean, median, mode];
};
