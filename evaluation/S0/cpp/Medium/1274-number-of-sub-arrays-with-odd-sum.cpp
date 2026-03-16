// Source: https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers arr, return the number of subarrays with an odd sum.
//
// Since the answer can be very large, return it modulo 109 + 7.
//
// Example:
// Input: arr = [1,3,5]
// Output: 4
// Explanation: All subarrays are [[1],[1,3],[1,3,5],[3],[3,5],[5]]
// All sub-arrays sum are [1,4,9,3,8,5].
// Odd sums are [1,9,3,5] so the answer is 4.
//
// Constraints:
// 1 <= arr.length <= 105
// 	1 <= arr[i] <= 100
//

class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        const int MOD = 1e9 + 7;
        long long oddCount = 0;
        long long evenCount = 1; // empty subarray
        long long currentSum = 0;
        long long result = 0;

        for (int num : arr) {
            currentSum += num;
            if (currentSum % 2 == 0) {
                result = (result + oddCount) % MOD;
                evenCount++;
            } else {
                result = (result + evenCount) % MOD;
                oddCount++;
            }
        }

        return static_cast<int>(result);            
    }
};
