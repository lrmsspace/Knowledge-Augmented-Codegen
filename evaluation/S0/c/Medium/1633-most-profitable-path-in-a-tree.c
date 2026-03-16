// Source: https://leetcode.com/problems/most-profitable-path-in-a-tree/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 0 to n - 1, rooted at node 0. You are given a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// At every node i, there is a gate. You are also given an array of even integers amount, where amount[i] represents:
//
//
// 	the price needed to open the gate at node i, if amount[i] is negative, or,
// 	the cash reward obtained on opening the gate at node i, otherwise.
//
//
// The game goes on as follows:
//
//
// 	Initially, Alice is at node 0 and Bob is at node bob.
// 	At every second, Alice and Bob each move to an adjacent node. Alice moves towards some leaf node, while Bob moves towards node 0.
// 	For every node along their path, Alice and Bob either spend money to open the gate at that node, or accept the reward. Note that:
// 	
// 		If the gate is already open, no price will be required, nor will there be any cash reward.
// 		If Alice and Bob reach the node simultaneously, they share the price/reward for opening the gate there. In other words, if the price to open the gate is c, then both Alice and Bob pay c / 2 each. Similarly, if the reward at the gate is c, both of them receive c / 2 each.
// 	
// 	
// 	If Alice reaches a leaf node, she stops moving. Similarly, if Bob reaches node 0, he stops moving. Note that these events are independent of each other.
//
//
// Return the maximum net income Alice can have if she travels towards the optimal leaf node.
//
// Example:
// Input: edges = [[0,1],[1,2],[1,3],[3,4]], bob = 3, amount = [-2,4,2,-4,6]
// Output: 6
// Explanation: 
// The above diagram represents the given tree. The game goes as follows:
// - Alice is initially on node 0, Bob on node 3. They open the gates of their respective nodes.
//   Alice's net income is now -2.
// - Both Alice and Bob move to node 1. 
//   Since they reach here simultaneously, they open the gate together and share the reward.
//   Alice's net income becomes -2 + (4 / 2) = 0.
// - Alice moves on to node 3. Since Bob already opened its gate, Alice's income remains unchanged.
//   Bob moves on to node 0, and stops moving.
// - Alice moves on to node 4 and opens the gate there. Her net income becomes 0 + 6 = 6.
// Now, neither Alice nor Bob can make any further moves, and the game ends.
// It is not possible for Alice to get a higher net income.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	edges represents a valid tree.
// 	1 <= bob < n
// 	amount.length == n
// 	amount[i] is an even integer in the range [-104, 104].
//

int mostProfitablePath(int** edges, int edgesSize, int* edgesColSize, int bob, int* amount, int amountSize) {
    // Build the tree as an adjacency list
    int n = amountSize;
    int** graph = (int**)malloc(n * sizeof(int*));
    int* graphColSize = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        graph[i] = (int*)malloc(n * sizeof(int));
    }
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        graph[u][graphColSize[u]++] = v;
        graph[v][graphColSize[v]++] = u;
    }

    // Find Bob's path to the root
    int* parent = (int*)calloc(n, sizeof(int));
    int* visited = (int*)calloc(n, sizeof(int));
    void dfs_parent(int node, int par) {
        visited[node] = 1;
        parent[node] = par;
        for (int i = 0; i < graphColSize[node]; i++) {
            int neighbor = graph[node][i];
            if (!visited[neighbor]) {
                dfs_parent(neighbor, node);
            }
        }
    }
    dfs_parent(0, -1);

    int* bobPathTime = (int*)calloc(n, sizeof(int));
    int time = 0;
    while (bob != -1) {
        bobPathTime[bob] = time++;
        bob = parent[bob];
    }

    // DFS to find the most profitable path for Alice
    int maxProfit = INT_MIN;
    void dfs_alice(int node, int time, int currentProfit) {
        visited[node] = 1;

        // Calculate profit at this node
        if (bobPathTime[node] == 0) {
            currentProfit += amount[node];
        } else if (bobPathTime[node] > time) {
            currentProfit += amount[node];
        } else if (bobPathTime[node] == time) {
            currentProfit += amount[node] / 2;
        }

        // If leaf node, update max profit
        if (graphColSize[node] == 1 && node != 0) {
            if (currentProfit > maxProfit) {
                maxProfit = currentProfit;
            }
        }

        // Continue DFS
        for (int i = 0; i < graphColSize[node]; i++) {
            int neighbor = graph[node][i];
            if (!visited[neighbor]) {
                dfs_alice(neighbor, time + 1, currentProfit);
            }
        }
        visited[node] = 0; // backtrack
    }
    memset(visited, 0, n * sizeof(int));
    dfs_alice(0, 0, 0);
    return maxProfit;
}
