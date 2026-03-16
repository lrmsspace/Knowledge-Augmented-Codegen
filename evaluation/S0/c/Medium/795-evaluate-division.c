// Source: https://leetcode.com/problems/evaluate-division/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of variable pairs equations and an array of real numbers values, where equations[i] = [Ai, Bi] and values[i] represent the equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a single variable.
//
// You are also given some queries, where queries[j] = [Cj, Dj] represents the jth query where you must find the answer for Cj / Dj = ?.
//
// Return the answers to all queries. If a single answer cannot be determined, return -1.0.
//
// Note: The input is always valid. You may assume that evaluating the queries will not result in division by zero and that there is no contradiction.
//
// Note: The variables that do not occur in the list of equations are undefined, so the answer cannot be determined for them.
//
// Example:
// Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
// Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
// Explanation: 
// Given: a / b = 2.0, b / c = 3.0
// queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? 
// return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
// note: x is undefined => -1.0
//
// Constraints:
// 1 <= equations.length <= 20
// 	equations[i].length == 2
// 	1 <= Ai.length, Bi.length <= 5
// 	values.length == equations.length
// 	0.0 < values[i] <= 20.0
// 	1 <= queries.length <= 20
// 	queries[i].length == 2
// 	1 <= Cj.length, Dj.length <= 5
// 	Ai, Bi, Cj, Dj consist of lower case English letters and digits.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
double* calcEquation(char*** equations, int equationsSize, int* equationsColSize, double* values, int valuesSize, char*** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    // Graph represented as an adjacency list
    typedef struct Edge {
        int to;
        double weight;
        struct Edge* next;
    } Edge;

    typedef struct Node {
        Edge* edges;
    } Node;

    // Hash map for variable to index mapping
    #define MAX_VARS 40
    char* varNames[MAX_VARS];
    int varCount = 0;

    int getVarIndex(char* var) {
        for (int i = 0; i < varCount; i++) {
            if (strcmp(varNames[i], var) == 0) {
                return i;
            }
        }
        varNames[varCount] = var;
        return varCount++;
    }

    Node graph[MAX_VARS] = {0};

    // Build the graph
    for (int i = 0; i < equationsSize; i++) {
        int u = getVarIndex(equations[i][0]);
        int v = getVarIndex(equations[i][1]);
        double val = values[i];

        Edge* edge1 = (Edge*)malloc(sizeof(Edge));
        edge1->to = v;
        edge1->weight = val;
        edge1->next = graph[u].edges;
        graph[u].edges = edge1;

        Edge* edge2 = (Edge*)malloc(sizeof(Edge));
        edge2->to = u;
        edge2->weight = 1.0 / val;
        edge2->next = graph[v].edges;
        graph[v].edges = edge2;
    }

    double* results = (double*)malloc(sizeof(double) * queriesSize);
    *returnSize = queriesSize;

    // DFS to find the result for each query
    for (int i = 0; i < queriesSize; i++) {
        char* startVar = queries[i][0];
        char* endVar = queries[i][1];
        int start = -1, end = -1;
        for (int j = 0; j < varCount; j++) {
            if (strcmp(varNames[j], startVar) == 0) start = j;
            if (strcmp(varNames[j], endVar) == 0) end = j;
        }
        if (start == -1 || end == -1) {
            results[i] = -1.0;
            continue;
        }

        // DFS
        double result = -1.0;
        int visited[MAX_VARS] = {0};

        void dfs(int node, double accProduct) {
            if (node == end) {
                result = accProduct;
                return;
            }
            visited[node] = 1;
            for (Edge* edge = graph[node].edges; edge != NULL; edge = edge->next) {
                if (!visited[edge->to]) {
                    dfs(edge->to, accProduct * edge->weight);
                    if (result != -1.0) return; // Early exit if result found
                }
            }
            visited[node] = 0;
        }

        dfs(start, 1.0);
        results[i] = result;
    }
    return results;
}
