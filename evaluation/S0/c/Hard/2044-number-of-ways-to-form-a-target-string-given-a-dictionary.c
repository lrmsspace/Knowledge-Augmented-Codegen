// Source: https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/   |   Difficulty: Hard
//
// Problem Description:
// You are given a list of strings of the same length words and a string target.
//
// Your task is to form target using the given words under the following rules:
//
//
// 	target should be formed from left to right.
// 	To form the ith character (0-indexed) of target, you can choose the kth character of the jth string in words if target[i] = words[j][k].
// 	Once you use the kth character of the jth string of words, you can no longer use the xth character of any string in words where x <= k. In other words, all characters to the left of or at index k become unusuable for every string.
// 	Repeat the process until you form the string target.
//
//
// Notice that you can use multiple characters from the same string in words provided the conditions above are met.
//
// Return the number of ways to form target from words. Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: words = ["acca","bbbb","caca"], target = "aba"
// Output: 6
// Explanation: There are 6 ways to form target.
// "aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("caca")
// "aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("caca")
// "aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("acca")
// "aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("acca")
// "aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("acca")
// "aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("caca")
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length <= 1000
// 	All strings in words have the same length.
// 	1 <= target.length <= 1000
// 	words[i] and target contain only lowercase English letters.
//

int numWays(char** words, int wordsSize, char* target) {
    int MOD = 1000000007;
    int wordLen = strlen(words[0]);
    int targetLen = strlen(target);

    // Precompute frequency of each character at each position
    int freq[26][wordLen];
    memset(freq, 0, sizeof(freq));
    for (int i = 0; i < wordsSize; i++) {
        for (int j = 0; j < wordLen; j++) {
            freq[words[i][j] - 'a'][j]++;
        }
    }

    // DP array to store number of ways to form target up to length j
    long dp[targetLen + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1; // One way to form    
    for (int i = 0; i < wordLen; i++) {
        for (int j = targetLen - 1; j >= 0; j--) {
            int charIndex = target[j] - 'a';
            if (freq[charIndex][i] > 0) {
                dp[j + 1] = (dp[j + 1] + dp[j] * freq[charIndex][i]) % MOD;
            }
        }
    }
    return (int)dp[targetLen];   
}
