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

class Solution {
public:
    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) {
        int n = amount.size();
        vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        vector<int> parent(n, -1);
        function<void(int, int)> dfsParent = [&](int node, int par) {
            parent[node] = par;
            for (int neighbor : graph[node]) {
                if (neighbor != par) {
                    dfsParent(neighbor, node);
                }
            }
        };
        dfsParent(0, -1);

        vector<int> bobTime(n, -1);
        int time = 0;
        int node = bob;
        while (node != -1) {
            bobTime[node] = time++;
            node = parent[node];
        }

        int maxIncome = INT_MIN;
        function<void(int, int, int)> dfsAlice = [&](int node, int par, int timeAlice) {
            if (bobTime[node] == timeAlice) {
                amount[node] /= 2;
            } else if (bobTime[node] < timeAlice && bobTime[node] != -1) {
                amount[node] = 0;
            }

            if (graph[node].size() == 1 && graph[node][0] == par) { // Leaf node
                maxIncome = max(maxIncome, amount[node]);
                return;
            }

            for (int neighbor : graph[node]) {
                if (neighbor != par) {
                    dfsAlice(neighbor, node, timeAlice + 1);
                }
            }
            amount[node] += accumulate(graph[node].begin(), graph[node].end(),
                                       0, [&](int sum, int neighbor) {
                                           return sum + (neighbor != par ? amount[neighbor] : 0);
                                       });
        };
        dfsAlice(0, -1, 0);

        return maxIncome;           
    }
};
