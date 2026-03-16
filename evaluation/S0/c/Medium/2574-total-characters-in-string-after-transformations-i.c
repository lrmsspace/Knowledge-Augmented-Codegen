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

int lengthAfterTransformations(char* s, int t) {
    const int MOD = 1000000007;
    int dp[26];
    for (int i = 0; i < 26; ++i) {
        dp[i] = 1;  // Base case: after 0 transformations, each character contributes 1 to the length
    }

    // Precompute the length contributions for each character after t transformations
    for (int step = 0; step < t; ++step) {
        int new_dp[26];
        for (int i = 0; i < 25; ++i) {
            new_dp[i] = dp[i + 1];  // 'a' to 'y' become the next character
        }
        new_dp[25] = (dp[0] + dp[1]) % MOD;  // 'z' becomes "ab"
        for (int i = 0; i < 26; ++i) {
            dp[i] = new_dp[i];
        }
    }

    // Calculate the total length after t transformations
    long long total_length = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
        total_length = (total_length + dp[s[i] - 'a']) % MOD;
    }

    return (int)total_length;       
}
