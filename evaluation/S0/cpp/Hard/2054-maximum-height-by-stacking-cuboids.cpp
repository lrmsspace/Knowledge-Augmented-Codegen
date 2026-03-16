// Source: https://leetcode.com/problems/maximum-height-by-stacking-cuboids/   |   Difficulty: Hard
//
// Problem Description:
// Given n cuboids where the dimensions of the ith cuboid is cuboids[i] = [widthi, lengthi, heighti] (0-indexed). Choose a subset of cuboids and place them on each other.
//
// You can place cuboid i on cuboid j if widthi <= widthj and lengthi <= lengthj and heighti <= heightj. You can rearrange any cuboid's dimensions by rotating it to put it on another cuboid.
//
// Return the maximum height of the stacked cuboids.
//
// Example:
// Input: cuboids = [[50,45,20],[95,37,53],[45,23,12]]
// Output: 190
// Explanation:
// Cuboid 1 is placed on the bottom with the 53x37 side facing down with height 95.
// Cuboid 0 is placed next with the 45x20 side facing down with height 50.
// Cuboid 2 is placed next with the 23x12 side facing down with height 45.
// The total height is 95 + 50 + 45 = 190.
//
// Constraints:
// n == cuboids.length
// 	1 <= n <= 100
// 	1 <= widthi, lengthi, heighti <= 100
//

class Solution {
public:
    int maxHeight(vector<vector<int>>& cuboids) {
        int n = cuboids.size();
        
        // Sort dimensions of each cuboid
        for (auto& cuboid : cuboids) {
            sort(cuboid.begin(), cuboid.end());
        }
        
        // Sort cuboids based on dimensions
        sort(cuboids.begin(), cuboids.end());
        
        // DP array to store max height ending with each cuboid
        vector<int> dp(n, 0);
        int maxHeight = 0;
        
        for (int i = 0; i < n; i++) {
            dp[i] = cuboids[i][2];  // Height of the current cuboid
            for (int j = 0; j < i; j++) {
                // Check if cuboid j can be placed below cuboid i
                if (cuboids[j][0] <= cuboids[i][0] &&
                    cuboids[j][1] <= cuboids[i][1] &&
                    cuboids[j][2] <= cuboids[i][2]) {
                    dp[i] = max(dp[i], dp[j] + cuboids[i][2]);
                }
            }
            maxHeight = max(maxHeight, dp[i]);
        }
        
        return maxHeight;           
    }
};
