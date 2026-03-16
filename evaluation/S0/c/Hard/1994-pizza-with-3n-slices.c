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

int maxSizeSlices(int* slices, int slicesSize) {
    int n = slicesSize / 3;
    int dp1[ slicesSize + 2];
    int dp2[ slicesSize + 2];
    memset(dp1, 0, sizeof(dp1));
    memset(dp2, 0, sizeof(dp2));

    for (int start = 0; start <= 1; start++) {
        int *dp = (start == 0) ? dp1 : dp2;
        for (int i = start; i < slicesSize - (start == 0 ? 1 : 0); i++) {
            for (int j = 1; j <= n; j++) {
                dp[i + 2] = (dp[i + 2] > dp[i + 1]) ? dp[i + 2] : dp[i + 1];
                int val = dp[i] + slices[i];
                dp[i + 2] = (dp[i + 2] > val) ? dp[i + 2] : val;
            }
        }
    }
    return (dp1[slicesSize + 1] > dp2[slicesSize]) ? dp1[slicesSize + 1] : dp2[slicesSize];     
}
