// Source: https://leetcode.com/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers arr and an integer target.
//
// You have to find two non-overlapping sub-arrays of arr each with a sum equal target. There can be multiple answers so you have to find an answer where the sum of the lengths of the two sub-arrays is minimum.
//
// Return the minimum sum of the lengths of the two required sub-arrays, or return -1 if you cannot find such two sub-arrays.
//
// Example:
// Input: arr = [3,2,2,4,3], target = 3
// Output: 2
// Explanation: Only two sub-arrays have sum = 3 ([3] and [3]). The sum of their lengths is 2.
//
// Constraints:
// 1 <= arr.length <= 105
// 	1 <= arr[i] <= 1000
// 	1 <= target <= 108
//

class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        vector<int> minLen(n, INT_MAX);
        unordered_map<int, int> prefixSumIndex;
        prefixSumIndex[0] = -1;  // Base case for subarray starting at index 0
        int prefixSum = 0;
        int minTotalLength = INT_MAX;
        int minLengthSoFar = INT_MAX;

        for (int i = 0; i < n; ++i) {
            prefixSum += arr[i];

            if (prefixSumIndex.find(prefixSum - target) != prefixSumIndex.end()) {
                int startIdx = prefixSumIndex[prefixSum - target] + 1;
                int currLength = i - startIdx + 1;

                if (startIdx > 0 && minLen[startIdx - 1] != INT_MAX) {
                    minTotalLength = min(minTotalLength, currLength + minLen[startIdx - 1]);
                }

                minLengthSoFar = min(minLengthSoFar, currLength);
            }

            minLen[i] = minLengthSoFar;
            prefixSumIndex[prefixSum] = i;
        }

        return minTotalLength == INT_MAX ? -1 : minTotalLength;         
    }
};
