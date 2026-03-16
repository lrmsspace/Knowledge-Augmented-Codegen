// Source: https://leetcode.com/problems/take-gifts-from-the-richest-pile/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array gifts denoting the number of gifts in various piles. Every second, you do the following:
//
//
// 	Choose the pile with the maximum number of gifts.
// 	If there is more than one pile with the maximum number of gifts, choose any.
// 	Reduce the number of gifts in the pile to the floor of the square root of the original number of gifts in the pile.
//
//
// Return the number of gifts remaining after k seconds.
//
// Example:
// Input: gifts = [25,64,9,4,100], k = 4
// Output: 29
// Explanation: 
// The gifts are taken in the following way:
// - In the first second, the last pile is chosen and 10 gifts are left behind.
// - Then the second pile is chosen and 8 gifts are left behind.
// - After that the first pile is chosen and 5 gifts are left behind.
// - Finally, the last pile is chosen again and 3 gifts are left behind.
// The final remaining gifts are [5,8,9,4,3], so the total number of gifts remaining is 29.
//
// Constraints:
// 1 <= gifts.length <= 103
// 	1 <= gifts[i] <= 109
// 	1 <= k <= 103
//
// Helpful references (internal KB):
// - Priority Queues (array, heap, heap-select)
//   • When to use: Use when you need to efficiently retrieve the highest or lowest priority item from a dynamic collection. It's ideal for scenarios requiring frequent insertions and extractions of extreme values without full sorting.
//   • Idea: A Priority Queue is an abstract data type that provides efficient retrieval of the maximum or minimum element. It is typically implemented using a binary heap, which stores elements in an array representing a complete binary tree, maintaining the heap-ordered property for O(log N) insertion and deletion.
//   • Invariants: For a max-heap, every parent node's key is greater than or equal to its children's keys.; The heap structure is always a complete binary tree, represented contiguously in an array.
//   • Tips: Represent the complete binary tree using an array, often 1-indexed for simpler parent/child calculations.; Use 'swim' (bottom-up reheapify) after insertion to restore heap order.
//   • Pitfalls: Forgetting to handle 0-indexed vs 1-indexed array representations correctly (parent/child formulas differ).; Violating the heap-ordered property during updates or custom operations.
// - Priority Queues (heap, stack, heap-select)
//   • When to use: Use when you need to efficiently retrieve the element with the highest (or lowest) priority from a collection, especially when elements are added or removed frequently.
//   • Idea: A priority queue is a data structure that allows efficient retrieval of the element with the highest or lowest priority, and efficient insertion of new elements. Operations typically run in logarithmic time, O(log N).
//   • Invariants: The priority queue maintains the heap property: parent nodes are always greater than/equal to (or less than/equal to) their children.; For a K-selection problem, the priority queue contains at most K elements, representing the K largest/smallest seen so far.
//   • Tips: Use a min-priority queue to find the K largest elements by keeping at most K elements.; Use a max-priority queue to find the K smallest elements by keeping at most K elements.
//   • Pitfalls: Confusing min-priority queue with max-priority queue for the desired extremum.; Inefficient underlying implementation leading to O(N) operations instead of O(log N).
// - Priority Queues (array, heap, heap-select)
//   • When to use: Use when an in-place sorting algorithm with O(N log N) worst-case time complexity is required, especially when memory constraints are a concern. It's also applicable for efficiently finding the K largest/smallest elements.
//   • Idea: Heapsort is an in-place comparison-based sorting algorithm that uses a binary heap data structure. It first builds a max-heap from the input array, then repeatedly extracts the maximum element and places it at the end of the array, achieving O(N log N) time complexity.
//   • Invariants: During heap construction, the processed subarray forms a valid heap-ordered complete binary tree.; During sortdown, the elements in `arr[0...i]` form a valid heap, and `arr[i+1...N-1]` contains sorted elements.
//   • Tips: Heap construction can be done in linear time using a bottom-up sink-based approach.; Heapsort is an in-place sorting algorithm, requiring O(1) auxiliary space.
//   • Pitfalls: Heapsort is not a stable sorting algorithm; the relative order of equal elements is not preserved.; Cache performance can be poor due to non-sequential memory access patterns during heap operations.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long pickGifts(int[] gifts, int k) {
        PriorityQueue<Integer> pq = new PriorityQueue<>(Collections.reverseOrder());
        for (int gift : gifts) {
            pq.offer(gift);
        }

        for (int i = 0; i < k; i++) {
            int maxGift = pq.poll();
            int reducedGift = (int) Math.floor(Math.sqrt(maxGift));
            pq.offer(reducedGift);
        }

        long totalGifts = 0;
        while (!pq.isEmpty()) {
            totalGifts += pq.poll();
        }

        return totalGifts;          
    }
}
