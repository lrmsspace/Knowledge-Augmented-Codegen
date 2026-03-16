// Source: https://leetcode.com/problems/binary-trees-with-factors/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of unique integers, arr, where each integer arr[i] is strictly greater than 1.
//
// We make a binary tree using these integers, and each number may be used for any number of times. Each non-leaf node's value should be equal to the product of the values of its children.
//
// Return the number of binary trees we can make. The answer may be too large so return the answer modulo 109 + 7.
//
// Example:
// Input: arr = [2,4]
// Output: 3
// Explanation: We can make these trees: [2], [4], [4, 2, 2]
//
// Constraints:
// 1 <= arr.length <= 1000
// 	2 <= arr[i] <= 109
// 	All the values of arr are unique.
//

class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        const int MOD = 1e9 + 7;
        int n = arr.size();
        sort(arr.begin(), arr.end());
        unordered_map<int, long long> dp;

        for (int i = 0; i < n; ++i) {
            dp[arr[i]] = 1; // Each number can form a single-node tree
            for (int j = 0; j < i; ++j) {
                if (arr[i] % arr[j] == 0) {
                    int right = arr[i] / arr[j];
                    if (dp.find(right) != dp.end()) {
                        dp[arr[i]] = (dp[arr[i]] + dp[arr[j]] * dp[right]) % MOD;
                    }
                }
            }
        }

        long long result = 0;
        for (const auto& entry : dp) {
            result = (result + entry.second) % MOD;
        }

        return static_cast<int>(result);            
    }
};
