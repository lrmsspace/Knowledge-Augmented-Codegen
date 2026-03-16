// Source: https://leetcode.com/problems/minimum-number-of-valid-strings-to-form-target-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of strings words and a string target.
//
// A string x is called valid if x is a prefix of any string in words.
//
// Return the minimum number of valid strings that can be concatenated to form target. If it is not possible to form target, return -1.
//
// Example:
// Input: words = ["abc","aaaaa","bcdef"], target = "aabcdabc"
//
// Output: 3
//
// Explanation:
//
// The target string can be formed by concatenating:
//
//
// 	Prefix of length 2 of words[1], i.e. "aa".
// 	Prefix of length 3 of words[2], i.e. "bcd".
// 	Prefix of length 3 of words[0], i.e. "abc".
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 5 * 104
// 	The input is generated such that sum(words[i].length) <= 105.
// 	words[i] consists only of lowercase English letters.
// 	1 <= target.length <= 5 * 104
// 	target consists only of lowercase English letters.
//

int minValidStrings(char** words, int wordsSize, char* target) {
    int targetLen = strlen(target);
    int *dp = (int*)malloc((targetLen + 1) * sizeof(int));
    if (!dp) return -1;
    for (int i = 0; i <= targetLen; ++i) dp[i] = targetLen + 1;
    dp[0] = 0;

    for (int i = 1; i <= targetLen; ++i) {
        for (int w = 0; w < wordsSize; ++w) {
            int wlen = strlen(words[w]);
            if (wlen <= i) {
                if (strncmp(target + i - wlen, words[w], wlen) == 0) {
                    if (dp[i - wlen] + 1 < dp[i]) {
                        dp[i] = dp[i - wlen] + 1;
                    }
                }
            } else {
                if (strncmp(target, words[w], i) == 0) {
                    if (dp[0] + 1 < dp[i]) {
                        dp[i] = dp[0] + 1;
                    }
                }
            }
        }
    }

    int result = (dp[targetLen] == targetLen + 1) ? -1 : dp[targetLen];
    free(dp);
    return result;      
}
