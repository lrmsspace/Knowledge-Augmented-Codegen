// Source: https://leetcode.com/problems/make-costs-of-paths-equal-in-a-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n representing the number of nodes in a perfect binary tree consisting of nodes numbered from 1 to n. The root of the tree is node 1 and each node i in the tree has two children where the left child is the node 2 * i and the right child is 2 * i + 1.
//
// Each node in the tree also has a cost represented by a given 0-indexed integer array cost of size n where cost[i] is the cost of node i + 1. You are allowed to increment the cost of any node by 1 any number of times.
//
// Return the minimum number of increments you need to make the cost of paths from the root to each leaf node equal.
//
// Note:
//
//
// 	A perfect binary tree is a tree where each node, except the leaf nodes, has exactly 2 children.
// 	The cost of a path is the sum of costs of nodes in the path.
//
// Example:
// Input: n = 7, cost = [1,5,2,2,3,3,1]
// Output: 6
// Explanation: We can do the following increments:
// - Increase the cost of node 4 one time.
// - Increase the cost of node 3 three times.
// - Increase the cost of node 7 two times.
// Each path from the root to a leaf will have a total cost of 9.
// The total increments we did is 1 + 3 + 2 = 6.
// It can be shown that this is the minimum answer we can achieve.
//
// Constraints:
// 3 <= n <= 105
// 	n + 1 is a power of 2
// 	cost.length == n
// 	1 <= cost[i] <= 104
//

class Solution {
public:
    int minIncrements(int n, vector<int>& cost) {
        int totalIncrements = 0;
        vector<int> pathCosts(n + 1, 0); // 1-indexed for convenience

        // Calculate path costs from leaves to root
        for (int i = n; i >= 1; --i) {
            pathCosts[i] += cost[i - 1];
            if (i > 1) {
                pathCosts[i / 2] += pathCosts[i];
            }
        }

        // The maximum path cost from root to any leaf
        int maxPathCost = 0;
        for (int i = n / 2 + 1; i <= n; ++i) {
            maxPathCost = max(maxPathCost, pathCosts[i]);
        }

        // Calculate total increments needed
        for (int i = n / 2 + 1; i <= n; ++i) {
            totalIncrements += maxPathCost - pathCosts[i];
        }

        return totalIncrements;         
    }
};
