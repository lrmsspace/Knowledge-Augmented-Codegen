// Source: https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/   |   Difficulty: Hard
//
// Problem Description:
// Given the root of a binary tree, calculate the vertical order traversal of the binary tree.
//
// For each node at position (row, col), its left and right children will be at positions (row + 1, col - 1) and (row + 1, col + 1) respectively. The root of the tree is at (0, 0).
//
// The vertical order traversal of a binary tree is a list of top-to-bottom orderings for each column index starting from the leftmost column and ending on the rightmost column. There may be multiple nodes in the same row and same column. In such a case, sort these nodes by their values.
//
// Return the vertical order traversal of the binary tree.
//
// Example:
// Input: root = [3,9,20,null,null,15,7]
// Output: [[9],[3,15],[20],[7]]
// Explanation:
// Column -1: Only node 9 is in this column.
// Column 0: Nodes 3 and 15 are in this column in that order from top to bottom.
// Column 1: Only node 20 is in this column.
// Column 2: Only node 7 is in this column.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 1000].
// 	0 <= Node.val <= 1000
//

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
    public List<List<Integer>> verticalTraversal(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) {
            return result;
        }

        Map<Integer, List<NodeInfo>> columnTable = new HashMap<>();
        int[] minMax = new int[2]; // minMax[0] = minCol, minMax[1] = maxCol
        minMax[0] = 0;
        minMax[1] = 0;

        dfs(root, 0, 0, columnTable, minMax);

        for (int col = minMax[0]; col <= minMax[1]; col++) {
            List<NodeInfo> nodeList = columnTable.get(col);
            Collections.sort(nodeList, (a, b) -> {
                if (a.row == b.row) {
                    return Integer.compare(a.val, b.val);
                }
                return Integer.compare(a.row, b.row);
            });

            List<Integer> sortedColumn = new ArrayList<>();
            for (NodeInfo nodeInfo : nodeList) {
                sortedColumn.add(nodeInfo.val);
            }
            result.add(sortedColumn);
        }

        return result;                  
    }
}
