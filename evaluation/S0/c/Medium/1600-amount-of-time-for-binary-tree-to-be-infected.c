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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int amountOfTime(struct TreeNode* root, int start) {
    #define MAXN 100005

    typedef struct Edge {
        int to;
        struct Edge* next;
    } Edge;

    Edge* graph[MAXN] = {0};
    int visited[MAXN] = {0};

    // Build the graph from the binary tree
    void buildGraph(struct TreeNode* node, struct TreeNode* parent) {
        if (!node) return;
        int u = node->val;
        if (parent) {
            int v = parent->val;
            Edge* edgeU = (Edge*)malloc(sizeof(Edge));
            edgeU->to = v;
            edgeU->next = graph[u];
            graph[u] = edgeU;

            Edge* edgeV = (Edge*)malloc(sizeof(Edge));
            edgeV->to = u;
            edgeV->next = graph[v];
            graph[v] = edgeV;
        }
        buildGraph(node->left, node);
        buildGraph(node->right, node);
    }

    buildGraph(root, NULL);

    // BFS to find the time to infect the entire tree
    int queue[MAXN];
    int front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = 1;
    int time = -1;

    while (front < rear) {
        int size = rear - front;
        time++;
        for (int i = 0; i < size; i++) {
            int u = queue[front++];
            Edge* curr = graph[u];
            while (curr) {
                int v = curr->to;
                if (!visited[v]) {
                    visited[v] = 1;
                    queue[rear++] = v;
                }
                curr = curr->next;
            }
        }
    }

    return time;
            
}
