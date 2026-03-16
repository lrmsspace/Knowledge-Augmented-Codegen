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

class Solution {
public:
    bool possiblyEquals(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        unordered_set<int> dp[n + 1][m + 1];
        dp[0][0].insert(0);
        
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                for (int diff : dp[i][j]) {
                    // Try to extend s1
                    if (i < n) {
                        if (isdigit(s1[i])) {
                            int val = 0;
                            for (int k = i; k < n && isdigit(s1[k]); k++) {
                                val = val * 10 + (s1[k] - '0');
                                dp[k + 1][j].insert(diff + val);
                            }
                        } else {
                            if (diff > 0) {
                                dp[i + 1][j].insert(diff - 1);
                            } else if (diff == 0 && j < m && s1[i] == s2[j]) {
                                dp[i + 1][j + 1].insert(0);
                            }
                        }
                    }
                    
                    // Try to extend s2
                    if (j < m) {
                        if (isdigit(s2[j])) {
                            int val = 0;
                            for (int k = j; k < m && isdigit(s2[k]); k++) {
                                val = val * 10 + (s2[k] - '0');
                                dp[i][k + 1].insert(diff - val);
                            }
                        } else {
                            if (diff < 0) {
                                dp[i][j + 1].insert(diff + 1);
                            } else if (diff == 0 && i < n && s1[i] == s2[j]) {
                                dp[i + 1][j + 1].insert(0);
                            }
                        }
                    }
                }
            }
        }
        
        return dp[n][m].count(0) > 0;           
    }
};
