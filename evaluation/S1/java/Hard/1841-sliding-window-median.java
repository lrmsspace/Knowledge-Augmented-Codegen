// Source: https://leetcode.com/problems/sliding-window-median/   |   Difficulty: Hard
//
// Problem Description:
// The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle values.
//
//
// 	For examples, if arr = [2,3,4], the median is 3.
// 	For examples, if arr = [1,2,3,4], the median is (2 + 3) / 2 = 2.5.
//
//
// You are given an integer array nums and an integer k. There is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
//
// Return the median array for each window in the original array. Answers within 10-5 of the actual value will be accepted.
//
// Example:
// Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
// Output: [1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
// Explanation: 
// Window position                Median
// ---------------                -----
// [1  3  -1] -3  5  3  6  7        1
//  1 [3  -1  -3] 5  3  6  7       -1
//  1  3 [-1  -3  5] 3  6  7       -1
//  1  3  -1 [-3  5  3] 6  7        3
//  1  3  -1  -3 [5  3  6] 7        5
//  1  3  -1  -3  5 [3  6  7]       6
//
// Constraints:
// 1 <= k <= nums.length <= 105
// 	-231 <= nums[i] <= 231 - 1
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Sqrt Decomposition (array, ds, sliding-window, two-pointers)
//   • When to use: Use when performing frequent range queries and point updates on an array, especially when a segment tree is too complex or memory-intensive, or when query types are diverse. It offers a balanced time complexity for both operations.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and point updates. It achieves O(sqrt(N)) time complexity for both operations.
//   • Invariants: Each element `arr[i]` belongs to exactly one block `block[i / block_size]`.; The summary for each block `block_summary[j]` accurately reflects the state of elements within block `j`.
//   • Tips: Choose block size carefully, typically sqrt(N) for balanced performance.; Precompute block summaries (e.g., sum, min, max) for efficient queries.
//   • Pitfalls: Off-by-one errors when calculating block indices or boundaries.; Forgetting to update the block's summary after a point update.
// - Minimum Spanning Trees (graph, heap, mst-kruskal)
//   • When to use: Use Kruskal's algorithm to find a subset of edges that connects all vertices in an edge-weighted graph with the minimum possible total edge weight. It is suitable for sparse graphs or when edges are easily sorted.
//   • Idea: Kruskal's algorithm is a greedy algorithm that builds a Minimum Spanning Tree (MST) by iteratively adding the cheapest available edge that does not form a cycle. It typically runs in O(E log E) time, dominated by sorting edges or Union-Find operations.
//   • Invariants: The set of edges chosen so far forms a forest, where each tree is a component of the MST.; All edges considered so far that do not form a cycle are part of the current forest.
//   • Tips: Sort all edges by their weights in non-decreasing order before processing.; Utilize a Union-Find data structure to efficiently track connected components and detect cycles.
//   • Pitfalls: Incorrectly implementing Union-Find can lead to performance bottlenecks or incorrect cycle detection.; Failing to sort edges correctly will result in a non-minimal spanning tree.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public double[] medianSlidingWindow(int[] nums, int k) {
        // Two Heaps approach
        PriorityQueue<Long> lowers = new PriorityQueue<>(Collections.reverseOrder());
        PriorityQueue<Long> highers = new PriorityQueue<>();

        double[] medians = new double[nums.length - k + 1];

        for (int i = 0; i < nums.length; i++) {
            addNumber(lowers, highers, (long) nums[i]);
            rebalanceHeaps(lowers, highers);

            if (i >= k - 1) {
                medians[i - k + 1] = getMedian(lowers, highers);
                long elementToRemove = (long) nums[i - k + 1];
                removeNumber(lowers, highers, elementToRemove);
                rebalanceHeaps(lowers, highers);
            }
        }

        return medians;         
    }
}
