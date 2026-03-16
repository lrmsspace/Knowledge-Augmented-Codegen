// Source: https://leetcode.com/problems/loud-and-rich/   |   Difficulty: Medium
//
// Problem Description:
// There is a group of n people labeled from 0 to n - 1 where each person has a different amount of money and a different level of quietness.
//
// You are given an array richer where richer[i] = [ai, bi] indicates that ai has more money than bi and an integer array quiet where quiet[i] is the quietness of the ith person. All the given data in richer are logically correct (i.e., the data will not lead you to a situation where x is richer than y and y is richer than x at the same time).
//
// Return an integer array answer where answer[x] = y if y is the least quiet person (that is, the person y with the smallest value of quiet[y]) among all people who definitely have equal to or more money than the person x.
//
// Example:
// Input: richer = [[1,0],[2,1],[3,1],[3,7],[4,3],[5,3],[6,3]], quiet = [3,2,5,4,6,1,7,0]
// Output: [5,5,2,5,4,5,6,7]
// Explanation: 
// answer[0] = 5.
// Person 5 has more money than 3, which has more money than 1, which has more money than 0.
// The only person who is quieter (has lower quiet[x]) is person 7, but it is not clear if they have more money than person 0.
// answer[7] = 7.
// Among all people that definitely have equal to or more money than person 7 (which could be persons 3, 4, 5, 6, or 7), the person who is the quietest (has lower quiet[x]) is person 7.
// The other answers can be filled out with similar reasoning.
//
// Constraints:
// n == quiet.length
// 	1 <= n <= 500
// 	0 <= quiet[i] < n
// 	All the values of quiet are unique.
// 	0 <= richer.length <= n * (n - 1) / 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	All the pairs of richer are unique.
// 	The observations in richer are all logically consistent.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* loudAndRich(int** richer, int richerSize, int* richerColSize, int* quiet, int quietSize, int* returnSize) {
    int n = quietSize;
    int* answer = (int*)malloc(n * sizeof(int));
    int** graph = (int**)malloc(n * sizeof(int*));
    int* graphColSize = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        graph[i] = (int*)malloc(n * sizeof(int));
    }
    
    for (int i = 0; i < richerSize; i++) {
        int u = richer[i][0];
        int v = richer[i][1];
        graph[u][graphColSize[u]++] = v;
    }
    
    int* visited = (int*)calloc(n, sizeof(int));
    
    void dfs(int u) {
        visited[u] = 1;
        for (int i = 0; i < graphColSize[u]; i++) {
            int v = graph[u][i];
            if (!visited[v]) {
                dfs(v);
            }
            if (quiet[answer[v]] < quiet[answer[u]]) {
                answer[u] = answer[v];
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        answer[i] = i;
    }
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    
    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(graphColSize);
    free(visited);
    
    *returnSize = n;
    return answer;      
}
