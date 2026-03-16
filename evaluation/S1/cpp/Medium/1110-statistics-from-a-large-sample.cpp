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
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<double> sampleStats(vector<int>& count) {
        double minimum = -1.0;
        double maximum = -1.0;
        double mean = 0.0;
        double median = 0.0;
        double mode = 0.0;

        long long total_count = 0;
        long long total_sum = 0;
        int mode_count = 0;

        for (int i = 0; i < 256; ++i) {
            if (count[i] > 0) {
                if (minimum < 0) {
                    minimum = static_cast<double>(i);
                }
                maximum = static_cast<double>(i);
                total_count += count[i];
                total_sum += static_cast<long long>(i) * count[i];
                if (count[i] > mode_count) {
                    mode_count = count[i];
                    mode = static_cast<double>(i);
                }
            }
        }

        mean = static_cast<double>(total_sum) / static_cast<double>(total_count);

        long long mid1 = (total_count + 1) / 2;
        long long mid2 = (total_count + 2) / 2;
        long long cumulative_count = 0;

        for (int i = 0; i < 256; ++i) {
            cumulative_count += count[i];
            if (cumulative_count >= mid1 && median == 0.0) {
                median += static_cast<double>(i);
            }
            if (cumulative_count >= mid2) {
                median += static_cast<double>(i);
                median /= 2.0;
                break;
            }
        }

        return {minimum, maximum, mean, median, mode};          
    }
};
