// Source: https://leetcode.com/problems/orderly-queue/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and an integer k. You can choose one of the first k letters of s and append it at the end of the string.
//
// Return the lexicographically smallest string you could have after applying the mentioned step any number of moves.
//
// Example:
// Input: s = "cba", k = 1
// Output: "acb"
// Explanation: 
// In the first move, we move the 1st character 'c' to the end, obtaining the string "bac".
// In the second move, we move the 1st character 'b' to the end, obtaining the final result "acb".
//
// Constraints:
// 1 <= k <= s.length <= 1000
// 	s consist of lowercase English letters.
//

char* orderlyQueue(char* s, int k) {
    int n = strlen(s);
    if (k > 1) {
        /* Can achieve any permutation, so just sort */
        char *res = (char*)malloc((n + 1) * sizeof(char));
        if (!res) return NULL;
        strcpy(res, s);
        /* Simple bubble sort since n <= 1000 */
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (res[j] > res[j + 1]) {
                    char tmp = res[j];
                    res[j] = res[j + 1];
                    res[j + 1] = tmp;
                }
            }
        }
        return res;
    } else {
        /* k == 1, find the smallest rotation */
        char *res = (char*)malloc((n + 1) * sizeof(char));
        if (!res) return NULL;
        strcpy(res, s);
        for (int i = 1; i < n; i++) {
            /* Generate rotation starting at index i */
            int idx = 0;
            for (int j = i; j < n; j++) {
                res[idx++] = s[j];
            }
            for (int j = 0; j < i; j++) {
                res[idx++] = s[j];
            }
            res[n] = '\0';
            if (strcmp(res, s) < 0) {
                strcpy(s, res);
            }
        }
        free(res);
        char *finalRes = (char*)malloc((n + 1) * sizeof(char));
        if (!finalRes) return NULL;
        strcpy(finalRes, s);
        return finalRes;
    }       
}
