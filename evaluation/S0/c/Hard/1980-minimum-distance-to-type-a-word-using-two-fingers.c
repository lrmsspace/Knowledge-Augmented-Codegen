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

int minimumDistance(char* word) {
    int n = strlen(word);
    int dp[27][27]; // dp[i][j]: min distance to type up to k-th letter with finger1 on i, finger2 on j
    memset(dp, 0x3f, sizeof(dp));
    dp[26][26] = 0; // both fingers start free

    for (int k = 0; k < n; ++k) {
        int c = word[k] - 'A';
        int x = c / 6, y = c % 6;
        int newDp[27][27];
        memset(newDp, 0x3f, sizeof(newDp));

        for (int i = 0; i < 27; ++i) {
            for (int j = 0; j < 27; ++j) {
                if (dp[i][j] == 0x3f3f3f3f) continue;

                // Move finger1 to c
                int cost1 = 0;
                if (i != 26) {
                    int ix = i / 6, iy = i % 6;
                    cost1 = abs(ix - x) + abs(iy - y);
                }
                if (dp[i][j] + cost1 < newDp[c][j]) {
                    newDp[c][j] = dp[i][j] + cost1;
                }

                // Move finger2 to c
                int cost2 = 0;
                if (j != 26) {
                    int jx = j / 6, jy = j % 6;
                    cost2 = abs(jx - x) + abs(jy - y);
                }
                if (dp[i][j] + cost2 < newDp[i][c]) {
                    newDp[i][c] = dp[i][j] + cost2;
                }
            }
        }
        memcpy(dp, newDp, sizeof(dp));
    }

    int result = 0x3f3f3f3f;
    for (int i = 0; i < 27; ++i) {
        for (int j = 0; j < 27; ++j) {
            if (dp[i][j] < result) {
                result = dp[i][j];
            }
        }
    }
    return result;      
}
