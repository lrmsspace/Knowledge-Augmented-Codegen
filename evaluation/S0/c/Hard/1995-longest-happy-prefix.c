// Source: https://leetcode.com/problems/longest-happy-prefix/   |   Difficulty: Hard
//
// Problem Description:
// A string is called a happy prefix if is a non-empty prefix which is also a suffix (excluding itself).
//
// Given a string s, return the longest happy prefix of s. Return an empty string "" if no such prefix exists.
//
// Example:
// Input: s = "level"
// Output: "l"
// Explanation: s contains 4 prefix excluding itself ("l", "le", "lev", "leve"), and suffix ("l", "el", "vel", "evel"). The largest prefix which is also suffix is given by "l".
//
// Constraints:
// 1 <= s.length <= 105
// 	s contains only lowercase English letters.
//

char* longestPrefix(char* s) {
    int n = strlen(s);
    int *lps = (int*)malloc(n * sizeof(int));
    if (!lps) return NULL;
    lps[0] = 0;
    int len = 0;
    for (int i = 1; i < n; ) {
        if (s[i] == s[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    int longestLen = lps[n - 1];
    char *result = (char*)malloc((longestLen + 1) * sizeof(char));
    if (!result) {
        free(lps);
        return NULL;
    }
    strncpy(result, s, longestLen);
    result[longestLen] = '\0';
    free(lps);
    return result;      
}
