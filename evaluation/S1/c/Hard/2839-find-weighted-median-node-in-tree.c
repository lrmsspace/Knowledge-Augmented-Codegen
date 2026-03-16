// Source: https://leetcode.com/problems/find-weighted-median-node-in-tree/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an undirected, weighted tree rooted at node 0 with n nodes numbered from 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates an edge from node ui to vi with weight wi.
//
// The weighted median node is defined as the first node x on the path from ui to vi such that the sum of edge weights from ui to x is greater than or equal to half of the total path weight.
//
// You are given a 2D integer array queries. For each queries[j] = [uj, vj], determine the weighted median node along the path from uj to vj.
//
// Return an array ans, where ans[j] is the node index of the weighted median for queries[j].
//
// Example:
// Input: n = 2, edges = [[0,1,7]], queries = [[1,0],[0,1]]
//
// Output: [0,1]
//
// Explanation:
//
//
//
//
// 	
// 		
// 			Query
// 			Path
// 			Edge
// 			Weights
// 			Total
// 			Path
// 			Weight
// 			Half
// 			Explanation
// 			Answer
// 		
// 	
// 	
// 		
// 			[1, 0]
// 			1 → 0
// 			[7]
// 			7
// 			3.5
// 			Sum from 1 → 0 = 7 >= 3.5, median is node 0.
// 			0
// 		
// 		
// 			[0, 1]
// 			0 → 1
// 			[7]
// 			7
// 			3.5
// 			Sum from 0 → 1 = 7 >= 3.5, median is node 1.
// 			1
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi, wi]
// 	0 <= ui, vi < n
// 	1 <= wi <= 109
// 	1 <= queries.length <= 105
// 	queries[j] == [uj, vj]
// 	0 <= uj, vj < n
// 	The input is generated such that edges represents a valid tree.
//
// Helpful references (internal KB):
// - Lowest Common Ancestor - Binary Lifting (tree, array, binary-lifting, dfs)
//   • When to use: Use binary lifting when you need to answer multiple Lowest Common Ancestor (LCA) queries or ancestor relationship checks efficiently on a static tree.
//   • Idea: Binary lifting precomputes ancestor pointers using DFS to answer Lowest Common Ancestor (LCA) queries and ancestor checks in O(log N) time per query, after O(N log N) preprocessing.
//   • Invariants: For any node `u` and power `k`, `up[u][k]` is the 2^k-th ancestor of `u`.; `depth[u]` correctly represents the distance from the root to node `u`.
//   • Tips: Precompute `up[u][k]` as the 2^k-th ancestor of `u`.; Use DFS to fill the `up` array and node depths.
//   • Pitfalls: Incorrectly calculating `log N` for array dimensions.; Failing to handle the root node's ancestors (e.g., `up[root][k]` should be itself or an invalid node).
// - Minimum spanning tree - Prim's algorithm (graph, mst-prim, greedy)
//   • When to use: Use Prim's algorithm to find a minimum spanning tree in a connected, undirected, weighted graph. It is often preferred for dense graphs due to its O(V^2) or O(E log V) complexity.
//   • Idea: Prim's algorithm is a greedy algorithm that builds a minimum spanning tree by iteratively adding the cheapest edge connecting a vertex in the growing tree to one outside it. It typically runs in O(E log V) time with a binary heap or O(V^2) with an adjacency matrix.
//   • Invariants: The set of vertices already included in the MST forms a connected component.; For any vertex not yet in the MST, its associated key/distance stores the minimum weight of an edge connecting it to a vertex already in the MST.
//   • Tips: Use a priority queue to efficiently retrieve the minimum weight edge connecting to the MST.; Initialize distances for all vertices to infinity, except the starting vertex (0).
//   • Pitfalls: Not suitable for disconnected graphs; it will only find an MST for the component of the starting vertex.; Forgetting to handle edge cases like graphs with no edges or a single vertex.
// - Lowest Common Ancestor (tree, segment-tree)
//   • When to use: Use this approach to efficiently answer multiple Lowest Common Ancestor queries on a static tree. It is suitable when precomputation time is acceptable for faster subsequent queries.
//   • Idea: This method transforms the LCA problem into a Range Minimum Query (RMQ) problem by constructing an Euler tour of the tree. It achieves O(N log N) precomputation and O(log N) query time by building a segment tree over the depths of nodes in the Euler tour.
//   • Invariants: The Euler tour array correctly records nodes in DFS entry and exit order.; The depth array stores the depth of each node as it appears in the Euler tour.
//   • Tips: Perform a DFS to generate an Euler tour of the tree, recording nodes and their depths.; Store the first occurrence index of each node in the Euler tour array.
//   • Pitfalls: Incorrectly constructing the Euler tour or depth array, leading to wrong ranges for RMQ.; Off-by-one errors when mapping node indices to Euler tour indices or defining segment tree query ranges.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

#include <stdlib.h>
#include <string.h>

#define MAX_LOG 17

typedef struct Edge {
    int to;
    long long weight;
    struct Edge* next;
} Edge;

typedef struct {
    Edge** adj;
    int* parent;
    int** up;
    int* depth;
    long long** dist;
    int n;
} Tree;

Edge* createEdge(int to, long long weight) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = to;
    e->weight = weight;
    e->next = NULL;
    return e;
}

void addEdge(Edge** adj, int from, int to, long long weight) {
    Edge* e = createEdge(to, weight);
    e->next = adj[from];
    adj[from] = e;
}

void dfs(Tree* tree, int u, int p, int d, long long dis) {
    tree->parent[u] = p;
    tree->depth[u] = d;
    tree->dist[u][0] = dis;
    
    tree->up[u][0] = p;
    for (int i = 1; i < MAX_LOG; i++) {
        if (tree->up[u][i-1] != -1) {
            tree->up[u][i] = tree->up[tree->up[u][i-1]][i-1];
        } else {
            tree->up[u][i] = -1;
        }
    }
    
    Edge* e = tree->adj[u];
    while (e) {
        if (e->to != p) {
            dfs(tree, e->to, u, d + 1, dis + e->weight);
        }
        e = e->next;
    }
}

int lca(Tree* tree, int u, int v) {
    if (tree->depth[u] < tree->depth[v]) {
        int temp = u;
        u = v;
        v = temp;
    }
    
    int diff = tree->depth[u] - tree->depth[v];
    for (int i = 0; i < MAX_LOG; i++) {
        if ((diff >> i) & 1) {
            u = tree->up[u][i];
        }
    }
    
    if (u == v) return u;
    
    for (int i = MAX_LOG - 1; i >= 0; i--) {
        if (tree->up[u][i] != tree->up[v][i]) {
            u = tree->up[u][i];
            v = tree->up[v][i];
        }
    }
    
    return tree->up[u][0];
}

typedef struct PathNode {
    int node;
    long long distFromStart;
    struct PathNode* next;
} PathNode;

void getPath(Tree* tree, int start, int end, int ancestor, PathNode** path, int* pathLen) {
    *pathLen = 0;
    *path = NULL;
    PathNode* tail = NULL;
    
    int curr = start;
    long long dist = 0;
    while (curr != ancestor) {
        PathNode* pn = (PathNode*)malloc(sizeof(PathNode));
        pn->node = curr;
        pn->distFromStart = dist;
        pn->next = NULL;
        
        if (*path == NULL) {
            *path = pn;
            tail = pn;
        } else {
            tail->next = pn;
            tail = pn;
        }
        (*pathLen)++;
        
        int nextNode = tree->parent[curr];
        Edge* e = tree->adj[curr];
        while (e) {
            if (e->to == nextNode) {
                dist += e->weight;
                break;
            }
            e = e->next;
        }
        curr = nextNode;
    }
    
    PathNode* pn = (PathNode*)malloc(sizeof(PathNode));
    pn->node = ancestor;
    pn->distFromStart = dist;
    pn->next = NULL;
    
    if (*path == NULL) {
        *path = pn;
        tail = pn;
    } else {
        tail->next = pn;
        tail = pn;
    }
    (*pathLen)++;
    
    if (ancestor != end) {
        int* revPath = (int*)malloc(sizeof(int) * tree->n);
        long long* revDist = (long long*)malloc(sizeof(long long) * tree->n);
        int revLen = 0;
        
        curr = end;
        long long distFromEnd = 0;
        while (curr != ancestor) {
            revPath[revLen] = curr;
            revDist[revLen] = distFromEnd;
            revLen++;
            
            int nextNode = tree->parent[curr];
            Edge* e = tree->adj[curr];
            while (e) {
                if (e->to == nextNode) {
                    distFromEnd += e->weight;
                    break;
                }
                e = e->next;
            }
            curr = nextNode;
        }
        
        for (int i = revLen - 1; i >= 0; i--) {
            pn = (PathNode*)malloc(sizeof(PathNode));
            pn->node = revPath[i];
            pn->distFromStart = dist + (distFromEnd - revDist[i]);
            pn->next = NULL;
            tail->next = pn;
            tail = pn;
            (*pathLen)++;
        }
        
        free(revPath);
        free(revDist);
    }
}

void freePath(PathNode* path) {
    while (path) {
        PathNode* temp = path;
        path = path->next;
        free(temp);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findMedian(int n, int** edges, int edgesSize, int* edgesColSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    Tree tree;
    tree.n = n;
    tree.adj = (Edge**)calloc(n, sizeof(Edge*));
    tree.parent = (int*)malloc(n * sizeof(int));
    tree.depth = (int*)malloc(n * sizeof(int));
    tree.dist = (long long**)malloc(n * sizeof(long long*));
    tree.up = (int**)malloc(n * sizeof(int*));
    
    for (int i = 0; i < n; i++) {
        tree.dist[i] = (long long*)malloc(sizeof(long long));
        tree.up[i] = (int*)malloc(MAX_LOG * sizeof(int));
    }
    
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        long long w = edges[i][2];
        addEdge(tree.adj, u, v, w);
        addEdge(tree.adj, v, u, w);
    }
    
    dfs(&tree, 0, -1, 0, 0);
    
    int* result = (int*)malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;
    
    for (int q = 0; q < queriesSize; q++) {
        int u = queries[q][0];
        int v = queries[q][1];
        
        int ancestor = lca(&tree, u, v);
        
        PathNode* path;
        int pathLen;
        getPath(&tree, u, v, ancestor, &path, &pathLen);
        
        PathNode* curr = path;
        long long totalWeight = 0;
        while (curr->next) {
            totalWeight = curr->next->distFromStart;
            curr = curr->next;
        }
        
        long long halfWeight = totalWeight;
        curr = path;
        int medianNode = u;
        while (curr) {
            if (curr->distFromStart * 2 >= halfWeight) {
                medianNode = curr->node;
                break;
            }
            curr = curr->next;
        }
        
        result[q] = medianNode;
        freePath(path);
    }
    
    for (int i = 0; i < n; i++) {
        free(tree.dist[i]);
        free(tree.up[i]);
        Edge* e = tree.adj[i];
        while (e) {
            Edge* temp = e;
            e = e->next;
            free(temp);
        }
    }
    free(tree.adj);
    free(tree.parent);
    free(tree.depth);
    free(tree.dist);
    free(tree.up);
    
    return result;
}