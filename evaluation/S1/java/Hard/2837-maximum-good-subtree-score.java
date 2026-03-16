// Source: https://leetcode.com/problems/maximum-good-subtree-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1. Each node i has an integer value vals[i], and its parent is given by par[i].
//
// A subset of nodes within the subtree of a node is called good if every digit from 0 to 9 appears at most once in the decimal representation of the values of the selected nodes.
//
// The score of a good subset is the sum of the values of its nodes.
//
// Define an array maxScore of length n, where maxScore[u] represents the maximum possible sum of values of a good subset of nodes that belong to the subtree rooted at node u, including u itself and all its descendants.
//
// Return the sum of all values in maxScore.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: vals = [2,3], par = [-1,0]
//
// Output: 8
//
// Explanation:
//
//
//
//
// 	The subtree rooted at node 0 includes nodes {0, 1}. The subset {2, 3} is good as the digits 2 and 3 appear only once. The score of this subset is 2 + 3 = 5.
// 	The subtree rooted at node 1 includes only node {1}. The subset {3} is good. The score of this subset is 3.
// 	The maxScore array is [5, 3], and the sum of all values in maxScore is 5 + 3 = 8. Thus, the answer is 8.
//
// Constraints:
// 1 <= n == vals.length <= 500
// 	1 <= vals[i] <= 109
// 	par.length == n
// 	par[0] == -1
// 	0 <= par[i] < n for i in [1, n - 1]
// 	The input is generated such that the parent array par represents a valid tree.
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int goodSubtreeSum(int[] vals, int[] par) {
        int n = vals.length;
        List<List<Integer>> tree = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            tree.add(new ArrayList<>());
        }
        for (int i = 1; i < n; i++) {
            tree.get(par[i]).add(i);
        }

        int MOD = (int)1e9 + 7;
        long result = 0;
        for (int i = 0; i < n; i++) {
            int[][] dp = new int[1 << 10][n];
            for (int[] row : dp) {
                Arrays.fill(row, -1);
            }
            result = (result + dfs(i, vals, tree, dp, (1 << 10) - 1)) % MOD;
        }
        return (int)result;         
    }
}
