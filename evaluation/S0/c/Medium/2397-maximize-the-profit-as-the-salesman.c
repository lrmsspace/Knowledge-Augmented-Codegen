// Source: https://leetcode.com/problems/maximize-the-profit-as-the-salesman/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n representing the number of houses on a number line, numbered from 0 to n - 1.
//
// Additionally, you are given a 2D integer array offers where offers[i] = [starti, endi, goldi], indicating that ith buyer wants to buy all the houses from starti to endi for goldi amount of gold.
//
// As a salesman, your goal is to maximize your earnings by strategically selecting and selling houses to buyers.
//
// Return the maximum amount of gold you can earn.
//
// Note that different buyers can't buy the same house, and some houses may remain unsold.
//
// Example:
// Input: n = 5, offers = [[0,0,1],[0,2,2],[1,3,2]]
// Output: 3
// Explanation: There are 5 houses numbered from 0 to 4 and there are 3 purchase offers.
// We sell houses in the range [0,0] to 1st buyer for 1 gold and houses in the range [1,3] to 3rd buyer for 2 golds.
// It can be proven that 3 is the maximum amount of gold we can achieve.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= offers.length <= 105
// 	offers[i].length == 3
// 	0 <= starti <= endi <= n - 1
// 	1 <= goldi <= 103
//

int maximizeTheProfit(int n, int** offers, int offersSize, int* offersColSize) {
    // Sort offers based on their end index
    qsort(offers, offersSize, sizeof(int*), [](const void* a, const void* b) {
        return (*(int**)a)[1] - (*(int**)b)[1];
    });

    // DP array to store maximum profit up to each house
    int* dp = (int*)calloc(n + 1, sizeof(int));
    int offerIndex = 0;

    for (int i = 0; i < n; i++) {
        // Carry forward the maximum profit from the previous house
        dp[i + 1] = dp[i];

        // Process all offers that end at the current house
        while (offerIndex < offersSize && offers[offerIndex][1] == i) {
            int start = offers[offerIndex][0];
            int gold = offers[offerIndex][2];
            dp[i + 1] = fmax(dp[i + 1], dp[start] + gold);
            offerIndex++;
        }
    }

    int result = dp[n];
    free(dp);
    return result;      
}
