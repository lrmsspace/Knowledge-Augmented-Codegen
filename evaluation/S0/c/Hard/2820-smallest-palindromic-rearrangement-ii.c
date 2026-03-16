// Source: https://leetcode.com/problems/smallest-palindromic-rearrangement-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a palindromic string s and an integer k.
//
// Return the k-th lexicographically smallest palindromic permutation of s. If there are fewer than k distinct palindromic permutations, return an empty string.
//
// Note: Different rearrangements that yield the same palindromic string are considered identical and are counted once.
//
// Example:
// Input: s = "abba", k = 2
//
// Output: "baab"
//
// Explanation:
//
//
// 	The two distinct palindromic rearrangements of "abba" are "abba" and "baab".
// 	Lexicographically, "abba" comes before "baab". Since k = 2, the output is "baab".
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of lowercase English letters.
// 	s is guaranteed to be palindromic.
// 	1 <= k <= 106
//

char* smallestPalindrome(char* s, int k) {
    int count[26] = {0};
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        count[s[i] - 'a']++;
    }
    char half[5000 + 1];
    int halfLen = 0;
    char midChar = '\0';
    for (int i = 0; i < 26; i++) {
        if (count[i] % 2 == 1) {
            midChar = 'a' + i;
        }
        for (int j = 0; j < count[i] / 2; j++) {
            half[halfLen++] = 'a' + i;
        }
    }
    half[halfLen] = '\0';

    char *result = (char *)malloc((len + 1) * sizeof(char));
    if (!result) return "";

    int fact[5001];
    fact[0] = 1;
    for (int i = 1; i <= halfLen; i++) {
        fact[i] = fact[i - 1] * i;
    }

    int totalPerms = fact[halfLen];
    for (int i = 0; i < 26; i++) {
        totalPerms /= fact[count[i] / 2];
    }

    if (k > totalPerms) {
        free(result);
        return "";
    }

    int used[5000] = {0};
    for (int pos = 0; pos < halfLen; pos++) {
        for (int i = 0; i < halfLen; i++) {
            if (used[i]) continue;
            char ch = half[i];
            used[i] = 1;

            int perms = fact[halfLen - pos - 1];
            int tempCount[26] = {0};
            for (int j = 0; j < 26; j++) {
                tempCount[j] = count[j] / 2;
            }
            tempCount[ch - 'a']--;
            for (int j = 0; j < 26; j++) {
                perms /= fact[tempCount[j]];
            }

            if (k > perms) {
                k -= perms;
                used[i] = 0;
            } else {
                result[pos] = ch;
                count[ch - 'a'] -= 2;
                break;
            }
        }
    }
    result[halfLen] = midChar;
    for (int i = halfLen - 1; i >= 0; i--) {
        result[len - halfLen + (halfLen - 1 - i)] = result[i];
    }
    result[len] = '\0';
    return result;
}
