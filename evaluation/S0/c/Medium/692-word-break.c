// Source: https://leetcode.com/problems/word-break/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.
//
// Note that the same word in the dictionary may be reused multiple times in the segmentation.
//
// Example:
// Input: s = "leetcode", wordDict = ["leet","code"]
// Output: true
// Explanation: Return true because "leetcode" can be segmented as "leet code".
//
// Constraints:
// 1 <= s.length <= 300
// 	1 <= wordDict.length <= 1000
// 	1 <= wordDict[i].length <= 20
// 	s and wordDict[i] consist of only lowercase English letters.
// 	All the strings of wordDict are unique.
//

bool wordBreak(char* s, char** wordDict, int wordDictSize) {
    int n = strlen(s);
    bool dp[n + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = true;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < wordDictSize; j++) {
            int len = strlen(wordDict[j]);
            if (i >= len && dp[i - len] && strncmp(&s[i - len], wordDict[j], len) == 0) {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[n];       
}
