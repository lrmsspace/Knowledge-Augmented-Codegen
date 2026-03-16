// Source: https://leetcode.com/problems/number-of-ways-to-reconstruct-a-tree/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array pairs, where pairs[i] = [xi, yi], and:
//
//
// 	There are no duplicates.
// 	xi < yi
//
//
// Let ways be the number of rooted trees that satisfy the following conditions:
//
//
// 	The tree consists of nodes whose values appeared in pairs.
// 	A pair [xi, yi] exists in pairs if and only if xi is an ancestor of yi or yi is an ancestor of xi.
// 	Note: the tree does not have to be a binary tree.
//
//
// Two ways are considered to be different if there is at least one node that has different parents in both ways.
//
// Return:
//
//
// 	0 if ways == 0
// 	1 if ways == 1
// 	2 if ways > 1
//
//
// A rooted tree is a tree that has a single root node, and all edges are oriented to be outgoing from the root.
//
// An ancestor of a node is any node on the path from the root to that node (excluding the node itself). The root has no ancestors.
//
// Example:
// Input: pairs = [[1,2],[2,3]]
// Output: 1
// Explanation: There is exactly one valid rooted tree, which is shown in the above figure.
//
// Constraints:
// 1 <= pairs.length <= 105
// 	1 <= xi < yi <= 500
// 	The elements in pairs are unique.
//

class Solution {
    public int checkWays(int[][] pairs) {
        Map<Integer, Set<Integer>> graph = new HashMap<>();
        Set<Integer> nodes = new HashSet<>();

        for (int[] pair : pairs) {
            graph.putIfAbsent(pair[0], new HashSet<>());
            graph.putIfAbsent(pair[1], new HashSet<>());

            graph.get(pair[0]).add(pair[1]);
            graph.get(pair[1]).add(pair[0]);

            nodes.add(pair[0]);
            nodes.add(pair[1]);
        }

        int n = nodes.size();
        Integer root = null;

        for (Integer node : nodes) {
            if (graph.get(node).size() == n - 1) {
                root = node;
                break;
            }
        }

        if (root == null) {
            return 0;
        }

        int result = 1;

        for (Integer node : nodes) {
            if (node.equals(root)) {
                continue;
            }

            int parent = -1;
            int parentDegree = Integer.MAX_VALUE;

            for (Integer neighbor : graph.get(node)) {
                int degree = graph.get(neighbor).size();

                if (degree >= graph.get(node).size() && degree < parentDegree) {
                    parentDegree = degree;
                    parent = neighbor;
                }
            }

            if (parent == -1) {
                return 0;
            }

            for (Integer neighbor : graph.get(node)) {
                if (neighbor.equals(parent)) {
                    continue;
                }

                if (!graph.get(parent).contains(neighbor)) {
                    return 0;
                }
            }

            if (parentDegree == graph.get(node).size()) {
                result = 2;
            }
        }

        return result;          
    }
}
