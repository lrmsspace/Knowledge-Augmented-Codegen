// Source: https://leetcode.com/problems/pizza-with-3n-slices/   |   Difficulty: Hard
//
// Problem Description:
// There is a pizza with 3n slices of varying size, you and your friends will take slices of pizza as follows:
//
//
// 	You will pick any pizza slice.
// 	Your friend Alice will pick the next slice in the anti-clockwise direction of your pick.
// 	Your friend Bob will pick the next slice in the clockwise direction of your pick.
// 	Repeat until there are no more slices of pizzas.
//
//
// Given an integer array slices that represent the sizes of the pizza slices in a clockwise direction, return the maximum possible sum of slice sizes that you can pick.
//
// Example:
// Input: slices = [1,2,3,4,5,6]
// Output: 10
// Explanation: Pick pizza slice of size 4, Alice and Bob will pick slices with size 3 and 5 respectively. Then Pick slices with size 6, finally Alice and Bob will pick slice of size 2 and 1 respectively. Total = 4 + 6.
//
// Constraints:
// 3 * n == slices.length
// 	1 <= slices.length <= 500
// 	1 <= slices[i] <= 1000
//

class Solution {
public:
    int maxSizeSlices(vector<int>& slices) {
        int n = slices.size();
        int take = n / 3;
        
        // Helper function to calculate max sum for linear slices
        auto maxSumLinear = [&](int start, int end) {
            vector<vector<int>> dp(end - start + 1, vector<int>(take + 1, 0));
            
            for (int i = start; i < end; i++) {
                for (int j = 1; j <= take; j++) {
                    dp[i - start + 1][j] = max(dp[i - start][j], dp[i - start - 1][j - 1] + slices[i]);
                }
            }
            
            return dp[end - start][take];
        };
        
        // Case 1: Exclude first slice
        int case1 = maxSumLinear(1, n);
        // Case 2: Exclude last slice
        int case2 = maxSumLinear(0, n - 1);
        
        return max(case1, case2);           
    }
};
