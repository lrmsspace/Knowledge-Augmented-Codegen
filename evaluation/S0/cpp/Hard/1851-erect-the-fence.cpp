// Source: https://leetcode.com/problems/erect-the-fence/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array trees where trees[i] = [xi, yi] represents the location of a tree in the garden.
//
// Fence the entire garden using the minimum length of rope, as it is expensive. The garden is well-fenced only if all the trees are enclosed.
//
// Return the coordinates of trees that are exactly located on the fence perimeter. You may return the answer in any order.
//
// Example:
// Input: trees = [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
// Output: [[1,1],[2,0],[4,2],[3,3],[2,4]]
// Explanation: All the trees will be on the perimeter of the fence except the tree at [2, 2], which will be inside the fence.
//
// Constraints:
// 1 <= trees.length <= 3000
// 	trees[i].length == 2
// 	0 <= xi, yi <= 100
// 	All the given positions are unique.
//

class Solution {
public:
    vector<vector<int>> outerTrees(vector<vector<int>>& trees) {
        int n = trees.size();
        if (n <= 3) return trees;
        
        // Find the leftmost point
        int leftmost = 0;
        for (int i = 1; i < n; i++) {
            if (trees[i][0] < trees[leftmost][0]) {
                leftmost = i;
            }
        }
        
        vector<bool> onHull(n, false);
        int p = leftmost;
        
        do {
            int q = (p + 1) % n;
            for (int r = 0; r < n; r++) {
                int cross = (trees[q][0] - trees[p][0]) * (trees[r][1] - trees[p][1]) -
                            (trees[q][1] - trees[p][1]) * (trees[r][0] - trees[p][0]);
                if (cross < 0) {
                    q = r;
                }
            }
            
            // Check for collinear points
            for (int r = 0; r < n; r++) {
                if (r != p && r != q) {
                    int cross = (trees[q][0] - trees[p][0]) * (trees[r][1] - trees[p][1]) -
                                (trees[q][1] - trees[p][1]) * (trees[r][0] - trees[p][0]);
                    if (cross == 0) {
                        onHull[r] = true;
                    }
                }
            }
            
            onHull[q] = true;
            p = q;
        } while (p != leftmost);
        
        vector<vector<int>> result;
        for (int i = 0; i < n; i++) {
            if (onHull[i]) {
                result.push_back(trees[i]);
            }
        }
        
        return result;          
    }
};
