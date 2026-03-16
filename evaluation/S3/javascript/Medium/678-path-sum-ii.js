// Source: https://leetcode.com/problems/path-sum-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree and an integer targetSum, return all root-to-leaf paths where the sum of the node values in the path equals targetSum. Each path should be returned as a list of the node values, not node references.
//
// A root-to-leaf path is a path starting from the root and ending at any leaf node. A leaf is a node with no children.
//
// Example:
// Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
// Output: [[5,4,11,2],[5,8,4,5]]
// Explanation: There are two paths whose sum equals targetSum:
// 5 + 4 + 11 + 2 = 22
// 5 + 8 + 4 + 5 = 22
//
// Constraints:
// The number of nodes in the tree is in the range [0, 5000].
// 	-1000 <= Node.val <= 1000
// 	-1000 <= targetSum <= 1000
//
// Helpful references (internal KB):
// - Depth-first search (graph, array, stack, dfs)
//   • When to use: Use when you need to explore all reachable vertices from a starting point or systematically visit all nodes in a graph or tree. It's suitable for problems requiring full exploration of a branch before backtracking.
//   • Idea: Depth-first search is an algorithm for traversing or searching tree or graph data structures. It explores as far as possible along each branch before backtracking, typically using a stack (explicit or implicit via recursion).
//   • Invariants: Every node `v` in the graph is either visited or not yet visited.; The recursion stack (or explicit stack) always contains a path from the source node to the current node being explored.
//   • Tips: Use a `visited` array or set to prevent cycles and redundant work.; Recursion is often cleaner for implementation, but iterative DFS with an explicit stack avoids recursion depth limits.
//   • Pitfalls: Stack overflow can occur with deep recursion on large graphs.; Forgetting to mark nodes as visited leads to infinite loops in cyclic graphs.
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {TreeNode} root
 * @param {number} targetSum
 * @return {number[][]}
 */
var pathSum = function(root, targetSum) {
    const result = [];
    
    function dfs(node, currentPath, currentSum) {
        if (!node) return;
        
        currentPath.push(node.val);
        currentSum += node.val;
        
        // Check if it's a leaf node and the path sum equals targetSum
        if (!node.left && !node.right && currentSum === targetSum) {
            result.push([...currentPath]); // Add a copy of the current path to the result
        }
        
        // Continue searching in the left and right subtrees
        dfs(node.left, currentPath, currentSum);
        dfs(node.right, currentPath, currentSum);
        
        // Backtrack: remove the last node from the path and subtract its value from the sum
        currentPath.pop();
    }
    
    dfs(root, [], 0);
    return result;
};
