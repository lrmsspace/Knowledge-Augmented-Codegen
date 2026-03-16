// Source: https://leetcode.com/problems/distinct-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// Given two strings s and t, return the number of distinct subsequences of s which equals t.
//
// The test cases are generated so that the answer fits on a 32-bit signed integer.
//
// Example:
// Input: s = "rabbbit", t = "rabbit"
// Output: 3
// Explanation:
// As shown below, there are 3 ways you can generate "rabbit" from s.
// rabbbit
// rabbbit
// rabbbit
//
// Constraints:
// 1 <= s.length, t.length <= 1000
// 	s and t consist of English letters.
//

int numDistinct(char* s, char* t) {
    int m = strlen(s);
    int n = strlen(t);
    int *dpPrev = (int*)calloc(n + 1, sizeof(int));
    int *dpCurr = (int*)calloc(n + 1, sizeof(int));
    if (!dpPrev || !dpCurr) {
        free(dpPrev);
        free(dpCurr);
        return 0; // allocation failure
    }
    dpPrev[0] = 1; // empty t can be formed by any prefix of s

    for (int i = 1; i <= m; i++) {
        dpCurr[0] = 1; // empty t can be formed by any prefix of s
        for (int j = 1; j <= n; j++) {
            if (s[i - 1] == t[j - 1]) {
                dpCurr[j] = dpPrev[j - 1] + dpPrev[j];
            } else {
                dpCurr[j] = dpPrev[j];
            }
        }
        int *temp = dpPrev;
        dpPrev = dpCurr;
        dpCurr = temp;
    }

    int result = dpPrev[n];
    free(dpPrev);
    free(dpCurr);
    return result;      
}
