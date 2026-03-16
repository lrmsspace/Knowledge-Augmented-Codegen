// Source: https://leetcode.com/problems/special-binary-string/   |   Difficulty: Hard
//
// Problem Description:
// Special binary strings are binary strings with the following two properties:
//
//
// 	The number of 0's is equal to the number of 1's.
// 	Every prefix of the binary string has at least as many 1's as 0's.
//
//
// You are given a special binary string s.
//
// A move consists of choosing two consecutive, non-empty, special substrings of s, and swapping them. Two strings are consecutive if the last character of the first string is exactly one index before the first character of the second string.
//
// Return the lexicographically largest resulting string possible after applying the mentioned operations on the string.
//
// Example:
// Input: s = "11011000"
// Output: "11100100"
// Explanation: The strings "10" [occuring at s[1]] and "1100" [at s[3]] are swapped.
// This is the lexicographically largest string possible after some number of swaps.
//
// Constraints:
// 1 <= s.length <= 50
// 	s[i] is either '0' or '1'.
// 	s is a special binary string.
//

char* makeLargestSpecial(char* s) {
    int len = strlen(s);
    if (len <= 2) return s;

    char **subs = (char**)malloc(len / 2 * sizeof(char*));
    int subsCount = 0;
    int balance = 0, lastPos = 0;
    for (int i = 0; i < len; ++i) {
        balance += (s[i] == '1') ? 1 : -1;
        if (balance == 0) {
            char *inner = (char*)malloc((i - lastPos) * sizeof(char));
            strncpy(inner, s + lastPos + 1, i - lastPos - 1);
            inner[i - lastPos - 1] = '\0';
            char *processedInner = makeLargestSpecial(inner);
            free(inner);

            int subLen = strlen(processedInner) + 2;
            char *sub = (char*)malloc((subLen + 1) * sizeof(char));
            sub[0] = '1';
            strcpy(sub + 1, processedInner);
            sub[subLen - 1] = '0';
            sub[subLen] = '\0';
            free(processedInner);

            subs[subsCount++] = sub;
            lastPos = i + 1;
        }
    }

    qsort(subs, subsCount, sizeof(char*), (int (*)(const void*, const void*))strcmp);
    char *result = (char*)malloc((len + 1) * sizeof(char));
    result[0] = '\0';
    for (int i = subsCount - 1; i >= 0; --i) {
        strcat(result, subs[i]);
        free(subs[i]);
    }
    free(subs);

    return result;      
}
