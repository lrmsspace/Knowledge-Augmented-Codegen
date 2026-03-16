// Source: https://leetcode.com/problems/time-needed-to-inform-all-employees/   |   Difficulty: Medium
//
// Problem Description:
// A company has n employees with a unique ID for each employee from 0 to n - 1. The head of the company is the one with headID.
//
// Each employee has one direct manager given in the manager array where manager[i] is the direct manager of the i-th employee, manager[headID] = -1. Also, it is guaranteed that the subordination relationships have a tree structure.
//
// The head of the company wants to inform all the company employees of an urgent piece of news. He will inform his direct subordinates, and they will inform their subordinates, and so on until all employees know about the urgent news.
//
// The i-th employee needs informTime[i] minutes to inform all of his direct subordinates (i.e., After informTime[i] minutes, all his direct subordinates can start spreading the news).
//
// Return the number of minutes needed to inform all the employees about the urgent news.
//
// Example:
// Input: n = 1, headID = 0, manager = [-1], informTime = [0]
// Output: 0
// Explanation: The head of the company is the only employee in the company.
//
// Constraints:
// 1 <= n <= 105
// 	0 <= headID < n
// 	manager.length == n
// 	0 <= manager[i] < n
// 	manager[headID] == -1
// 	informTime.length == n
// 	0 <= informTime[i] <= 1000
// 	informTime[i] == 0 if employee i has no subordinates.
// 	It is guaranteed that all the employees can be informed.
//
// Helpful references (internal KB):
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
// - Prüfer code (tree, heap, simulation, greedy)
//   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
//   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
//   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
//   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
//   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
// - Heavy-light decomposition (tree, array, dfs, divide-and-conquer, tree-dp)
//   • When to use: When you need to efficiently perform path queries or updates on a tree, transforming tree paths into linear segments for data structures like segment trees.
//   • Idea: Heavy-light decomposition partitions a tree into disjoint heavy paths, ensuring any root-to-node path crosses at most O(log N) heavy paths. This reduces tree path queries to segment operations, typically achieving O(log^2 N) or O(log N) complexity.
//   • Invariants: Every node is part of exactly one heavy path.; Traversing from any node to the root involves at most O(log N) heavy path switches.
//   • Tips: Precompute subtree sizes for all nodes to identify heavy edges.; Map heavy paths to contiguous array segments for efficient range queries.
//   • Pitfalls: Misidentifying heavy edges or having more than one heavy child per node.; Off-by-one errors when converting tree path segments to array indices.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int numOfMinutes(int n, int headID, int[] manager, int[] informTime) {
        List<List<Integer>> subordinates = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            subordinates.add(new ArrayList<>());
        }
        for (int i = 0; i < n; i++) {
            if (manager[i] != -1) {
                subordinates.get(manager[i]).add(i);
            }
        }
        return dfs(headID, subordinates, informTime);           
    }
}
