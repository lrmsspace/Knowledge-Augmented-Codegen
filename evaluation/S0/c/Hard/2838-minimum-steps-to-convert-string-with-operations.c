// Source: https://leetcode.com/problems/minimum-steps-to-convert-string-with-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings, word1 and word2, of equal length. You need to transform word1 into word2.
//
// For this, divide word1 into one or more contiguous substrings. For each substring substr you can perform the following operations:
//
//
//  
//  Replace: Replace the character at any one index of substr with another lowercase English letter.
//  
//  
//  Swap: Swap any two characters in substr.
//  
//  
//  Reverse Substring: Reverse substr.
//  
//
//
// Each of these counts as one operation and each character of each substring can be used in each type of operation at most once (i.e. no single index may be involved in more than one replace, one swap, or one reverse).
//
// Return the minimum number of operations required to transform word1 into word2.
//
// Example:
// Input: word1 = "abcdf", word2 = "dacbe"
//
// Output: 4
//
// Explanation:
//
// Divide word1 into "ab", "c", and "df". The operations are:
//
//
//  For the substring "ab",
//
//  
//   Perform operation of type 3 on "ab" -> "ba".
//   Perform operation of type 1 on "ba" -> "da".
//  
//  
//  For the substring "c" do no operations.
//  For the substring "df",
//  
//   Perform operation of type 1 on "df" -> "bf".
//   Perform operation of type 1 on "bf" -> "be".
//
// Constraints:
// 1 <= word1.length == word2.length <= 100
//  word1 and word2 consist only of lowercase English letters.
//

int minOperations(char* word1, char* word2) {
    int n = strlen(word1);
    int dp[n + 1];
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i - 1] + 2; /* worst case: replace each character */
        for (int j = i - 1; j >= 0; --j) {
            int diff = 0;
            int count[26] = {0};
            for (int k = j; k < i; ++k) {
                if (word1[k] != word2[k]) {
                    diff++;
                    count[word1[k] - 'a']++;
                    count[word2[k] - 'a']--;
                }
            }
            if (diff == 0) {
                dp[i] = fmin(dp[i], dp[j]);
            } else if (diff == 2) {
                for (int c = 0; c < 26; ++c) {
                    if (count[c] == 2 || count[c] == -2) {
                        dp[i] = fmin(dp[i], dp[j] + 1); /* swap */
                        break;
                    }
                }
            } else if (diff > 2 && diff % 2 == 0) {
                int halfDiff = diff / 2;
                int swapCount = 0;
                for (int c = 0; c < 26; ++c) {
                    if (count[c] > 0) {
                        swapCount += count[c];
                    }
                }
                if (swapCount == halfDiff) {
                    dp[i] = fmin(dp[i], dp[j] + halfDiff); /* all can be swapped */
                } else {
                    dp[i] = fmin(dp[i], dp[j] + halfDiff + 1); /* some need replace */
                }
            } else {
                dp[i] = fmin(dp[i], dp[j] + diff); /* all need replace */
            }
        }
    }
    return dp[n];       
}
