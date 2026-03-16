// Source: https://leetcode.com/problems/distant-barcodes/   |   Difficulty: Medium
//
// Problem Description:
// In a warehouse, there is a row of barcodes, where the ith barcode is barcodes[i].
//
// Rearrange the barcodes so that no two adjacent barcodes are equal. You may return any answer, and it is guaranteed an answer exists.
//
// Example:
// Input: barcodes = [1,1,1,2,2,2]
// Output: [2,1,2,1,2,1]
//
// Constraints:
// 1 <= barcodes.length <= 10000
// 	1 <= barcodes[i] <= 10000
//
// Helpful references (internal KB):
// - Priority Queues (heap, stack, heap-select)
//   • When to use: Use when you need to efficiently retrieve the element with the highest (or lowest) priority from a collection, especially when elements are added or removed frequently.
//   • Idea: A priority queue is a data structure that allows efficient retrieval of the element with the highest or lowest priority, and efficient insertion of new elements. Operations typically run in logarithmic time, O(log N).
//   • Invariants: The priority queue maintains the heap property: parent nodes are always greater than/equal to (or less than/equal to) their children.; For a K-selection problem, the priority queue contains at most K elements, representing the K largest/smallest seen so far.
//   • Tips: Use a min-priority queue to find the K largest elements by keeping at most K elements.; Use a max-priority queue to find the K smallest elements by keeping at most K elements.
//   • Pitfalls: Confusing min-priority queue with max-priority queue for the desired extremum.; Inefficient underlying implementation leading to O(N) operations instead of O(log N).
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - bucket-sort (array, bucket-sort)
//   • When to use: Use when sorting elements with a known, uniform distribution over a specific range. It is efficient for numbers that are uniformly distributed across a range, often achieving linear time complexity.
//   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually, and then concatenates them. It can achieve O(N+K) average time complexity for uniformly distributed data.
//   • Invariants: After distributing elements, each element `x` is in bucket `floor(N * x)`.; After sorting buckets, every bucket `buckets[i]` contains its elements in sorted order.
//   • Tips: Choose the number of buckets appropriately based on data distribution and range.; Normalize input data to a [0, 1) range for simpler bucket indexing.
//   • Pitfalls: Poor performance with non-uniform data distribution, potentially degrading to O(N^2).; Requires extra space for the buckets, proportional to N+K.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] rearrangeBarcodes(int[] barcodes) {
        // Count frequency of each barcode
        int n = barcodes.length;
        int[] count = new int[10001];
        for (int code : barcodes) {
            count[code]++;
        }

        // Create a max-heap based on barcode frequencies
        PriorityQueue<int[]> maxHeap = new PriorityQueue<>((a, b) -> b[1] - a[1]);
        for (int i = 0; i < count.length; i++) {
            if (count[i] > 0) {
                maxHeap.offer(new int[]{i, count[i]});
            }
        }

        int[] result = new int[n];
        int index = 0;

        // Rearrange barcodes
        while (maxHeap.size() > 1) {
            int[] first = maxHeap.poll();
            int[] second = maxHeap.poll();

            result[index++] = first[0];
            result[index++] = second[0];

            if (--first[1] > 0) {
                maxHeap.offer(first);
            }
            if (--second[1] > 0) {
                maxHeap.offer(second);
            }
        }

        // If there's one barcode left, place it at the end
        if (!maxHeap.isEmpty()) {
            int[] last = maxHeap.poll();
            result[index] = last[0];
        }

        return result;          
    }
}
