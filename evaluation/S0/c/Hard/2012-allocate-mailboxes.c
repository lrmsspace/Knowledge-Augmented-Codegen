// Source: https://leetcode.com/problems/allocate-mailboxes/   |   Difficulty: Hard
//
// Problem Description:
// Given the array houses where houses[i] is the location of the ith house along a street and an integer k, allocate k mailboxes in the street.
//
// Return the minimum total distance between each house and its nearest mailbox.
//
// The test cases are generated so that the answer fits in a 32-bit integer.
//
// Example:
// Input: houses = [1,4,8,10,20], k = 3
// Output: 5
// Explanation: Allocate mailboxes in position 3, 9 and 20.
// Minimum total distance from each houses to nearest mailboxes is |3-1| + |4-3| + |9-8| + |10-9| + |20-20| = 5
//
// Constraints:
// 1 <= k <= houses.length <= 100
// 	1 <= houses[i] <= 104
// 	All the integers of houses are unique.
//

int minDistance(int* houses, int housesSize, int k) {
    qsort(houses, housesSize, sizeof(int), cmpInt);

    int dp[housesSize + 1][k + 1];
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;

    int cost[housesSize][housesSize];
    for (int i = 0; i < housesSize; ++i) {
        for (int j = i; j < housesSize; ++j) {
            int mid = (i + j) / 2;
            int c = 0;
            for (int t = i; t <= j; ++t) {
                c += abs(houses[t] - houses[mid]);
            }
            cost[i][j] = c;
        }
    }

    for (int i = 1; i <= housesSize; ++i) {
        for (int j = 1; j <= k && j <= i; ++j) {
            for (int p = 0; p < i; ++p) {
                if (dp[p][j - 1] + cost[p][i - 1] < dp[i][j]) {
                    dp[i][j] = dp[p][j - 1] + cost[p][i - 1];
                }
            }
        }
    }

    return dp[housesSize][k];       
}
