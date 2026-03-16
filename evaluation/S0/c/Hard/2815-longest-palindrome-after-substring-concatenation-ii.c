// Source: https://leetcode.com/problems/longest-palindrome-after-substring-concatenation-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings, s and t.
//
// You can create a new string by selecting a substring from s (possibly empty) and a substring from t (possibly empty), then concatenating them in order.
//
// Return the length of the longest palindrome that can be formed this way.
//
// Example:
// Input: s = "a", t = "a"
//
// Output: 2
//
// Explanation:
//
// Concatenating "a" from s and "a" from t results in "aa", which is a palindrome of length 2.
//
// Constraints:
// 1 <= s.length, t.length <= 1000
//  s and t consist of lowercase English letters.
//

int longestPalindrome(char* s, char* t) {
    int sLen = strlen(s);
    int tLen = strlen(t);
    int maxLen = 0;

    // Check all possible substrings of s
    for (int i = 0; i <= sLen; i++) {
        for (int j = i; j <= sLen; j++) {
            // Extract substring from s
            int subLen = j - i;
            char* subS = (char*)malloc((subLen + 1) * sizeof(char));
            strncpy(subS, s + i, subLen);
            subS[subLen] = '\0';

            // Check all possible substrings of t
            for (int k = 0; k <= tLen; k++) {
                for (int l = k; l <= tLen; l++) {
                    // Extract substring from t
                    int subTLen = l - k;
                    char* subT = (char*)malloc((subTLen + 1) * sizeof(char));
                    strncpy(subT, t + k, subTLen);
                    subT[subTLen] = '\0';

                    // Concatenate substrings
                    int concatLen = subLen + subTLen;
                    char* concatStr = (char*)malloc((concatLen + 1) * sizeof(char));
                    strcpy(concatStr, subS);
                    strcat(concatStr, subT);

                    // Check if concatenated string is a palindrome
                    int left = 0, right = concatLen - 1;
                    int isPalindrome = 1;
                    while (left < right) {
                        if (concatStr[left] != concatStr[right]) {
                            isPalindrome = 0;
                            break;
                        }
                        left++;
                        right--;
                    }

                    if (isPalindrome && concatLen > maxLen) {
                        maxLen = concatLen;
                    }

                    free(subT);
                    free(concatStr);
                }
            }

            free(subS);
        }
    }

    return maxLen;      
}
