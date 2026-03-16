// Source: https://leetcode.com/problems/minimize-deviation-in-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums of n positive integers.
//
// You can perform two types of operations on any element of the array any number of times:
//
//
// 	If the element is even, divide it by 2.
//
// 	
// 		For example, if the array is [1,2,3,4], then you can do this operation on the last element, and the array will be [1,2,3,2].
// 	
// 	
// 	If the element is odd, multiply it by 2.
// 	
// 		For example, if the array is [1,2,3,4], then you can do this operation on the first element, and the array will be [2,2,3,4].
// 	
// 	
//
//
// The deviation of the array is the maximum difference between any two elements in the array.
//
// Return the minimum deviation the array can have after performing some number of operations.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: 1
// Explanation: You can transform the array to [1,2,3,2], then to [2,2,3,2], then the deviation will be 3 - 2 = 1.
//
// Constraints:
// n == nums.length
// 	2 <= n <= 5 * 104
// 	1 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Binary Exponentiation by Factoring (number, counting, mod-exp)
//   • When to use: Use when performing modular exponentiation for an odd base modulo a power of two, especially when dealing with specific logarithmic-like functions or inverses in this modulus.
//   • Idea: This technique computes modular exponentiation for an odd base modulo a power of two by factoring the exponent or its inverse into a product of terms like (2^n+1). It leverages bit manipulation to efficiently find this factorization, allowing for O(d) or O(d log d) complexity where d is the exponent of the modulus.
//   • Invariants: During the iterative process to find $x^{-1} \pmod{2^d}$, the current value of $x$ is always odd.; After processing bit $n$, the $n$-th bit of the current $x$ (for $x^{-1}$ calculation) is zero, and lower bits are unchanged.
//   • Tips: Precompute $4L(2^n+1)$ values for efficiency.; Leverage bitwise operations for multiplying by $2^n+1$ (e.g., x = x + (x << n)).
//   • Pitfalls: This method is specific to odd bases and moduli of the form $2^d$; it's not a general modular exponentiation.; Careful handling of negative results from $4L(x^{-1})$ when working with modular arithmetic.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - 0-1 BFS (graph, array, dijkstra, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
//   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
//   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
//   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
//   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minimumDeviation(int[] nums) {
        // Step 1: Normalize the array by making all numbers even
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        int minValue = Integer.MAX_VALUE;

        for (int num : nums) {
            if (num % 2 == 1) {
                num *= 2; // Make odd numbers even
            }
            maxHeap.offer(num);
            minValue = Math.min(minValue, num);
        }

        int minDeviation = Integer.MAX_VALUE;

        // Step 2: Reduce the maximum element until it's odd
        while (!maxHeap.isEmpty()) {
            int maxValue = maxHeap.poll();
            minDeviation = Math.min(minDeviation, maxValue - minValue);

            if (maxValue % 2 == 0) {
                maxValue /= 2; // Reduce the maximum element
                maxHeap.offer(maxValue);
                minValue = Math.min(minValue, maxValue); // Update the minimum value
            } else {
                break; // If the maximum is odd, we can't reduce it further
            }
        }

        return minDeviation;            
    }
}
