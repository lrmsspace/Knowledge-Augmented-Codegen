// Source: https://leetcode.com/problems/minimize-hamming-distance-after-swap-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays, source and target, both of length n. You are also given an array allowedSwaps where each allowedSwaps[i] = [ai, bi] indicates that you are allowed to swap the elements at index ai and index bi (0-indexed) of array source. Note that you can swap elements at a specific pair of indices multiple times and in any order.
//
// The Hamming distance of two arrays of the same length, source and target, is the number of positions where the elements are different. Formally, it is the number of indices i for 0 <= i <= n-1 where source[i] != target[i] (0-indexed).
//
// Return the minimum Hamming distance of source and target after performing any amount of swap operations on array source.
//
// Example:
// Input: source = [1,2,3,4], target = [2,1,4,5], allowedSwaps = [[0,1],[2,3]]
// Output: 1
// Explanation: source can be transformed the following way:
// - Swap indices 0 and 1: source = [2,1,3,4]
// - Swap indices 2 and 3: source = [2,1,4,3]
// The Hamming distance of source and target is 1 as they differ in 1 position: index 3.
//
// Constraints:
// n == source.length == target.length
// 	1 <= n <= 105
// 	1 <= source[i], target[i] <= 105
// 	0 <= allowedSwaps.length <= 105
// 	allowedSwaps[i].length == 2
// 	0 <= ai, bi <= n - 1
// 	ai != bi
//
// Helpful references (internal KB):
// - Range Minimum Query (array, ds, union-find)
//   • When to use: Use when range minimum queries are needed on an array where elements can be dynamically removed or merged, and Union-Find is employed to manage the active state or connectivity of indices.
//   • Idea: Union-Find can be adapted to assist in range minimum queries, particularly when elements are dynamically removed or merged. It helps maintain connectivity of active elements or segments, allowing efficient traversal to find the minimum among available items, often with near-constant amortized time per Union-Find operation.
//   • Invariants: The `find` operation correctly returns the canonical representative for any element `i`.; Each set in the Union-Find structure maintains a property (e.g., minimum value, next available index) relevant to its merged elements.
//   • Tips: Utilize path compression and union by rank/size for optimal Union-Find performance.; Store relevant properties (e.g., minimum value, next available index) within the representative of each set.
//   • Pitfalls: Union-Find alone does not directly provide range minimums; it typically manages connectivity or availability.; Naive iteration through active elements found by Union-Find can be too slow for large ranges.
// - Search for connected components in a graph (graph, dfs, bfs, enumeration)
//   • When to use: Use when you need to partition an undirected graph into maximal connected subgraphs where every node is reachable from every other node within its subgraph.
//   • Idea: This algorithm identifies all connected components in an undirected graph by iteratively performing graph traversals (DFS or BFS) from unvisited nodes. It has a time complexity of O(V + E) for adjacency list representation.
//   • Invariants: All nodes visited so far belong to an identified connected component.; Any node currently being visited is part of the current connected component being explored.
//   • Tips: Maintain a visited array or set to track processed nodes.; Iterate through all nodes, starting a new traversal if a node is unvisited.
//   • Pitfalls: Failing to iterate through all nodes to find all components in a disconnected graph.; Not correctly marking nodes as visited during traversal, leading to infinite loops or re-processing.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumHammingDistance(int* source, int sourceSize, int* target, int targetSize, int** allowedSwaps, int allowedSwapsSize, int* allowedSwapsColSize) {
    typedef struct {
        int parent;
        int rank;
    } UnionFind;

    UnionFind* uf = (UnionFind*)malloc(sourceSize * sizeof(UnionFind));
    for (int i = 0; i < sourceSize; i++) {
        uf[i].parent = i;
        uf[i].rank = 0;
    }

    // Find function with path compression
    int find(UnionFind* uf, int x) {
        if (uf[x].parent != x) {
            uf[x].parent = find(uf, uf[x].parent);
        }
        return uf[x].parent;
    }

    // Union function with union by rank
    void unionSets(UnionFind* uf, int x, int y) {
        int rootX = find(uf, x);
        int rootY = find(uf, y);
        if (rootX != rootY) {
            if (uf[rootX].rank < uf[rootY].rank) {
                uf[rootX].parent = rootY;
            } else if (uf[rootX].rank > uf[rootY].rank) {
                uf[rootY].parent = rootX;
            } else {
                uf[rootY].parent = rootX;
                uf[rootX].rank++;
            }
        }
    }

    // Perform unions based on allowed swaps
    for (int i = 0; i < allowedSwapsSize; i++) {
        unionSets(uf, allowedSwaps[i][0], allowedSwaps[i][1]);
    }

    // Map from root to frequency map of source values
    #include <stdlib.h>
    #include <string.h>

    typedef struct Node {
        int key;
        int count;
        struct Node* next;
    } Node;

    typedef struct HashMap {
        Node** buckets;
        int size;
    } HashMap;

    HashMap* createHashMap(int size) {
        HashMap* map = (HashMap*)malloc(sizeof(HashMap));
        map->buckets = (Node**)calloc(size, sizeof(Node*));
        map->size = size;
        return map;
    }

    void put(HashMap* map, int key) {
        int index = key % map->size;
        Node* curr = map->buckets[index];
        while (curr) {
            if (curr->key == key) {
                curr->count++;
                return;
            }
            curr = curr->next;
        }
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key;
        newNode->count = 1;
        newNode->next = map->buckets[index];
        map->buckets[index] = newNode;
    }
    int getCount(HashMap* map, int key) {
        int index = key % map->size;
        Node* curr = map->buckets[index];
        while (curr) {
            if (curr->key == key) {
                return curr->count;
            }
            curr = curr->next;
        }
        return 0;
    }
    void decrement(HashMap* map, int key) {
        int index = key % map->size;
        Node* curr = map->buckets[index];
        while (curr) {
            if (curr->key == key) {
                curr->count--;
                return;
            }
            curr = curr->next;
        }
    }
    void freeHashMap(HashMap* map) {
        for (int i = 0; i < map->size; i++) {
            Node* curr = map->buckets[i];
            while (curr) {
                Node* temp = curr;
                curr = curr->next;
                free(temp);
            }
        }
        free(map->buckets);
        free(map);
    }
    HashMap** groupMaps = (HashMap**)malloc(sourceSize * sizeof(HashMap*));
    for (int i = 0; i < sourceSize; i++) {
        int root = find(uf, i);
        if (!groupMaps[root]) {
            groupMaps[root] = createHashMap(97); // A small prime number for hash map size
        }
        put(groupMaps[root], source[i]);
    }
    int hammingDistance = 0;
    for (int i = 0; i < targetSize; i++) {
        int root = find(uf, i);
        if (groupMaps[root]) {
            int count = getCount(groupMaps[root], target[i]);
            if (count > 0) {
                decrement(groupMaps[root], target[i]);
            } else {
                hammingDistance++;
            }
        } else {
            hammingDistance++;
        }
    }
    // Free resources
    for (int i = 0; i < sourceSize; i++) {
        if (groupMaps[i]) {
            freeHashMap(groupMaps[i]);
        }
    }
    free(groupMaps);
    free(uf);
    return hammingDistance;
}
