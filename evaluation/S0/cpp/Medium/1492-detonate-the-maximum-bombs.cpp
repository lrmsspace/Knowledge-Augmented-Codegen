// Source: https://leetcode.com/problems/detonate-the-maximum-bombs/   |   Difficulty: Medium
//
// Problem Description:
// You are given a list of bombs. The range of a bomb is defined as the area where its effect can be felt. This area is in the shape of a circle with the center as the location of the bomb.
//
// The bombs are represented by a 0-indexed 2D integer array bombs where bombs[i] = [xi, yi, ri]. xi and yi denote the X-coordinate and Y-coordinate of the location of the ith bomb, whereas ri denotes the radius of its range.
//
// You may choose to detonate a single bomb. When a bomb is detonated, it will detonate all bombs that lie in its range. These bombs will further detonate the bombs that lie in their ranges.
//
// Given the list of bombs, return the maximum number of bombs that can be detonated if you are allowed to detonate only one bomb.
//
// Example:
// Input: bombs = [[2,1,3],[6,1,4]]
// Output: 2
// Explanation:
// The above figure shows the positions and ranges of the 2 bombs.
// If we detonate the left bomb, the right bomb will not be affected.
// But if we detonate the right bomb, both bombs will be detonated.
// So the maximum bombs that can be detonated is max(1, 2) = 2.
//
// Constraints:
// 1 <= bombs.length <= 100
// 	bombs[i].length == 3
// 	1 <= xi, yi, ri <= 105
//

class Solution {
public:
    int maximumDetonation(vector<vector<int>>& bombs) {
        int n = bombs.size();
        vector<vector<int>> graph(n);

        // Build the graph
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    long long dx = bombs[i][0] - bombs[j][0];
                    long long dy = bombs[i][1] - bombs[j][1];
                    long long r = bombs[i][2];
                    if (dx * dx + dy * dy <= r * r) {
                        graph[i].push_back(j);
                    }
                }
            }
        }

        // Function to perform DFS and count detonated bombs
        function<int(int, vector<bool>&)> dfs = [&](int node, vector<bool>& visited) {
            visited[node] = true;
            int count = 1;
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    count += dfs(neighbor, visited);
                }
            }
            return count;
        };

        int maxDetonated = 0;
        for (int i = 0; i < n; ++i) {
            vector<bool> visited(n, false);
            int detonatedCount = dfs(i, visited);
            maxDetonated = max(maxDetonated, detonatedCount);
        }

        return maxDetonated;            
    }
};
