// Source: https://leetcode.com/problems/delete-columns-to-make-sorted-iii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of n strings strs, all of the same length.
//
// We may choose any deletion indices, and we delete all the characters in those indices for each string.
//
// For example, if we have strs = ["abcdef","uvwxyz"] and deletion indices {0, 2, 3}, then the final array after deletions is ["bef", "vyz"].
//
// Suppose we chose a set of deletion indices answer such that after deletions, the final array has every string (row) in lexicographic order. (i.e., (strs[0][0] <= strs[0][1] <= ... <= strs[0][strs[0].length - 1]), and (strs[1][0] <= strs[1][1] <= ... <= strs[1][strs[1].length - 1]), and so on). Return the minimum possible value of answer.length.
//
// Example:
// Input: strs = ["babca","bbazb"]
// Output: 3
// Explanation: After deleting columns 0, 1, and 4, the final array is strs = ["bc", "az"].
// Both these rows are individually in lexicographic order (ie. strs[0][0] <= strs[0][1] and strs[1][0] <= strs[1][1]).
// Note that strs[0] > strs[1] - the array strs is not necessarily in lexicographic order.
//
// Constraints:
// n == strs.length
// 	1 <= n <= 100
// 	1 <= strs[i].length <= 100
// 	strs[i] consists of lowercase English letters.
//

int minDeletionSize(char** strs, int strsSize) {
    if (!strs || strsSize <= 0) return 0;
    int len = strlen(strs[0]);
    int *dp = (int*)malloc(len * sizeof(int));
    if (!dp) return 0;
    for (int i = 0; i < len; ++i) dp[i] = 1;

    for (int i = 1; i < len; ++i) {
        for (int j = 0; j < i; ++j) {
            int k;
            for (k = 0; k < strsSize; ++k) {
                if (strs[k][j] > strs[k][i]) break;
            }
            if (k == strsSize) {
                if (dp[j] + 1 > dp[i]) dp[i] = dp[j] + 1;
            }
        }
    }

    int maxLen = 0;
    for (int i = 0; i < len; ++i) {
        if (dp[i] > maxLen) maxLen = dp[i];
    }
    free(dp);
    return len - maxLen;        
}
