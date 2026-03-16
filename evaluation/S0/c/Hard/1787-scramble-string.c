// Source: https://leetcode.com/problems/scramble-string/   |   Difficulty: Hard
//
// Problem Description:
// We can scramble a string s to get a string t using the following algorithm:
//
//
// 	If the length of the string is 1, stop.
// 	If the length of the string is > 1, do the following:
// 	
// 		Split the string into two non-empty substrings at a random index, i.e., if the string is s, divide it to x and y where s = x + y.
// 		Randomly decide to swap the two substrings or to keep them in the same order. i.e., after this step, s may become s = x + y or s = y + x.
// 		Apply step 1 recursively on each of the two substrings x and y.
// 	
// 	
//
//
// Given two strings s1 and s2 of the same length, return true if s2 is a scrambled string of s1, otherwise, return false.
//
// Example:
// Input: s1 = "great", s2 = "rgeat"
// Output: true
// Explanation: One possible scenario applied on s1 is:
// "great" --> "gr/eat" // divide at random index.
// "gr/eat" --> "gr/eat" // random decision is not to swap the two substrings and keep them in order.
// "gr/eat" --> "g/r / e/at" // apply the same algorithm recursively on both substrings. divide at random index each of them.
// "g/r / e/at" --> "r/g / e/at" // random decision was to swap the first substring and to keep the second substring in the same order.
// "r/g / e/at" --> "r/g / e/ a/t" // again apply the algorithm recursively, divide "at" to "a/t".
// "r/g / e/ a/t" --> "r/g / e/ a/t" // random decision is to keep both substrings in the same order.
// The algorithm stops now, and the result string is "rgeat" which is s2.
// As one possible scenario led s1 to be scrambled to s2, we return true.
//
// Constraints:
// s1.length == s2.length
// 	1 <= s1.length <= 30
// 	s1 and s2 consist of lowercase English letters.
//

bool isScramble(char* s1, char* s2) {
    int len = strlen(s1);
    if (len != strlen(s2)) return false;

    // dp[i][j][l]: whether s1 substring starting at i with length l
    // can be scrambled to s2 substring starting at j with length l
    bool dp[31][31][31];
    memset(dp, 0, sizeof(dp));

    // Initialize for substrings of length 1
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            dp[i][j][1] = (s1[i] == s2[j]);
        }
    }

    // Build up the DP table for lengths from 2 to len
    for (int l = 2; l <= len; ++l) {
        for (int i = 0; i <= len - l; ++i) {
            for (int j = 0; j <= len - l; ++j) {
                for (int k = 1; k < l; ++k) {
                    // Check without swap
                    if (dp[i][j][k] && dp[i + k][j + k][l - k]) {
                        dp[i][j][l] = true;
                        break;
                    }
                    // Check with swap
                    if (dp[i][j + l - k][k] && dp[i + k][j][l - k]) {
                        dp[i][j][l] = true;
                        break;
                    }
                }
            }
        }
    }

    return dp[0][0][len];       
}
