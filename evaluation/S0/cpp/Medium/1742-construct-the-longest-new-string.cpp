// Source: https://leetcode.com/problems/construct-the-longest-new-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given three integers x, y, and z.
//
// You have x strings equal to "AA", y strings equal to "BB", and z strings equal to "AB". You want to choose some (possibly all or none) of these strings and concatenate them in some order to form a new string. This new string must not contain "AAA" or "BBB" as a substring.
//
// Return the maximum possible length of the new string.
//
// A substring is a contiguous non-empty sequence of characters within a string.
//
// Example:
// Input: x = 2, y = 5, z = 1
// Output: 12
// Explanation: We can concatenate the strings "BB", "AA", "BB", "AA", "BB", and "AB" in that order. Then, our new string is "BBAABBAABBAB". 
// That string has length 12, and we can show that it is impossible to construct a string of longer length.
//
// Constraints:
// 1 <= x, y, z <= 50
//

class Solution {
public:
    int longestString(int x, int y, int z) {
        // dp[a][b][c][last] = max length using a "AA", b "BB", c "AB" with last used string type 'last'
        int dp[51][51][51][3];
        memset(dp, -1, sizeof(dp));
        
        function<int(int, int, int, int)> dfs = [&](int a, int b, int c, int last) {
            if (dp[a][b][c][last] != -1) return dp[a][b][c][last];
            int res = 0;
            if (a > 0 && last != 0) {
                res = max(res, 2 + dfs(a - 1, b, c, 0));
            }
            if (b > 0 && last != 1) {
                res = max(res, 2 + dfs(a, b - 1, c, 1));
            }
            if (c > 0) {
                res = max(res, 2 + dfs(a, b, c - 1, 2));
            }
            dp[a][b][c][last] = res;
            return res;
        };
        
        return dfs(x, y, z, 2); // Start with no last string used           
    }
};
