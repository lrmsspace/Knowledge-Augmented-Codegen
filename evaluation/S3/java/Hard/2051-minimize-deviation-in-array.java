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
// - Second Best Minimum Spanning Tree (graph, array, mst-kruskal, enumeration)
//   • When to use: Use when you need to find a spanning tree with the second smallest total edge weight, often for redundancy or alternative network path planning. It's applicable in scenarios requiring fault tolerance beyond a single optimal solution.
//   • Idea: This algorithm finds a spanning tree with the second minimum total edge weight in a connected, undirected graph. It involves finding the primary MST, then modifying it by replacing one MST edge with a non-MST edge.
//   • Invariants: The primary MST is always a valid spanning tree with minimum total weight.; Adding any non-MST edge (u,v) to the MST creates exactly one cycle.
//   • Tips: First, compute the primary Minimum Spanning Tree (MST) using an algorithm like Kruskal's or Prim's.; For each edge not in the MST, adding it to the MST creates a unique cycle. Find the maximum weight edge on this cycle.
//   • Pitfalls: Naively recomputing an entire MST for each removed edge is inefficient (O(V * E log E)).; Incorrectly identifying the maximum weight edge on the cycle formed by adding a non-MST edge.
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Sqrt Decomposition (array, enumeration, prefix-sum)
//   • When to use: Use when frequent range queries and point/range updates are needed on an array, offering a balanced O(sqrt(N)) time complexity for both operations. It's a good alternative when a segment tree is too complex or overkill.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and updates. It achieves an O(sqrt(N)) time complexity for both query and update operations.
//   • Invariants: Each block maintains an up-to-date aggregate of its elements.; For any query, fully contained blocks are processed using their precomputed aggregates.
//   • Tips: Choose block size carefully, typically sqrt(N) for optimal balance.; Precompute block aggregates (sum, min, max) for efficient queries.
//   • Pitfalls: Incorrectly handling partial blocks or boundary conditions.; Off-by-one errors in block indices or element indices within blocks.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minimumDeviation(int[] nums) {
        // Step 1: Normalize the array by making all elements even
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        int minElement = Integer.MAX_VALUE;

        for (int num : nums) {
            if (num % 2 == 1) {
                num *= 2; // Make odd numbers even
            }
            maxHeap.offer(num);
            minElement = Math.min(minElement, num);
        }

        // Step 2: Calculate the minimum deviation
        int minDeviation = Integer.MAX_VALUE;

        while (!maxHeap.isEmpty()) {
            int maxElement = maxHeap.poll();
            minDeviation = Math.min(minDeviation, maxElement - minElement);

            // If the maximum element is even, we can divide it by 2
            if (maxElement % 2 == 0) {
                int newElement = maxElement / 2;
                maxHeap.offer(newElement);
                minElement = Math.min(minElement, newElement);
            } else {
                // If it's odd, we can't reduce it further
                break;
            }
        }

        return minDeviation;            
    }
}
