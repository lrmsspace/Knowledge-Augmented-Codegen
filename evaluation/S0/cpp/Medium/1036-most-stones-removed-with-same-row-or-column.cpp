// Source: https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/   |   Difficulty: Medium
//
// Problem Description:
// On a 2D plane, we place n stones at some integer coordinate points. Each coordinate point may have at most one stone.
//
// A stone can be removed if it shares either the same row or the same column as another stone that has not been removed.
//
// Given an array stones of length n where stones[i] = [xi, yi] represents the location of the ith stone, return the largest possible number of stones that can be removed.
//
// Example:
// Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
// Output: 5
// Explanation: One way to remove 5 stones is as follows:
// 1. Remove stone [2,2] because it shares the same row as [2,1].
// 2. Remove stone [2,1] because it shares the same column as [0,1].
// 3. Remove stone [1,2] because it shares the same row as [1,0].
// 4. Remove stone [1,0] because it shares the same column as [0,0].
// 5. Remove stone [0,1] because it shares the same row as [0,0].
// Stone [0,0] cannot be removed since it does not share a row/column with another stone still on the plane.
//
// Constraints:
// 1 <= stones.length <= 1000
// 	0 <= xi, yi <= 104
// 	No two stones are at the same coordinate point.
//

class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        vector<int> parent(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }

        function<int(int)> find = [&](int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };

        auto unite = [&](int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX != rootY) {
                parent[rootY] = rootX;
            }
        };

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1]) {
                    unite(i, j);
                }
            }
        }

        unordered_set<int> uniqueRoots;
        for (int i = 0; i < n; ++i) {
            uniqueRoots.insert(find(i));
        }

        return n - uniqueRoots.size();          
    }
};
