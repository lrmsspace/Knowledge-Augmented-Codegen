// Source: https://leetcode.com/problems/remove-methods-from-project/   |   Difficulty: Medium
//
// Problem Description:
// You are maintaining a project that has n methods numbered from 0 to n - 1.
//
// You are given two integers n and k, and a 2D integer array invocations, where invocations[i] = [ai, bi] indicates that method ai invokes method bi.
//
// There is a known bug in method k. Method k, along with any method invoked by it, either directly or indirectly, are considered suspicious and we aim to remove them.
//
// A group of methods can only be removed if no method outside the group invokes any methods within it.
//
// Return an array containing all the remaining methods after removing all the suspicious methods. You may return the answer in any order. If it is not possible to remove all the suspicious methods, none should be removed.
//
// Example:
// Input: n = 4, k = 1, invocations = [[1,2],[0,1],[3,2]]
//
// Output: [0,1,2,3]
//
// Explanation:
//
//
//
// Method 2 and method 1 are suspicious, but they are directly invoked by methods 3 and 0, which are not suspicious. We return all elements without removing anything.
//
// Constraints:
// 1 <= n <= 105
// 	0 <= k <= n - 1
// 	0 <= invocations.length <= 2 * 105
// 	invocations[i] == [ai, bi]
// 	0 <= ai, bi <= n - 1
// 	ai != bi
// 	invocations[i] != invocations[j]
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* remainingMethods(int n, int k, int** invocations, int invocationsSize, int* invocationsColSize, int* returnSize) {
    // Create an adjacency list to represent the graph
    int* graph[n];
    int graphSize[n];
    memset(graphSize, 0, sizeof(graphSize));
    
    for (int i = 0; i < invocationsSize; i++) {
        int a = invocations[i][0];
        int b = invocations[i][1];
        graph[a] = realloc(graph[a], sizeof(int) * (graphSize[a] + 1));
        graph[a][graphSize[a]++] = b;
    }
    
    // DFS to find all suspicious methods
    int suspicious[n];
    memset(suspicious, 0, sizeof(suspicious));
    
    void dfs(int method) {
        if (suspicious[method]) return;
        suspicious[method] = 1;
        for (int i = 0; i < graphSize[method]; i++) {
            dfs(graph[method][i]);
        }
    }
    
    dfs(k);
    
    // Check if any non-suspicious method invokes a suspicious method
    for (int i = 0; i < n; i++) {
        if (!suspicious[i]) {
            for (int j = 0; j < graphSize[i]; j++) {
                if (suspicious[graph[i][j]]) {
                    // Found a non-suspicious method invoking a suspicious one
                    *returnSize = n;
                    int* result = malloc(sizeof(int) * n);
                    for (int x = 0; x < n; x++) {
                        result[x] = x;
                    }
                    return result;
                }
            }
        }
    }
    
    // Collect remaining methods
    int* result = malloc(sizeof(int) * n);
    int idx = 0;
    for (int i = 0; i < n; i++) {
        if (!suspicious[i]) {
            result[idx++] = i;
        }
    }
    
    *returnSize = idx;
    return result;      
}
