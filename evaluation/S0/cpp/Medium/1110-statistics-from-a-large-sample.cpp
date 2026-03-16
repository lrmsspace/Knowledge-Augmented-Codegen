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

class Solution {
public:
    vector<double> sampleStats(vector<int>& count) {
        double minimum = -1;
        double maximum = -1;
        double mean = 0.0;
        double median = 0.0;
        double mode = 0.0;

        long long totalCount = 0;
        long long totalSum = 0;
        int modeCount = 0;

        for (int i = 0; i < 256; ++i) {
            if (count[i] > 0) {
                if (minimum == -1) {
                    minimum = i;
                }
                maximum = i;

                totalCount += count[i];
                totalSum += (long long)i * count[i];

                if (count[i] > modeCount) {
                    modeCount = count[i];
                    mode = i;
                }
            }
        }

        mean = (double)totalSum / totalCount;

        long long mid1 = (totalCount + 1) / 2;
        long long mid2 = (totalCount + 2) / 2;
        long long cumulativeCount = 0;

        for (int i = 0; i < 256; ++i) {
            cumulativeCount += count[i];

            if (cumulativeCount >= mid1 && median == 0.0) {
                median += i;
            }
            if (cumulativeCount >= mid2) {
                median += i;
                median /= 2.0;
                break;
            }
        }

        return {minimum, maximum, mean, median, mode};          
    }
};
