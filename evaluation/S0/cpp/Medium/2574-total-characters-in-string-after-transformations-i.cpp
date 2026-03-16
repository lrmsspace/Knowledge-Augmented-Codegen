// Source: https://leetcode.com/problems/total-characters-in-string-after-transformations-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and an integer t, representing the number of transformations to perform. In one transformation, every character in s is replaced according to the following rules:
//
//
// 	If the character is 'z', replace it with the string "ab".
// 	Otherwise, replace it with the next character in the alphabet. For example, 'a' is replaced with 'b', 'b' is replaced with 'c', and so on.
//
//
// Return the length of the resulting string after exactly t transformations.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: s = "abcyy", t = 2
//
// Output: 7
//
// Explanation:
//
//
// 	First Transformation (t = 1):
//
// 	
// 		'a' becomes 'b'
// 		'b' becomes 'c'
// 		'c' becomes 'd'
// 		'y' becomes 'z'
// 		'y' becomes 'z'
// 		String after the first transformation: "bcdzz"
// 	
// 	
// 	Second Transformation (t = 2):
// 	
// 		'b' becomes 'c'
// 		'c' becomes 'd'
// 		'd' becomes 'e'
// 		'z' becomes "ab"
// 		'z' becomes "ab"
// 		String after the second transformation: "cdeabab"
// 	
// 	
// 	Final Length of the string: The string is "cdeabab", which has 7 characters.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists only of lowercase English letters.
// 	1 <= t <= 105
//

class Solution {
public:
    int lengthAfterTransformations(string s, int t) {
        const int MOD = 1e9 + 7;
        vector<vector<int>> dp(26, vector<int>(t + 1, 0));

        // Base case: for t = 0, each character contributes 1 to the length
        for (int c = 0; c < 26; ++c) {
            dp[c][0] = 1;
        }

        // Fill the DP table
        for (int time = 1; time <= t; ++time) {
            for (int c = 0; c < 26; ++c) {
                if (c == 25) { // 'z'
                    dp[c][time] = (dp[0][time - 1] + dp[1][time - 1]) % MOD; // 'z' -> "ab"
                } else {
                    dp[c][time] = dp[c + 1][time - 1]; // c -> next character
                }
            }
        }

        // Calculate the total length after t transformations
        long long totalLength = 0;
        for (char ch : s) {
            int c = ch - 'a';
            totalLength = (totalLength + dp[c][t]) % MOD;
        }

        return static_cast<int>(totalLength);           
    }
};
