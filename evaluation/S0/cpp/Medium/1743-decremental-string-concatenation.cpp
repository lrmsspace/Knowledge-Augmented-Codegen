// Source: https://leetcode.com/problems/decremental-string-concatenation/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array words containing n strings.
//
// Let's define a join operation join(x, y) between two strings x and y as concatenating them into xy. However, if the last character of x is equal to the first character of y, one of them is deleted.
//
// For example join("ab", "ba") = "aba" and join("ab", "cde") = "abcde".
//
// You are to perform n - 1 join operations. Let str0 = words[0]. Starting from i = 1 up to i = n - 1, for the ith operation, you can do one of the following:
//
//
// 	Make stri = join(stri - 1, words[i])
// 	Make stri = join(words[i], stri - 1)
//
//
// Your task is to minimize the length of strn - 1.
//
// Return an integer denoting the minimum possible length of strn - 1.
//
// Example:
// Input: words = ["aa","ab","bc"]
// Output: 4
// Explanation: In this example, we can perform join operations in the following order to minimize the length of str2: 
// str0 = "aa"
// str1 = join(str0, "ab") = "aab"
// str2 = join(str1, "bc") = "aabc" 
// It can be shown that the minimum possible length of str2 is 4.
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length <= 50
// 	Each character in words[i] is an English lowercase letter
//

class Solution {
public:
    int minimizeConcatenatedLength(vector<string>& words) {
        const int ALPHABET_SIZE = 26;
        const int OFFSET = 'a';

        int n = words.size();
        vector<vector<int>> dp(ALPHABET_SIZE, vector<int>(ALPHABET_SIZE, INT_MAX));

        // Initialize dp with the first word
        int firstWordLen = words[0].length();
        int firstWordStart = words[0][0] - OFFSET;
        int firstWordEnd = words[0].back() - OFFSET;
        dp[firstWordStart][firstWordEnd] = firstWordLen;

        for (int i = 1; i < n; ++i) {
            vector<vector<int>> newDp(ALPHABET_SIZE, vector<int>(ALPHABET_SIZE, INT_MAX));
            int wordLen = words[i].length();
            int wordStart = words[i][0] - OFFSET;
            int wordEnd = words[i].back() - OFFSET;

            for (int startChar = 0; startChar < ALPHABET_SIZE; ++startChar) {
                for (int endChar = 0; endChar < ALPHABET_SIZE; ++endChar) {
                    if (dp[startChar][endChar] == INT_MAX) continue;

                    // Option 1: Append current word to the end
                    int cost1 = dp[startChar][endChar] + wordLen - (endChar == wordStart ? 1 : 0);
                    newDp[startChar][wordEnd] = min(newDp[startChar][wordEnd], cost1);

                    // Option 2: Prepend current word to the beginning
                    int cost2 = dp[startChar][endChar] + wordLen - (startChar == wordEnd ? 1 : 0);
                    newDp[wordStart][endChar] = min(newDp[wordStart][endChar], cost2);
                }
            }
            dp = move(newDp);
        }

        int minLength = INT_MAX;
        for (int startChar = 0; startChar < ALPHABET_SIZE; ++startChar) {
            for (int endChar = 0; endChar < ALPHABET_SIZE; ++endChar) {
                minLength = min(minLength, dp[startChar][endChar]);
            }
        }

        return minLength;           
    }
};
