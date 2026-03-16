// Source: https://leetcode.com/problems/minimum-total-cost-to-make-arrays-unequal/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed integer arrays nums1 and nums2, of equal length n.
//
// In one operation, you can swap the values of any two indices of nums1. The cost of this operation is the sum of the indices.
//
// Find the minimum total cost of performing the given operation any number of times such that nums1[i] != nums2[i] for all 0 <= i <= n - 1 after performing all the operations.
//
// Return the minimum total cost such that nums1 and nums2 satisfy the above condition. In case it is not possible, return -1.
//
// Example:
// Input: nums1 = [1,2,3,4,5], nums2 = [1,2,3,4,5]
// Output: 10
// Explanation: 
// One of the ways we can perform the operations is:
// - Swap values at indices 0 and 3, incurring cost = 0 + 3 = 3. Now, nums1 = [4,2,3,1,5]
// - Swap values at indices 1 and 2, incurring cost = 1 + 2 = 3. Now, nums1 = [4,3,2,1,5].
// - Swap values at indices 0 and 4, incurring cost = 0 + 4 = 4. Now, nums1 =[5,3,2,1,4].
// We can see that for each index i, nums1[i] != nums2[i]. The cost required here is 10.
// Note that there are other ways to swap values, but it can be proven that it is not possible to obtain a cost less than 10.
//
// Constraints:
// n == nums1.length == nums2.length
//  1 <= n <= 105
//  1 <= nums1[i], nums2[i] <= n
//
// Helpful references (internal KB):
// - Hungarian algorithm for solving the assignment problem (matrix, graph, array, greedy, bfs, enumeration)
//   • When to use: Use when finding a minimum cost perfect matching in a bipartite graph, typically represented as an N x N cost matrix, where each row must be assigned to exactly one column.
//   • Idea: The Hungarian algorithm finds a minimum weight perfect matching in a bipartite graph, solving the assignment problem for an N x N cost matrix. It iteratively finds augmenting paths in an equality graph and adjusts potentials, achieving O(N^3) time complexity.
//   • Invariants: For all i, j, u[i] + v[j] <= A[i][j] (potential condition).; The current matching is always valid (each row/column used at most once).
//   • Tips: Understand the concept of potentials and their role in maintaining the equality graph.; The algorithm can be adapted for maximum profit problems by negating costs.
//   • Pitfalls: Incorrectly updating potentials can lead to non-optimal solutions or infinite loops.; Handling non-square matrices requires careful padding with dummy values.
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long minimumTotalCost(int[] nums1, int[] nums2) {
        int n = nums1.length;
        long totalCost = 0;
        Map<Integer, Integer> countMap = new HashMap<>();
        List<Integer> conflictIndices = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            if (nums1[i] == nums2[i]) {
                conflictIndices.add(i);
                countMap.put(nums1[i], countMap.getOrDefault(nums1[i], 0) + 1);
            }
        }

        int maxCount = 0;
        int maxNum = -1;
        for (Map.Entry<Integer, Integer> entry : countMap.entrySet()) {
            if (entry.getValue() > maxCount) {
                maxCount = entry.getValue();
                maxNum = entry.getKey();
            }
        }

        int swapsNeeded = 0;
        if (maxCount > (conflictIndices.size() + 1) / 2) {
            swapsNeeded = 2 * maxCount - conflictIndices.size() - 1;
        }

        for (int i = 0; i < n && swapsNeeded > 0; i++) {
            if (nums1[i] != nums2[i] && nums1[i] != maxNum && nums2[i] != maxNum) {
                totalCost += i;
                swapsNeeded--;
            }
        }

        if (swapsNeeded > 0) {
            return -1;
        }

        for (int index : conflictIndices) {
            totalCost += index;
        }

        return totalCost;           
    }
}
