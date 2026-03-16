// Source: https://leetcode.com/problems/check-if-an-original-string-exists-given-two-encoded-strings/   |   Difficulty: Hard
//
// Problem Description:
// An original string, consisting of lowercase English letters, can be encoded by the following steps:
//
//
// 	Arbitrarily split it into a sequence of some number of non-empty substrings.
// 	Arbitrarily choose some elements (possibly none) of the sequence, and replace each with its length (as a numeric string).
// 	Concatenate the sequence as the encoded string.
//
//
// For example, one way to encode an original string "abcdefghijklmnop" might be:
//
//
// 	Split it as a sequence: ["ab", "cdefghijklmn", "o", "p"].
// 	Choose the second and third elements to be replaced by their lengths, respectively. The sequence becomes ["ab", "12", "1", "p"].
// 	Concatenate the elements of the sequence to get the encoded string: "ab121p".
//
//
// Given two encoded strings s1 and s2, consisting of lowercase English letters and digits 1-9 (inclusive), return true if there exists an original string that could be encoded as both s1 and s2. Otherwise, return false.
//
// Note: The test cases are generated such that the number of consecutive digits in s1 and s2 does not exceed 3.
//
// Example:
// Input: s1 = "internationalization", s2 = "i18n"
// Output: true
// Explanation: It is possible that "internationalization" was the original string.
// - "internationalization" 
//   -> Split:       ["internationalization"]
//   -> Do not replace any element
//   -> Concatenate:  "internationalization", which is s1.
// - "internationalization"
//   -> Split:       ["i", "nternationalizatio", "n"]
//   -> Replace:     ["i", "18",                 "n"]
//   -> Concatenate:  "i18n", which is s2
//
// Constraints:
// 1 <= s1.length, s2.length <= 40
// 	s1 and s2 consist of digits 1-9 (inclusive), and lowercase English letters only.
// 	The number of consecutive digits in s1 and s2 does not exceed 3.
//

bool possiblyEquals(char* s1, char* s2) {
    /* Use DFS with memoization to explore all possible interpretations of the encoded strings.
       The key idea is to track the difference in length between the two strings as we parse them.
       A positive difference means s1 is longer, a negative means s2 is longer, and zero means they are equal so far.
    */

    #define MAX_LEN 40
    #define OFFSET 1600  // To handle negative differences in memoization

    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int memo[MAX_LEN + 1][MAX_LEN + 1][OFFSET * 2];
    memset(memo, -1, sizeof(memo));

    int dfs(int i, int j, int diff) {
        if (i == len1 && j == len2) return diff == 0;
        if (memo[i][j][diff + OFFSET] != -1) return memo[i][j][diff + OFFSET];

        // Try to match letters
        if (diff == 0) {
            if (i < len1 && j < len2 && s1[i] == s2[j]) {
                if (dfs(i + 1, j + 1, diff)) {
                    memo[i][j][diff + OFFSET] = 1;
                    return 1;
                }
            }
        }

        // Handle digits in s1
        if (i < len1 && isdigit(s1[i])) {
            int num = 0;
            for (int k = i; k < len1 && isdigit(s1[k]); ++k) {
                num = num * 10 + (s1[k] - '0');
                if (dfs(k + 1, j, diff + num)) {
                    memo[i][j][diff + OFFSET] = 1;
                    return 1;
                }
            }
        }

        // Handle digits in s2
        if (j < len2 && isdigit(s2[j])) {
            int num = 0;
            for (int k = j; k < len2 && isdigit(s2[k]); ++k) {
                num = num * 10 + (s2[k] - '0');
                if (dfs(i, k + 1, diff - num)) {
                    memo[i][j][diff + OFFSET] = 1;
                    return 1;
                }
            }
        }
        memo[i][j][diff + OFFSET] = 0;
        return 0;
    }
    return dfs(0, 0, 0);
}
