// Source: https://leetcode.com/problems/longest-duplicate-substring/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s, consider all duplicated substrings: (contiguous) substrings of s that occur 2 or more times. The occurrences may overlap.
//
// Return any duplicated substring that has the longest possible length. If s does not have a duplicated substring, the answer is "".
//
// Example:
// Input: s = "banana"
// Output: "ana"
//
// Constraints:
// 2 <= s.length <= 3 * 104
// 	s consists of lowercase English letters.
//

char* longestDupSubstring(char* s) {
    int n = strlen(s);
    int left = 1, right = n - 1;
    int start = -1, maxLen = 0;
    const unsigned int mod = 1000000007;
    const unsigned int base = 31;

    unsigned int *powBase = (unsigned int*)malloc((n + 1) * sizeof(unsigned int));
    powBase[0] = 1;
    for (int i = 1; i <= n; i++) {
        powBase[i] = (powBase[i - 1] * base) % mod;
    }

    while (left <= right) {
        int len = left + (right - left) / 2;
        unsigned int hash = 0;
        for (int i = 0; i < len; i++) {
            hash = (hash * base + (s[i] - 'a' + 1)) % mod;
        }

        int found = 0;
        unsigned int *hashes = (unsigned int*)calloc(n - len + 1, sizeof(unsigned int));
        hashes[0] = hash;
        for (int i = 1; i <= n - len; i++) {
            hash = (hash * base - (s[i - 1] - 'a' + 1) * powBase[len] % mod + mod) % mod;
            hash = (hash + (s[i + len - 1] - 'a' + 1)) % mod;
            hashes[i] = hash;
        }

        qsort(hashes, n - len + 1, sizeof(unsigned int), cmpInt);

        for (int i = 1; i <= n - len; i++) {
            if (hashes[i] == hashes[i - 1]) {
                found = 1;
                break;
            }
        }
        free(hashes);

        if (found) {
            start = left;
            maxLen = len;
            left = len + 1;
        } else {
            right = len - 1;
        }
    }

    free(powBase);

    if (start == -1) return "";

    char *result = (char*)malloc((maxLen + 1) * sizeof(char));
    strncpy(result, s + start - 1, maxLen);
    result[maxLen] = '\0';
    return result;      
}
