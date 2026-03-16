// Source: https://leetcode.com/problems/delete-columns-to-make-sorted-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of n strings strs, all of the same length.
//
// We may choose any deletion indices, and we delete all the characters in those indices for each string.
//
// For example, if we have strs = ["abcdef","uvwxyz"] and deletion indices {0, 2, 3}, then the final array after deletions is ["bef", "vyz"].
//
// Suppose we chose a set of deletion indices answer such that after deletions, the final array has its elements in lexicographic order (i.e., strs[0] <= strs[1] <= strs[2] <= ... <= strs[n - 1]). Return the minimum possible value of answer.length.
//
// Example:
// Input: strs = ["ca","bb","ac"]
// Output: 1
// Explanation: 
// After deleting the first column, strs = ["a", "b", "c"].
// Now strs is in lexicographic order (ie. strs[0] <= strs[1] <= strs[2]).
// We require at least 1 deletion since initially strs was not in lexicographic order, so the answer is 1.
//
// Constraints:
// n == strs.length
// 	1 <= n <= 100
// 	1 <= strs[i].length <= 100
// 	strs[i] consists of lowercase English letters.
//

int minDeletionSize(char** strs, int strsSize) {
    int m = strlen(strs[0]);
    int deleteCount = 0;
    int sorted[100] = {0}; // Tracks if pairs are confirmed sorted

    for (int col = 0; col < m; col++) {
        int needDelete = 0;

        for (int row = 1; row < strsSize; row++) {
            if (!sorted[row - 1] && strs[row][col] < strs[row - 1][col]) {
                needDelete = 1;
                break;
            }
        }

        if (needDelete) {
            deleteCount++;
        } else {
            for (int row = 1; row < strsSize; row++) {
                if (strs[row][col] > strs[row - 1][col]) {
                    sorted[row - 1] = 1; // Mark as sorted
                }
            }
        }
    }

    return deleteCount;     
}
