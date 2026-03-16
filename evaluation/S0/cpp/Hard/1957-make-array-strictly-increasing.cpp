// Source: https://leetcode.com/problems/make-array-strictly-increasing/   |   Difficulty: Hard
//
// Problem Description:
// Given two integer arrays arr1 and arr2, return the minimum number of operations (possibly zero) needed to make arr1 strictly increasing.
//
// In one operation, you can choose two indices 0 <= i < arr1.length and 0 <= j < arr2.length and do the assignment arr1[i] = arr2[j].
//
// If there is no way to make arr1 strictly increasing, return -1.
//
// Example:
// Input: arr1 = [1,5,3,6,7], arr2 = [1,3,2,4]
// Output: 1
// Explanation: Replace 5 with 2, then arr1 = [1, 2, 3, 6, 7].
//
// Constraints:
// 1 <= arr1.length, arr2.length <= 2000
// 	0 <= arr1[i], arr2[i] <= 10^9
//

class Solution {
public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        set<int> s(arr2.begin(), arr2.end());
        vector<int> arr2Unique(s.begin(), s.end());
        int n = arr1.size();
        int m = arr2Unique.size();
        
        // dp[i][j]: min operations to make arr1[0..i] strictly increasing with arr1[i] replaced by arr2[j]
        vector<vector<int>> dp(n, vector<int>(m + 1, INT_MAX));
        
        // Initialize dp for the first element
        dp[0][m] = 0;  // No replacement
        for (int j = 0; j < m; j++) {
            dp[0][j] = 1;  // Replace with arr2[j]
        }
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= m; j++) {
                int prevVal = (j == m) ? arr1[i - 1] : arr2Unique[j];
                
                // Case 1: No replacement at arr1[i]
                if (arr1[i] > prevVal && dp[i - 1][j] != INT_MAX) {
                    dp[i][m] = min(dp[i][m], dp[i - 1][j]);
                }
                
                // Case 2: Replacement at arr1[i]
                for (int k = 0; k < m; k++) {
                    if (arr2Unique[k] > prevVal && dp[i - 1][j] != INT_MAX) {
                        dp[i][k] = min(dp[i][k], dp[i - 1][j] + 1);
                    }
                }
            }
        }
        
        int result = INT_MAX;
        for (int j = 0; j <= m; j++) {
            result = min(result, dp[n - 1][j]);
        }
        
        return (result == INT_MAX) ? -1 : result;           
    }
};
