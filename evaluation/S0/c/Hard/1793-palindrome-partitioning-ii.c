// Source: https://leetcode.com/problems/palindrome-partitioning-ii/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s, partition s such that every substring of the partition is a palindrome.
//
// Return the minimum cuts needed for a palindrome partitioning of s.
//
// Example:
// Input: s = "aab"
// Output: 1
// Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
//
// Constraints:
// 1 <= s.length <= 2000
// 	s consists of lowercase English letters only.
//

int minCut(char* s) {
    int n = strlen(s);
    int *dp = (int*)malloc((n + 1) * sizeof(int));
    int **isPal = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        isPal[i] = (int*)calloc(n, sizeof(int));
    }

    for (int i = 0; i <= n; i++) {
        dp[i] = i - 1; // max cuts
    }

    for (int end = 0; end < n; end++) {
        for (int start = 0; start <= end; start++) {
            if (s[start] == s[end] && (end - start <= 2 || isPal[start + 1][end - 1])) {
                isPal[start][end] = 1;
                dp[end + 1] = dp[end + 1] < dp[start] + 1 ? dp[end + 1] : dp[start] + 1;
            }
        }
    }

    int result = dp[n];
    for (int i = 0; i < n; i++) {
        free(isPal[i]);
    }
    free(isPal);
    free(dp);
    return result;      
}
