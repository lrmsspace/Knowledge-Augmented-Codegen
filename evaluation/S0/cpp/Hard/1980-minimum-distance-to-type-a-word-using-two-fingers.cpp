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
public:
    int minimumDistance(string word) {
        int n = word.size();
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(26, vector<int>(26, INT_MAX)));
        dp[0][26][26] = 0;  // both fingers not used yet
        
        auto dist = [](char a, char b) {
            if (a == 26 || b == 26) return 0;
            int x1 = (a - 'A') / 6, y1 = (a - 'A') % 6;
            int x2 = (b - 'A') / 6, y2 = (b - 'A') % 6;
            return abs(x1 - x2) + abs(y1 - y2);
        };
        
        for (int i = 0; i < n; i++) {
            int currChar = word[i] - 'A';
            for (int f1 = 0; f1 <= 26; f1++) {
                for (int f2 = 0; f2 <= 26; f2++) {
                    if (dp[i][f1][f2] == INT_MAX) continue;
                    // Move finger 1
                    dp[i + 1][currChar][f2] = min(dp[i + 1][currChar][f2], dp[i][f1][f2] + dist(f1 + 'A', word[i]));
                    // Move finger 2
                    dp[i + 1][f1][currChar] = min(dp[i + 1][f1][currChar], dp[i][f1][f2] + dist(f2 + 'A', word[i]));
                }
            }
        }
        
        int result = INT_MAX;
        for (int f1 = 0; f1 <= 26; f1++) {
            for (int f2 = 0; f2 <= 26; f2++) {
                result = min(result, dp[n][f1][f2]);
            }
        }
        
        return result;          
    }
};
