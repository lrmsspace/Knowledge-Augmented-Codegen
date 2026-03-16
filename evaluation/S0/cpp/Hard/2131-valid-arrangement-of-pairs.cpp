// Source: https://leetcode.com/problems/valid-arrangement-of-pairs/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array pairs where pairs[i] = [starti, endi]. An arrangement of pairs is valid if for every index i where 1 <= i < pairs.length, we have endi-1 == starti.
//
// Return any valid arrangement of pairs.
//
// Note: The inputs will be generated such that there exists a valid arrangement of pairs.
//
// Example:
// Input: pairs = [[5,1],[4,5],[11,9],[9,4]]
// Output: [[11,9],[9,4],[4,5],[5,1]]
// Explanation:
// This is a valid arrangement since endi-1 always equals starti.
// end0 = 9 == 9 = start1 
// end1 = 4 == 4 = start2
// end2 = 5 == 5 = start3
//
// Constraints:
// 1 <= pairs.length <= 105
// 	pairs[i].length == 2
// 	0 <= starti, endi <= 109
// 	starti != endi
// 	No two pairs are exactly the same.
// 	There exists a valid arrangement of pairs.
//

class Solution {
public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        unordered_map<int, multiset<int>> graph;
        unordered_map<int, int> outDegree, inDegree;
        
        // Build the graph
        for (const auto& p : pairs) {
            graph[p[0]].insert(p[1]);
            outDegree[p[0]]++;
            inDegree[p[1]]++;
        }
        
        // Find start node for Eulerian path
        int startNode = pairs[0][0];
        for (const auto& [node, outDeg] : outDegree) {
            int inDeg = inDegree[node];
            if (outDeg - inDeg == 1) {
                startNode = node;
                break;
            }
        }
        
        vector<vector<int>> result;
        stack<int> stk;
        stk.push(startNode);
        
        // Hierholzer's algorithm for Eulerian path
        while (!stk.empty()) {
            int node = stk.top();
            if (graph[node].empty()) {
                stk.pop();
                if (!stk.empty()) {
                    result.push_back({stk.top(), node});
                }
            } else {
                int nextNode = *graph[node].begin();
                graph[node].erase(graph[node].begin());
                stk.push(nextNode);
            }
        }
        
        reverse(result.begin(), result.end());
        return result;          
    }
};
