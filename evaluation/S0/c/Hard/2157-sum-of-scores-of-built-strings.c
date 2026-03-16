// Source: https://leetcode.com/problems/sum-of-scores-of-built-strings/   |   Difficulty: Hard
//
// Problem Description:
// You are building a string s of length n one character at a time, prepending each new character to the front of the string. The strings are labeled from 1 to n, where the string with length i is labeled si.
//
//
// 	For example, for s = "abaca", s1 == "a", s2 == "ca", s3 == "aca", etc.
//
//
// The score of si is the length of the longest common prefix between si and sn (Note that s == sn).
//
// Given the final string s, return the sum of the score of every si.
//
// Example:
// Input: s = "babab"
// Output: 9
// Explanation:
// For s1 == "b", the longest common prefix is "b" which has a score of 1.
// For s2 == "ab", there is no common prefix so the score is 0.
// For s3 == "bab", the longest common prefix is "bab" which has a score of 3.
// For s4 == "abab", there is no common prefix so the score is 0.
// For s5 == "babab", the longest common prefix is "babab" which has a score of 5.
// The sum of the scores is 1 + 0 + 3 + 0 + 5 = 9, so we return 9.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
//

long long sumScores(char* s) {
    int n = strlen(s);
    int *z = (int*)calloc(n, sizeof(int));
    if (!z) return 0; /* allocation failure */

    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) z[i] = (z[i - l] < (r - i + 1)) ? z[i - l] : (r - i + 1);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) {
            l = i; r = i + z[i] - 1;
        }
    }

    long long result = n; /* account for s_n */
    for (int i = 1; i < n; ++i) {
        result += z[i];
    }

    free(z);
    return result;      
}
