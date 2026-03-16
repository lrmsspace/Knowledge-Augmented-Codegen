// Source: https://leetcode.com/problems/count-number-of-nice-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and an integer k. A continuous subarray is called nice if there are k odd numbers on it.
//
// Return the number of nice sub-arrays.
//
// Example:
// Input: nums = [1,1,2,1,1], k = 3
// Output: 2
// Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].
//
// Constraints:
// 1 <= nums.length <= 50000
// 	1 <= nums[i] <= 10^5
// 	1 <= k <= nums.length
//

class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> oddIndices;
        oddIndices.push_back(-1); // Sentinel for easier calculations

        for (int i = 0; i < n; ++i) {
            if (nums[i] % 2 == 1) {
                oddIndices.push_back(i);
            }
        }
        oddIndices.push_back(n); // Sentinel for easier calculations

        int count = 0;
        int m = oddIndices.size();
        for (int i = 1; i + k < m; ++i) {
            int leftEvenCount = oddIndices[i] - oddIndices[i - 1];
            int rightEvenCount = oddIndices[i + k] - oddIndices[i + k - 1];
            count += leftEvenCount * rightEvenCount;
        }

        return count;           
    }
};
