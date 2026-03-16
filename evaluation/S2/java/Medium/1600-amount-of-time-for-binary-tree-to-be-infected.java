// Source: https://leetcode.com/problems/amount-of-time-for-binary-tree-to-be-infected/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree with unique values, and an integer start. At minute 0, an infection starts from the node with value start.
//
// Each minute, a node becomes infected if:
//
//
// 	The node is currently uninfected.
// 	The node is adjacent to an infected node.
//
//
// Return the number of minutes needed for the entire tree to be infected.
//
// Example:
// Input: root = [1,5,3,null,4,10,6,9,2], start = 3
// Output: 4
// Explanation: The following nodes are infected during:
// - Minute 0: Node 3
// - Minute 1: Nodes 1, 10 and 6
// - Minute 2: Node 5
// - Minute 3: Node 4
// - Minute 4: Nodes 9 and 2
// It takes 4 minutes for the whole tree to be infected so we return 4.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 105].
// 	1 <= Node.val <= 105
// 	Each node has a unique value.
// 	A node with a value of start exists in the tree.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    public int amountOfTime(TreeNode root, int start) {
        Map<Integer, List<Integer>> graph = new HashMap<>();
        buildGraph(root, graph);

        Queue<Integer> queue = new LinkedList<>();
        Set<Integer> visited = new HashSet<>();

        queue.offer(start);
        visited.add(start);

        int minutes = -1;

        while (!queue.isEmpty()) {
            int size = queue.size();
            minutes++;

            for (int i = 0; i < size; i++) {
                int currentNode = queue.poll();

                for (int neighbor : graph.getOrDefault(currentNode, Collections.emptyList())) {
                    if (!visited.contains(neighbor)) {
                        visited.add(neighbor);
                        queue.offer(neighbor);
                    }
                }
            }
        }

        return minutes;         
    }
}
