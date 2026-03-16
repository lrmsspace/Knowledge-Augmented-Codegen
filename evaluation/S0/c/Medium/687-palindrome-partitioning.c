// Source: https://leetcode.com/problems/palindrome-partitioning/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.
//
// Example:
// Input: s = "aab"
// Output: [["a","a","b"],["aa","b"]]
//
// Constraints:
// 1 <= s.length <= 16
// 	s contains only lowercase English letters.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** partition(char* s, int* returnSize, int** returnColumnSizes) {
    int n = strlen(s);
    int maxPartitions = 1 << n; // Maximum possible partitions
    char*** result = malloc(maxPartitions * sizeof(char**));
    *returnColumnSizes = malloc(maxPartitions * sizeof(int));
    *returnSize = 0;

    // Helper function to check if a substring is a palindrome
    int isPalindrome(char* str, int left, int right) {
        while (left < right) {
            if (str[left++] != str[right--]) return 0;
        }
        return 1;
    }

    // Backtracking function to find all partitions
    void backtrack(int start, char** path, int pathSize) {
        if (start == n) {
            result[*returnSize] = malloc(pathSize * sizeof(char*));
            for (int i = 0; i < pathSize; i++) {
                result[*returnSize][i] = strdup(path[i]);
            }
            (*returnColumnSizes)[*returnSize] = pathSize;
            (*returnSize)++;
            return;
        }

        for (int end = start; end < n; end++) {
            if (isPalindrome(s, start, end)) {
                char* substr = strndup(s + start, end - start + 1);
                path[pathSize] = substr;
                backtrack(end + 1, path, pathSize + 1);
                free(substr);
            }
        }
    }

    char** path = malloc(n * sizeof(char*));
    backtrack(0, path, 0);
    free(path);

    return result;      
}
