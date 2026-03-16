// Source: https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/   |   Difficulty: Hard
//
// Problem Description:
// You have a keyboard layout as shown above in the X-Y plane, where each English uppercase letter is located at some coordinate.
//
//
// 	For example, the letter 'A' is located at coordinate (0, 0), the letter 'B' is located at coordinate (0, 1), the letter 'P' is located at coordinate (2, 3) and the letter 'Z' is located at coordinate (4, 1).
//
//
// Given the string word, return the minimum total distance to type such string using only two fingers.
//
// The distance between coordinates (x1, y1) and (x2, y2) is |x1 - x2| + |y1 - y2|.
//
// Note that the initial positions of your two fingers are considered free so do not count towards your total distance, also your two fingers do not have to start at the first letter or the first two letters.
//
// Example:
// Input: word = "CAKE"
// Output: 3
// Explanation: Using two fingers, one optimal way to type "CAKE" is: 
// Finger 1 on letter 'C' -> cost = 0 
// Finger 1 on letter 'A' -> cost = Distance from letter 'C' to letter 'A' = 2 
// Finger 2 on letter 'K' -> cost = 0 
// Finger 2 on letter 'E' -> cost = Distance from letter 'K' to letter 'E' = 1 
// Total distance = 3
//
// Constraints:
// 2 <= word.length <= 300
// 	word consists of uppercase English letters.
//

class Solution {
    public int minimumDistance(String word) {
        int n = word.length();
        int[][] dp = new int[n + 1][26];
        for (int i = 0; i < n; i++) {
            char c = word.charAt(i);
            int idx = c - 'A';
            for (int j = 0; j < 26; j++) {
                dp[i + 1][j] = Integer.MAX_VALUE;
            }
            for (int j = 0; j < 26; j++) {
                // move finger 1
                dp[i + 1][j] = Math.min(dp[i + 1][j], dp[i][j] + distance(word.charAt(i - 1), c));
                // move finger 2
                dp[i + 1][idx] = Math.min(dp[i + 1][idx], dp[i][j]);
            }
        }
        int result = Integer.MAX_VALUE;
        for (int j = 0; j < 26; j++) {
            result = Math.min(result, dp[n][j]);
        }
        return result;                  
    }
}
