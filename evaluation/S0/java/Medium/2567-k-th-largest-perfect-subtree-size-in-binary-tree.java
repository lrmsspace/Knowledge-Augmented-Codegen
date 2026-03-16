// Source: https://leetcode.com/problems/k-th-largest-perfect-subtree-size-in-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree and an integer k.
//
// Return an integer denoting the size of the kth largest perfect binary subtree, or -1 if it doesn't exist.
//
// A perfect binary tree is a tree where all leaves are on the same level, and every parent has two children.
//
// Example:
// Input: root = [5,3,6,5,2,5,7,1,8,null,null,6,8], k = 2
//
// Output: 3
//
// Explanation:
//
//
//
// The roots of the perfect binary subtrees are highlighted in black. Their sizes, in non-increasing order are [3, 3, 1, 1, 1, 1, 1, 1].
// The 2nd largest size is 3.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 2000].
// 	1 <= Node.val <= 2000
// 	1 <= k <= 1024
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
    public int kthLargestPerfectSubtree(TreeNode root, int k) {
        List<Integer> perfectSizes = new ArrayList<>();
        computePerfectSubtreeSizes(root, perfectSizes);
        Collections.sort(perfectSizes, Collections.reverseOrder());
        return k <= perfectSizes.size() ? perfectSizes.get(k - 1) : -1;         
    }
}
