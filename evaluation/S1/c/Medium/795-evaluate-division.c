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
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - 0-1 BFS (graph, deque, 01-bfs, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently computes single-source shortest paths, outperforming Dijkstra's for this specific weight constraint.
//   • Idea: 0-1 BFS is a graph traversal algorithm that finds the single-source shortest paths in a graph where all edge weights are restricted to 0 or 1. It uses a deque to process nodes, achieving an optimal time complexity of O(V + E).
//   • Invariants: When a node 'u' is extracted from the front of the deque, 'dist[u]' is its shortest path from the source.; The deque always contains nodes whose distances are either 'D' or 'D+1', where 'D' is the distance of the last node extracted.
//   • Tips: Always push 0-weight edges to the front of the deque.; Push 1-weight edges to the back of the deque.
//   • Pitfalls: Pushing 0-weight edges to the back or 1-weight edges to the front of the deque.; Not correctly initializing distances or the source node.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
double* calcEquation(char*** equations, int equationsSize, int* equationsColSize, double* values, int valuesSize, char*** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    // Graph representation using adjacency list
    typedef struct Edge {
        int to;
        double weight;
        struct Edge* next;
    } Edge;

    typedef struct Graph {
        Edge** adj;
        int size;
    } Graph;

    Graph* createGraph(int size) {
        Graph* graph = (Graph*)malloc(sizeof(Graph));
        graph->size = size;
        graph->adj = (Edge**)calloc(size, sizeof(Edge*));
        return graph;
    }

    void addEdge(Graph* graph, int from, int to, double weight) {
        Edge* edge = (Edge*)malloc(sizeof(Edge));
        edge->to = to;
        edge->weight = weight;
        edge->next = graph->adj[from];
        graph->adj[from] = edge;
    }

    void freeGraph(Graph* graph) {
        for (int i = 0; i < graph->size; i++) {
            Edge* edge = graph->adj[i];
            while (edge) {
                Edge* temp = edge;
                edge = edge->next;
                free(temp);
            }
        }
        free(graph->adj);
        free(graph);
    }

    // Hash map for variable to index mapping
    #define HASH_SIZE 1009

    typedef struct HashNode {
        char* key;
        int value;
        struct HashNode* next;
    } HashNode;

    typedef struct HashMap {
        HashNode** table;
    } HashMap;

    unsigned int hash(const char* str) {
        unsigned int hash = 5381;
        int c;
        while ((c = *str++)) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash % HASH_SIZE;
    }

    HashMap* createHashMap() {
        HashMap* map = (HashMap*)malloc(sizeof(HashMap));
        map->table = (HashNode**)calloc(HASH_SIZE, sizeof(HashNode*));
        return map;
    }

    void put(HashMap* map, const char* key, int value) {
        unsigned int h = hash(key);
        HashNode* node = map->table[h];
        while (node) {
            if (strcmp(node->key, key) == 0) {
                node->value = value;
                return;
            }
            node = node->next;
        }
        node = (HashNode*)malloc(sizeof(HashNode));
        node->key = strdup(key);
        node->value = value;
        node->next = map->table[h];
        map->table[h] = node;
    }
    int get(HashMap* map, const char* key) {
        unsigned int h = hash(key);
        HashNode* node = map->table[h];
        while (node) {
            if (strcmp(node->key, key) == 0) {
                return node->value;
            }
            node = node->next;
        }
        return -1; // Not found
    }
    void freeHashMap(HashMap* map) {
        for (int i = 0; i < HASH_SIZE; i++) {
            HashNode* node = map->table[i];
            while (node) {
                HashNode* temp = node;
                node = node->next;
                free(temp->key);
                free(temp);
            }
        }
        free(map->table);
        free(map);
    }
    // Build graph
    HashMap* varToIndex = createHashMap();
    int varCount = 0;
    for (int i = 0; i < equationsSize; i++) {
        char* varA = equations[i][0];
        char* varB = equations[i][1];
        if (get(varToIndex, varA) == -1) {
            put(varToIndex, varA, varCount++);
        }
        if (get(varToIndex, varB) == -1) {
            put(varToIndex, varB, varCount++);
        }
    }
    Graph* graph = createGraph(varCount);
    for (int i = 0; i < equationsSize; i++) {
        char* varA = equations[i][0];
        char* varB = equations[i][1];
        int indexA = get(varToIndex, varA);
        int indexB = get(varToIndex, varB);
        double value = values[i];
        addEdge(graph, indexA, indexB, value);
        addEdge(graph, indexB, indexA, 1.0 / value);
    }
    // Process queries using BFS
    double* results = (double*)malloc(queriesSize * sizeof(double));
    for (int i = 0; i < queriesSize; i++) {
        char* varC = queries[i][0];
        char* varD = queries[i][1];
        int indexC = get(varToIndex, varC);
        int indexD = get(varToIndex, varD);
        if (indexC == -1 || indexD == -1) {
            results[i] = -1.0;
            continue;
        }
        if (indexC == indexD) {
            results[i] = 1.0;
            continue;
        }
        // BFS
        double* dist = (double*)malloc(graph->size * sizeof(double));
        for (int j = 0; j < graph->size; j++) {
            dist[j] = -1.0;
        }
        dist[indexC] = 1.0;
        int* queue = (int*)malloc(graph->size * sizeof(int));
        int front = 0, back = 0;
        queue[back++] = indexC;
        int found = 0;
        while (front < back) {
            int curr = queue[front++];
            Edge* edge = graph->adj[curr];
            while (edge) {
                int neighbor = edge->to;
                if (dist[neighbor] < 0) {
                    dist[neighbor] = dist[curr] * edge->weight;
                    if (neighbor == indexD) {
                        results[i] = dist[neighbor];
                        found = 1;
                        break;
                    }
                    queue[back++] = neighbor;
                }
                edge = edge->next;
            }
            if (found) break;
        }
        if (!found) {
            results[i] = -1.0;
        }
        free(dist);
        free(queue);
    }
    // Cleanup
    freeGraph(graph);
    freeHashMap(varToIndex);
    *returnSize = queriesSize;
    return results;
}
