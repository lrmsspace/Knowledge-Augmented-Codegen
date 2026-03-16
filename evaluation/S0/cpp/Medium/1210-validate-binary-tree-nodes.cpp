// Source: https://leetcode.com/problems/validate-binary-tree-nodes/   |   Difficulty: Medium
//
// Problem Description:
// You have n binary tree nodes numbered from 0 to n - 1 where node i has two children leftChild[i] and rightChild[i], return true if and only if all the given nodes form exactly one valid binary tree.
//
// If node i has no left child then leftChild[i] will equal -1, similarly for the right child.
//
// Note that the nodes have no values and that we only use the node numbers in this problem.
//
// Example:
// Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,-1,-1,-1]
// Output: true
//
// Constraints:
// n == leftChild.length == rightChild.length
// 	1 <= n <= 104
// 	-1 <= leftChild[i], rightChild[i] <= n - 1
//

class Solution {
public:
    bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
        vector<int> parentCount(n, 0);

        // Count parents for each node
        for (int i = 0; i < n; ++i) {
            if (leftChild[i] != -1) {
                parentCount[leftChild[i]]++;
                if (parentCount[leftChild[i]] > 1) return false; // More than one parent
            }
            if (rightChild[i] != -1) {
                parentCount[rightChild[i]]++;
                if (parentCount[rightChild[i]] > 1) return false; // More than one parent
            }
        }

        // Find root (node with no parents)
        int rootCount = 0;
        int rootIndex = -1;
        for (int i = 0; i < n; ++i) {
            if (parentCount[i] == 0) {
                rootCount++;
                rootIndex = i;
            }
        }
        if (rootCount != 1) return false; // Must have exactly one root

        // BFS to check connectivity
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(rootIndex);
        visited[rootIndex] = true;
        int visitedCount = 1;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            if (leftChild[node] != -1 && !visited[leftChild[node]]) {
                visited[leftChild[node]] = true;
                visitedCount++;
                q.push(leftChild[node]);
            }
            if (rightChild[node] != -1 && !visited[rightChild[node]]) {
                visited[rightChild[node]] = true;
                visitedCount++;
                q.push(rightChild[node]);
            }
        }

        return visitedCount == n; // All nodes must be visited          
    }
};
