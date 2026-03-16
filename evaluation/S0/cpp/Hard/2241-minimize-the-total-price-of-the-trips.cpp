// Source: https://leetcode.com/problems/minimize-the-total-price-of-the-trips/   |   Difficulty: Hard
//
// Problem Description:
// There exists an undirected and unrooted tree with n nodes indexed from 0 to n - 1. You are given the integer n and a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// Each node has an associated price. You are given an integer array price, where price[i] is the price of the ith node.
//
// The price sum of a given path is the sum of the prices of all nodes lying on that path.
//
// Additionally, you are given a 2D integer array trips, where trips[i] = [starti, endi] indicates that you start the ith trip from the node starti and travel to the node endi by any path you like.
//
// Before performing your first trip, you can choose some non-adjacent nodes and halve the prices.
//
// Return the minimum total price sum to perform all the given trips.
//
// Example:
// Input: n = 4, edges = [[0,1],[1,2],[1,3]], price = [2,2,10,6], trips = [[0,3],[2,1],[2,3]]
// Output: 23
// Explanation: The diagram above denotes the tree after rooting it at node 2. The first part shows the initial tree and the second part shows the tree after choosing nodes 0, 2, and 3, and making their price half.
// For the 1st trip, we choose path [0,1,3]. The price sum of that path is 1 + 2 + 3 = 6.
// For the 2nd trip, we choose path [2,1]. The price sum of that path is 2 + 5 = 7.
// For the 3rd trip, we choose path [2,1,3]. The price sum of that path is 5 + 2 + 3 = 10.
// The total price sum of all trips is 6 + 7 + 10 = 23.
// It can be proven, that 23 is the minimum answer that we can achieve.
//
// Constraints:
// 1 <= n <= 50
// 	edges.length == n - 1
// 	0 <= ai, bi <= n - 1
// 	edges represents a valid tree.
// 	price.length == n
// 	price[i] is an even integer.
// 	1 <= price[i] <= 1000
// 	1 <= trips.length <= 100
// 	0 <= starti, endi <= n - 1
//

class Solution {
public:
    int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
        vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        vector<int> freq(n, 0);
        
        function<bool(int, int, int)> dfs = [&](int node, int target, int parent) {
            if (node == target) {
                freq[node]++;
                return true;
            }
            for (int neighbor : graph[node]) {
                if (neighbor == parent) continue;
                if (dfs(neighbor, target, node)) {
                    freq[node]++;
                    return true;
                }
            }
            return false;
        };
        
        for (const auto& trip : trips) {
            dfs(trip[0], trip[1], -1);
        }
        
        vector<vector<int>> dp(n, vector<int>(2, 0));
        
        function<void(int, int)> treeDP = [&](int node, int parent) {
            dp[node][0] = freq[node] * price[node];
            dp[node][1] = freq[node] * (price[node] / 2);
            
            for (int neighbor : graph[node]) {
                if (neighbor == parent) continue;
                treeDP(neighbor, node);
                
                dp[node][0] += min(dp[neighbor][0], dp[neighbor][1]);
                dp[node][1] += dp[neighbor][0];
            }
        };
        
        treeDP(0, -1);
        
        return min(dp[0][0], dp[0][1]);         
    }
};
