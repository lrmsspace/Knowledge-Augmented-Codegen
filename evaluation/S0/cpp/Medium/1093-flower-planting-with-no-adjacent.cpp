// Source: https://leetcode.com/problems/flower-planting-with-no-adjacent/   |   Difficulty: Medium
//
// Problem Description:
// You have n gardens, labeled from 1 to n, and an array paths where paths[i] = [xi, yi] describes a bidirectional path between garden xi to garden yi. In each garden, you want to plant one of 4 types of flowers.
//
// All gardens have at most 3 paths coming into or leaving it.
//
// Your task is to choose a flower type for each garden such that, for any two gardens connected by a path, they have different types of flowers.
//
// Return any such a choice as an array answer, where answer[i] is the type of flower planted in the (i+1)th garden. The flower types are denoted 1, 2, 3, or 4. It is guaranteed an answer exists.
//
// Example:
// Input: n = 3, paths = [[1,2],[2,3],[3,1]]
// Output: [1,2,3]
// Explanation:
// Gardens 1 and 2 have different types.
// Gardens 2 and 3 have different types.
// Gardens 3 and 1 have different types.
// Hence, [1,2,3] is a valid answer. Other valid answers include [1,2,4], [1,4,2], and [3,2,1].
//
// Constraints:
// 1 <= n <= 104
// 	0 <= paths.length <= 2 * 104
// 	paths[i].length == 2
// 	1 <= xi, yi <= n
// 	xi != yi
// 	Every garden has at most 3 paths coming into or leaving it.
//

class Solution {
public:
    vector<int> gardenNoAdj(int n, vector<vector<int>>& paths) {
        vector<vector<int>> graph(n);
        for (const auto& path : paths) {
            graph[path[0] - 1].push_back(path[1] - 1);
            graph[path[1] - 1].push_back(path[0] - 1);
        }

        vector<int> result(n, 0);
        for (int garden = 0; garden < n; ++garden) {
            vector<bool> used(5, false); // Flower types 1 to 4
            for (int neighbor : graph[garden]) {
                if (result[neighbor] != 0) {
                    used[result[neighbor]] = true;
                }
            }
            for (int flowerType = 1; flowerType <= 4; ++flowerType) {
                if (!used[flowerType]) {
                    result[garden] = flowerType;
                    break;
                }
            }
        }

        return result;          
    }
};
