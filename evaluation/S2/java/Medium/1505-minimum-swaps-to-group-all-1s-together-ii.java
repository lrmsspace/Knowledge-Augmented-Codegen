// Source: https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/   |   Difficulty: Medium
//
// Problem Description:
// A swap is defined as taking two distinct positions in an array and swapping the values in them.
//
// A circular array is defined as an array where we consider the first element and the last element to be adjacent.
//
// Given a binary circular array nums, return the minimum number of swaps required to group all 1's present in the array together at any location.
//
// Example:
// Input: nums = [0,1,0,1,1,0,0]
// Output: 1
// Explanation: Here are a few of the ways to group all the 1's together:
// [0,0,1,1,1,0,0] using 1 swap.
// [0,1,1,1,0,0,0] using 1 swap.
// [1,1,0,0,0,0,1] using 2 swaps (using the circular property of the array).
// There is no way to group all 1's together with 0 swaps.
// Thus, the minimum number of swaps required is 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	nums[i] is either 0 or 1.
//
// Helpful references (internal KB):
// - 0-1 BFS (graph, array, dijkstra, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
//   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
//   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
//   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
//   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
// - Josephus Problem (number, dp-1d, recursion)
//   • When to use: Used to determine the position of the last remaining person in a circle where every k-th person is eliminated until only one remains. It models sequential removal processes in a circular arrangement.
//   • Idea: The Josephus Problem determines the position of the survivor in a circle of N people, where every K-th person is eliminated. The standard solution uses a recursive relation or dynamic programming, typically achieving O(N) time complexity.
//   • Invariants: The result J(n, k) represents the survivor's original 0-indexed position among n people.; Each recursive step J(n, k) correctly transforms the result from J(n-1, k) based on the k-th elimination.
//   • Tips: Use 0-indexing for a simpler and more elegant recursive formula.; Establish the base case for N=1 (the survivor is always 0 or 1).
//   • Pitfalls: Off-by-one errors when switching between 0-indexing and 1-indexing.; Incorrectly applying the modulo operator, especially with negative results in some languages.
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minSwaps(int[] nums) {
        int totalOnes = 0;
        for (int num : nums) {
            if (num == 1) {
                totalOnes++;
            }
        }

        if (totalOnes == 0 || totalOnes == nums.length) {
            return 0; // No swaps needed if there are no 1's or all are 1's
        }

        int maxOnesInWindow = 0;
        int currentOnesInWindow = 0;

        // Count the number of 1's in the first window of size totalOnes
        for (int i = 0; i < totalOnes; i++) {
            if (nums[i] == 1) {
                currentOnesInWindow++;
            }
        }
        maxOnesInWindow = currentOnesInWindow;

        // Use a sliding window to count the number of 1's in each subsequent window of size totalOnes
        for (int i = totalOnes; i < nums.length + totalOnes; i++) {
            // Remove the leftmost element of the previous window
            if (nums[i - totalOnes] == 1) {
                currentOnesInWindow--;
            }
            // Add the new element to the current window
            if (nums[i % nums.length] == 1) {
                currentOnesInWindow++;
            }
            maxOnesInWindow = Math.max(maxOnesInWindow, currentOnesInWindow);
        }

        return totalOnes - maxOnesInWindow; // Minimum swaps needed         
    }
}
