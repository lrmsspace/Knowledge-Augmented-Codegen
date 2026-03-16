// Source: https://leetcode.com/problems/word-ladder-ii/   |   Difficulty: Hard
//
// Problem Description:
// A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:
//
//
// 	Every adjacent pair of words differs by a single letter.
// 	Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
// 	sk == endWord
//
//
// Given two words, beginWord and endWord, and a dictionary wordList, return all the shortest transformation sequences from beginWord to endWord, or an empty list if no such sequence exists. Each sequence should be returned as a list of the words [beginWord, s1, s2, ..., sk].
//
// Example:
// Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
// Output: [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]
// Explanation: There are 2 shortest transformation sequences:
// "hit" -> "hot" -> "dot" -> "dog" -> "cog"
// "hit" -> "hot" -> "lot" -> "log" -> "cog"
//
// Constraints:
// 1 <= beginWord.length <= 5
// 	endWord.length == beginWord.length
// 	1 <= wordList.length <= 500
// 	wordList[i].length == beginWord.length
// 	beginWord, endWord, and wordList[i] consist of lowercase English letters.
// 	beginWord != endWord
// 	All the words in wordList are unique.
// 	The sum of all shortest transformation sequences does not exceed 105.
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
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** findLadders(char* beginWord, char* endWord, char** wordList, int wordListSize, int* returnSize, int** returnColumnSizes) {
    int n = 0;
    for (int i = 0; i < wordListSize; i++) {
        if (strcmp(wordList[i], endWord) == 0) {
            n = 1;
            break;
        }
    }
    if (n == 0) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }
    
    // Build adjacency list with dynamic allocation
    Edge** graph = (Edge**)malloc(sizeof(Edge*) * n);
    int* graphSize = (int*)malloc(sizeof(int) * n);
    
    for (int i = 0; i < n; i++) {
        graph[i] = (Edge*)malloc(sizeof(Edge) * (edgesSize * 2));
        graphSize[i] = 0;
    }
    
    // Record which edges have -1 weight
    int negEdges[edgesSize];
    int negCount = 0;
    
    // Add edges to graph, use INF weight for -1 edges initially
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0], v = edges[i][1];
        long long w = (edges[i][2] == -1) ? INF : edges[i][2];
        
        graph[u][graphSize[u]++] = (Edge){v, w};
        graph[v][graphSize[v]++] = (Edge){u, w};
        
        if (edges[i][2] == -1) {
            negEdges[negCount++] = i;
        }
    }
    
    // Try all combinations of -1 edge weights using recursion/backtracking
    // First, assign all -1 edges to 1
    for (int i = 0; i < edgesSize; i++) {
        if (edges[i][2] == -1) {
            edges[i][2] = 1;
        }
    }
    
    // Rebuild graph with weights=1 for -1 edges
    for (int i = 0; i < n; i++) {
        graphSize[i] = 0;
    }
    
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0], v = edges[i][1];
        long long w = edges[i][2];
        
        graph[u][graphSize[u]++] = (Edge){v, w};
        graph[v][graphSize[v]++] = (Edge){u, w};
    }

    long long dist1 = dijkstra(n, source, destination, (int**)graph, graphSize);

    if (dist1 < target) {
        // Impossible
        int** result = (int**)malloc(sizeof(int*));
        *returnSize = 0;
        *returnColumnSizes = (int*)malloc(0);
        
        for (int i = 0; i < n; i++) {
            free(graph[i]);
        }
        free(graph);
        free(graphSize);
        
        return result;
    }

    bool found = false;
    for (int i = 0; i < negCount && !found; i++) {
        int edgeIdx = negEdges[i];
        long long increase = dist1 - target;
        
        // Modify this edge
        long long oldWeight = edges[edgeIdx][2];
        edges[edgeIdx][2] = oldWeight + increase;
        
        // Rebuild graph
        for (int j = 0; j < n; j++) {
            graphSize[j] = 0;
        }
        
        for (int j = 0; j < edgesSize; j++) {
            int u = edges[j][0], v = edges[j][1];
            long long w = edges[j][2];
            
            graph[u][graphSize[u]++] = (Edge){v, w};
            graph[v][graphSize[v]++] = (Edge){u, w};
        }
        
        long long newDist = dijkstra(n, source, destination, (int**)graph, graphSize);
        
        if (newDist == target) {
            found = true;
        } else {
            edges[edgeIdx][2] = oldWeight;
        }
    }
    // Build result
    int** result = (int**)malloc(sizeof(int*) * edgesSize);
    *returnColumnSizes = (int*)malloc(sizeof(int) * edgesSize);
    for (int i = 0; i < edgesSize; i++) {
        result[i] = (int*)malloc(sizeof(int) * 3);
        result[i][0] = edges[i][0];
        result[i][1] = edges[i][1];
        result[i][2] = edges[i][2];
        (*returnColumnSizes)[i] = 3;
    }
    *returnSize = edgesSize;
    return result;
}