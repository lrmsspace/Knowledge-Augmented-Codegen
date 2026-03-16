// Source: https://leetcode.com/problems/minimum-number-of-valid-strings-to-form-target-i/   |   Difficulty: Medium
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
// 	1 <= words[i].length <= 5 * 103
// 	The input is generated such that sum(words[i].length) <= 105.
// 	words[i] consists only of lowercase English letters.
// 	1 <= target.length <= 5 * 103
// 	target consists only of lowercase English letters.
//

int minValidStrings(char** words, int wordsSize, char* target) {
    int targetLen = strlen(target);
    int dp[targetLen + 1];
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    for (int i = 1; i <= targetLen; i++) {
        for (int j = 0; j < wordsSize; j++) {
            int wordLen = strlen(words[j]);
            if (wordLen <= i && strncmp(&target[i - wordLen], words[j], wordLen) == 0) {
                dp[i] = fmin(dp[i], dp[i - wordLen] + 1);
            }
        }
    }

    return dp[targetLen] == 0x3f3f3f3f ? -1 : dp[targetLen];        
}
