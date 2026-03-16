// Source: https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, the value of a target node target, and an integer k, return an array of the values of all nodes that have a distance k from the target node.
//
// You can return the answer in any order.
//
// Example:
// Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
// Output: [7,4,1]
// Explanation: The nodes that are a distance 2 from the target node (with value 5) have values 7, 4, and 1.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 500].
// 	0 <= Node.val <= 500
// 	All the values Node.val are unique.
// 	target is the value of one of the nodes in the tree.
// 	0 <= k <= 1000
//

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
class Solution {
    public List<Integer> distanceK(TreeNode root, TreeNode target, int k) {
        Map<TreeNode, TreeNode> parentMap = new HashMap<>();
        buildParentMap(root, null, parentMap);

        List<Integer> result = new ArrayList<>();
        Set<TreeNode> visited = new HashSet<>();
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(target);
        visited.add(target);
        int currentDistance = 0;

        while (!queue.isEmpty()) {
            int size = queue.size();
            if (currentDistance == k) {
                for (int i = 0; i < size; i++) {
                    result.add(queue.poll().val);
                }
                return result;
            }
            for (int i = 0; i < size; i++) {
                TreeNode currentNode = queue.poll();
                for (TreeNode neighbor : getNeighbors(currentNode, parentMap)) {
                    if (neighbor != null && !visited.contains(neighbor)) {
                        visited.add(neighbor);
                        queue.offer(neighbor);
                    }
                }
            }
            currentDistance++;
        }

        return result;          
    }
}
