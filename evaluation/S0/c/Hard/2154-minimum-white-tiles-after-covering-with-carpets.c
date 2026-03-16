// Source: https://leetcode.com/problems/minimum-white-tiles-after-covering-with-carpets/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed binary string floor, which represents the colors of tiles on a floor:
//
//
// 	floor[i] = '0' denotes that the ith tile of the floor is colored black.
// 	On the other hand, floor[i] = '1' denotes that the ith tile of the floor is colored white.
//
//
// You are also given numCarpets and carpetLen. You have numCarpets black carpets, each of length carpetLen tiles. Cover the tiles with the given carpets such that the number of white tiles still visible is minimum. Carpets may overlap one another.
//
// Return the minimum number of white tiles still visible.
//
// Example:
// Input: floor = "10110101", numCarpets = 2, carpetLen = 2
// Output: 2
// Explanation: 
// The figure above shows one way of covering the tiles with the carpets such that only 2 white tiles are visible.
// No other way of covering the tiles with the carpets can leave less than 2 white tiles visible.
//
// Constraints:
// 1 <= carpetLen <= floor.length <= 1000
// 	floor[i] is either '0' or '1'.
// 	1 <= numCarpets <= 1000
//

int minimumWhiteTiles(char* floor, int numCarpets, int carpetLen) {
    int n = strlen(floor);
    int *dp = (int*)malloc((n + 1) * sizeof(int));
    if (!dp) return 0;
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i - 1] + (floor[i - 1] == '1' ? 1 : 0);
    }
    for (int c = 0; c < numCarpets; ++c) {
        for (int i = n; i >= 1; --i) {
            int start = i - carpetLen >= 0 ? i - carpetLen : 0;
            if (dp[start] < dp[i]) {
                dp[i] = dp[start];
            }
        }
    }
    int result = dp[n];
    free(dp);
    return result;      
}
