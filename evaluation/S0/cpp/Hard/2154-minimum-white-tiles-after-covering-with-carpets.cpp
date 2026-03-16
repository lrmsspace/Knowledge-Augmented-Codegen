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

class Solution {
public:
    int minimumWhiteTiles(string floor, int numCarpets, int carpetLen) {
        int n = floor.size();
        vector<vector<int>> dp(n + 1, vector<int>(numCarpets + 1, INT_MAX));
        
        // Base case: 0 tiles means 0 white tiles
        for (int j = 0; j <= numCarpets; j++) {
            dp[0][j] = 0;
        }
        
        for (int i = 1; i <= n; i++) {
            int isWhite = (floor[i - 1] == '1') ? 1 : 0;
            for (int j = 0; j <= numCarpets; j++) {
                // Option 1: Do not use a carpet on the ith tile
                dp[i][j] = dp[i - 1][j] + isWhite;
                
                // Option 2: Use a carpet on the ith tile (if we have carpets left)
                if (j > 0) {
                    int startIdx = max(0, i - carpetLen);
                    dp[i][j] = min(dp[i][j], dp[startIdx][j - 1]);
                }
            }
        }
        
        return dp[n][numCarpets];           
    }
};
