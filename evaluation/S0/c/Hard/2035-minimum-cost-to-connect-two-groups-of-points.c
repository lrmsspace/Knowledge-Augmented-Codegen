// Source: https://leetcode.com/problems/minimum-cost-to-connect-two-groups-of-points/   |   Difficulty: Hard
//
// Problem Description:
// You are given two groups of points where the first group has size1 points, the second group has size2 points, and size1 >= size2.
//
// The cost of the connection between any two points are given in an size1 x size2 matrix where cost[i][j] is the cost of connecting point i of the first group and point j of the second group. The groups are connected if each point in both groups is connected to one or more points in the opposite group. In other words, each point in the first group must be connected to at least one point in the second group, and each point in the second group must be connected to at least one point in the first group.
//
// Return the minimum cost it takes to connect the two groups.
//
// Example:
// Input: cost = [[15, 96], [36, 2]]
// Output: 17
// Explanation: The optimal way of connecting the groups is:
// 1--A
// 2--B
// This results in a total cost of 17.
//
// Constraints:
// size1 == cost.length
// 	size2 == cost[i].length
// 	1 <= size1, size2 <= 12
// 	size1 >= size2
// 	0 <= cost[i][j] <= 100
//

int connectTwoGroups(int** cost, int costSize, int* costColSize) {
    int size1 = costSize;
    int size2 = costColSize[0];
    int fullMask = (1 << size2) - 1;
    int dp[1 << 12];
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    for (int i = 0; i < size1; ++i) {
        int newDp[1 << 12];
        memset(newDp, 0x3f, sizeof(newDp));

        for (int mask = 0; mask <= fullMask; ++mask) {
            for (int j = 0; j < size2; ++j) {
                int newMask = mask | (1 << j);
                if (newDp[newMask] > dp[mask] + cost[i][j]) {
                    newDp[newMask] = dp[mask] + cost[i][j];
                }
            }
        }

        memcpy(dp, newDp, sizeof(dp));
    }

    return dp[fullMask];        
}
