// Source: https://leetcode.com/problems/length-of-longest-fibonacci-subsequence/   |   Difficulty: Medium
//
// Problem Description:
// A sequence x1, x2, ..., xn is Fibonacci-like if:
//
//
// 	n >= 3
// 	xi + xi+1 == xi+2 for all i + 2 <= n
//
//
// Given a strictly increasing array arr of positive integers forming a sequence, return the length of the longest Fibonacci-like subsequence of arr. If one does not exist, return 0.
//
// A subsequence is derived from another sequence arr by deleting any number of elements (including none) from arr, without changing the order of the remaining elements. For example, [3, 5, 8] is a subsequence of [3, 4, 5, 6, 7, 8].
//
// Example:
// Input: arr = [1,2,3,4,5,6,7,8]
// Output: 5
// Explanation: The longest subsequence that is fibonacci-like: [1,2,3,5,8].
//
// Constraints:
// 3 <= arr.length <= 1000
// 	1 <= arr[i] < arr[i + 1] <= 109
//

class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        int n = arr.size();
        unordered_map<int, int> indexMap;
        for (int i = 0; i < n; ++i) {
            indexMap[arr[i]] = i;
        }

        vector<vector<int>> dp(n, vector<int>(n, 2));
        int maxLength = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int expectedPrev = arr[j] - arr[i];
                if (expectedPrev >= arr[i]) {
                    break; // Since arr is strictly increasing
                }
                if (indexMap.find(expectedPrev) != indexMap.end()) {
                    int k = indexMap[expectedPrev];
                    dp[i][j] = dp[k][i] + 1;
                    maxLength = max(maxLength, dp[i][j]);
                }
            }
        }

        return maxLength >= 3 ? maxLength : 0;          
    }
};
