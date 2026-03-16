// Source: https://leetcode.com/problems/longest-cycle-in-a-graph/   |   Difficulty: Hard
//
// Problem Description:
// You are given a directed graph of n nodes numbered from 0 to n - 1, where each node has at most one outgoing edge.
//
// The graph is represented with a given 0-indexed array edges of size n, indicating that there is a directed edge from node i to node edges[i]. If there is no outgoing edge from node i, then edges[i] == -1.
//
// Return the length of the longest cycle in the graph. If no cycle exists, return -1.
//
// A cycle is a path that starts and ends at the same node.
//
// Example:
// Input: edges = [3,3,4,2,3]
// Output: 3
// Explanation: The longest cycle in the graph is the cycle: 2 -> 4 -> 3 -> 2.
// The length of this cycle is 3, so 3 is returned.
//
// Constraints:
// n == edges.length
// 	2 <= n <= 105
// 	-1 <= edges[i] < n
// 	edges[i] != i
//

class Solution {
public:
    int longestCycle(vector<int>& edges) {
        int n = edges.size();
        vector<int> visited(n, 0);  // 0: unvisited, 1: visiting, 2: visited
        int longest = -1;
        
        for (int i = 0; i < n; i++) {
            if (visited[i] != 0) continue;
            
            unordered_map<int, int> nodeToIndex;
            int index = 0;
            int current = i;
            
            while (current != -1) {
                if (visited[current] == 2) {
                    // Already fully processed
                    break;
                }
                if (visited[current] == 1) {
                    // Cycle detected
                    if (nodeToIndex.find(current) != nodeToIndex.end()) {
                        int cycleLength = index - nodeToIndex[current];
                        longest = max(longest, cycleLength);
                    }
                    break;
                }
                
                // Mark as visiting
                visited[current] = 1;
                nodeToIndex[current] = index++;
                
                current = edges[current];
            }
            
            // Mark all nodes in the current path as visited
            current = i;
            while (current != -1 && visited[current] == 1) {
                visited[current] = 2;
                current = edges[current];
            }
        }
        
        return longest;         
    }
};
