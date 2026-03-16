// Source: https://leetcode.com/problems/check-if-dfs-strings-are-palindromes/   |   Difficulty: Hard
//
// Problem Description:
// You are given a tree rooted at node 0, consisting of n nodes numbered from 0 to n - 1. The tree is represented by an array parent of size n, where parent[i] is the parent of node i. Since node 0 is the root, parent[0] == -1.
//
// You are also given a string s of length n, where s[i] is the character assigned to node i.
//
// Consider an empty string dfsStr, and define a recursive function dfs(int x) that takes a node x as a parameter and performs the following steps in order:
//
//
// 	Iterate over each child y of x in increasing order of their numbers, and call dfs(y).
// 	Add the character s[x] to the end of the string dfsStr.
//
//
// Note that dfsStr is shared across all recursive calls of dfs.
//
// You need to find a boolean array answer of size n, where for each index i from 0 to n - 1, you do the following:
//
//
// 	Empty the string dfsStr and call dfs(i).
// 	If the resulting string dfsStr is a palindrome, then set answer[i] to true. Otherwise, set answer[i] to false.
//
//
// Return the array answer.
//
// Example:
// Input: parent = [-1,0,0,1,1,2], s = "aababa"
//
// Output: [true,true,false,true,true,true]
//
// Explanation:
//
//
// 	Calling dfs(0) results in the string dfsStr = "abaaba", which is a palindrome.
// 	Calling dfs(1) results in the string dfsStr = "aba", which is a palindrome.
// 	Calling dfs(2) results in the string dfsStr = "ab", which is not a palindrome.
// 	Calling dfs(3) results in the string dfsStr = "a", which is a palindrome.
// 	Calling dfs(4) results in the string dfsStr = "b", which is a palindrome.
// 	Calling dfs(5) results in the string dfsStr = "a", which is a palindrome.
//
// Constraints:
// n == parent.length == s.length
// 	1 <= n <= 105
// 	0 <= parent[i] <= n - 1 for all i >= 1.
// 	parent[0] == -1
// 	parent represents a valid tree.
// 	s consists only of lowercase English letters.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* findAnswer(int* parent, int parentSize, char* s, int* returnSize) {
    if (!returnSize || parentSize <= 0 || !parent || !s) return NULL;

    int n = parentSize;
    bool *answer = (bool*)malloc(n * sizeof(bool));
    if (!answer) return NULL;

    /* build adjacency list */
    int *childCounts = (int*)calloc(n, sizeof(int));
    if (!childCounts) { free(answer); return NULL; }
    for (int i = 1; i < n; ++i) {
        childCounts[parent[i]]++;
    }
    int **children = (int**)malloc(n * sizeof(int*));
    if (!children) { free(answer); free(childCounts); return NULL; }
    for (int i = 0; i < n; ++i) {
        if (childCounts[i] > 0) {
            children[i] = (int*)malloc(childCounts[i] * sizeof(int));
            if (!children[i]) {
                for (int j = 0; j < i; ++j) free(children[j]);
                free(children); free(childCounts); free(answer);
                return NULL;
            }
            childCounts[i] = 0; /* reuse for indexing */
        } else {
            children[i] = NULL;
        }
    }
    for (int i = 1; i < n; ++i) {
        int p = parent[i];
        children[p][childCounts[p]++] = i;
    }

    /* DFS function to build dfsStr and check palindrome */
    char *dfsStr = (char*)malloc(n * sizeof(char));
    if (!dfsStr) {
        for (int i = 0; i < n; ++i) free(children[i]);
        free(children); free(childCounts); free(answer);
        return NULL;
    }

    void dfs(int node, int *len) {
        for (int i = 0; i < childCounts[node]; ++i) {
            dfs(children[node][i], len);
        }
        dfsStr[(*len)++] = s[node];
    }

    for (int i = 0; i < n; ++i) {
        int len = 0;
        dfs(i, &len);
        /* Check if dfsStr is palindrome */
        bool isPalindrome = true;
        for (int j = 0; j < len / 2; ++j) {
            if (dfsStr[j] != dfsStr[len - 1 - j]) {
                isPalindrome = false;
                break;
            }
        }
        answer[i] = isPalindrome;
    }
    free(dfsStr);
    for (int i = 0; i < n; ++i) free(children[i]);
    free(children);
    free(childCounts);
    *returnSize = n;
    return answer;
}
