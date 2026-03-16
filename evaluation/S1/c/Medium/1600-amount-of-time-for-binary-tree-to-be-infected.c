// Source: https://leetcode.com/problems/amount-of-time-for-binary-tree-to-be-infected/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree with unique values, and an integer start. At minute 0, an infection starts from the node with value start.
//
// Each minute, a node becomes infected if:
//
//
// 	The node is currently uninfected.
// 	The node is adjacent to an infected node.
//
//
// Return the number of minutes needed for the entire tree to be infected.
//
// Example:
// Input: root = [1,5,3,null,4,10,6,9,2], start = 3
// Output: 4
// Explanation: The following nodes are infected during:
// - Minute 0: Node 3
// - Minute 1: Nodes 1, 10 and 6
// - Minute 2: Node 5
// - Minute 3: Node 4
// - Minute 4: Nodes 9 and 2
// It takes 4 minutes for the whole tree to be infected so we return 4.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 105].
// 	1 <= Node.val <= 105
// 	Each node has a unique value.
// 	A node with a value of start exists in the tree.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - Strong Orientation (graph, tree, dfs)
//   • When to use: Use this when you need to convert an undirected, bridgeless, and connected graph into a strongly connected directed graph, ensuring reachability between any two vertices.
//   • Idea: This algorithm transforms a bridgeless, connected undirected graph into a strongly connected directed graph by performing a Depth-First Search. It orients DFS tree edges away from the root and back edges towards ancestors, achieving strong connectivity in O(V+E) time.
//   • Invariants: All DFS tree edges discovered so far are oriented from parent to child.; All back edges discovered so far are oriented from child to ancestor.
//   • Tips: Verify the input graph is connected and bridgeless before applying the algorithm.; During DFS, mark visited vertices and track parent-child relationships to distinguish edge types.
//   • Pitfalls: Applying to a graph with bridges will result in a non-strongly connected graph.; Incorrectly identifying or orienting back edges can break the strong connectivity property.
// - Lowest Common Ancestor - Binary Lifting (tree, array, dfs, binary-lifting)
//   • When to use: When you need to find the lowest common ancestor of multiple pairs of nodes in a static tree efficiently. It's suitable for scenarios requiring fast query times after initial preprocessing.
//   • Idea: Binary lifting precomputes ancestors at powers of two distances for each node, enabling O(log N) LCA queries after O(N log N) preprocessing. It finds the LCA by lifting nodes to the same depth and then simultaneously upwards.
//   • Invariants: `up[u][j]` stores the `2^j`-th ancestor of node `u`.; For any node `u`, `depth[u]` is its distance from the root.
//   • Tips: Precompute depths of all nodes using DFS from the root.; Initialize `up[u][0]` as the direct parent of `u` for all nodes.
//   • Pitfalls: Incorrectly handling the root's parent or depth calculation.; Off-by-one errors in `logN` calculation for array dimensions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int amountOfTime(struct TreeNode* root, int start) {

    Ctx ctx;
    ctx.buckets = (struct Entry**)calloc(BUCKETS, sizeof(struct Entry*));
    ctx.capacity = 100005;
    ctx.counts = (int*)calloc(ctx.capacity, sizeof(int));
    ctx.firstNode = (struct TreeNode**)calloc(ctx.capacity, sizeof(struct TreeNode*));
    ctx.nextId = 1;
    ctx.results = (struct TreeNode**)malloc(ctx.capacity * sizeof(struct TreeNode*));
    ctx.resCap = ctx.capacity;
    ctx.resSize = 0;

    // Build graph and find start node
    struct TreeNode* startNode = NULL;
    void buildGraph(struct TreeNode* node, struct TreeNode* parent) {
        if (!node) return;
        if (node->val == start) {
            startNode = node;
        }
        if (parent) {
            // Add edge from parent to node
            int h1 = parent->val % BUCKETS;
            struct Entry* e1 = (struct Entry*)malloc(sizeof(struct Entry));
            e1->val = node->val;
            e1->left = -1;
            e1->right = -1;
            e1->id = ctx.nextId++;
            e1->next = ctx.buckets[h1];
            ctx.buckets[h1] = e1;

            // Add edge from node to parent
            int h2 = node->val % BUCKETS;
            struct Entry* e2 = (struct Entry*)malloc(sizeof(struct Entry));
            e2->val = parent->val;
            e2->left = -1;
            e2->right = -1;
            e2->id = ctx.nextId++;
            e2->next = ctx.buckets[h2];
            ctx.buckets[h2] = e2;
        }
        buildGraph(node->left, node);
        buildGraph(node->right, node);
    }
    buildGraph(root, NULL);

    // BFS to find time to infect all nodes
    int time = -1;
    int* visited = (int*)calloc(ctx.capacity, sizeof(int));
    struct TreeNode** queue = (struct TreeNode**)malloc(ctx.capacity * sizeof(struct TreeNode*));
    int front = 0, back = 0;

    queue[back++] = startNode;
    visited[startNode->val] = 1;

    while (front < back) {
        int levelSize = back - front;
        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* current = queue[front++];
            int h = current->val % BUCKETS;
            struct Entry* e = ctx.buckets[h];
            while (e) {
                if (!visited[e->val]) {
                    visited[e->val] = 1;
                    struct TreeNode* neighbor = (struct TreeNode*)malloc(sizeof(struct TreeNode));
                    neighbor->val = e->val;
                    neighbor->left = NULL;
                    neighbor->right = NULL;
                    queue[back++] = neighbor;
                }
                e = e->next;
            }
        }
        time++;
    }
    return time;
            
}
