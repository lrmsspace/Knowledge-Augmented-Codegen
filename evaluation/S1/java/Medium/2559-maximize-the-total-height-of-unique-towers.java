// Source: https://leetcode.com/problems/maximize-the-total-height-of-unique-towers/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array maximumHeight, where maximumHeight[i] denotes the maximum height the ith tower can be assigned.
//
// Your task is to assign a height to each tower so that:
//
//
// 	The height of the ith tower is a positive integer and does not exceed maximumHeight[i].
// 	No two towers have the same height.
//
//
// Return the maximum possible total sum of the tower heights. If it's not possible to assign heights, return -1.
//
// Example:
// Input: maximumHeight = [2,3,4,3]
//
// Output: 10
//
// Explanation:
//
// We can assign heights in the following way: [1, 2, 4, 3].
//
// Constraints:
// 1 <= maximumHeight.length <= 105
// 	1 <= maximumHeight[i] <= 109
//
// Helpful references (internal KB):
// - Disjoint Set Union (ds, tree, array, union-find)
//   • When to use: Use when you need to maintain a collection of disjoint sets and efficiently perform union operations to merge sets or find the representative of an element's set.
//   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. With path compression and union by rank/size, these operations achieve nearly constant amortized time complexity, O(alpha(N)).
//   • Invariants: Each element `v` is either a root (parent[v] == v) or has a parent pointer to another element in its set.; The `find_set` operation, after path compression, ensures that all nodes on the path from `v` to its root directly point to the root.
//   • Tips: Implement path compression in `find_set` for optimal performance.; Use union by rank or union by size to keep trees flat and balanced.
//   • Pitfalls: Forgetting path compression or union by rank/size leads to O(N) worst-case operations.; Incorrectly merging sets by only updating one root without considering the other's rank/size.
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long maximumTotalSum(int[] maximumHeight) {
        java.util.Arrays.sort(maximumHeight);
        long totalSum = 0;
        long currentHeight = (long) maximumHeight[maximumHeight.length - 1] + 1;

        for (int i = maximumHeight.length - 1; i >= 0; i--) {
            if (currentHeight > 1) {
                currentHeight = Math.min(currentHeight - 1, maximumHeight[i]);
                totalSum += currentHeight;
            } else {
                return -1;
            }
        }

        return totalSum;            
    }
}
