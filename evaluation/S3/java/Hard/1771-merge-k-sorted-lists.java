// Source: https://leetcode.com/problems/merge-k-sorted-lists/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
//
// Merge all the linked-lists into one sorted linked-list and return it.
//
// Example:
// Input: lists = [[1,4,5],[1,3,4],[2,6]]
// Output: [1,1,2,3,4,4,5,6]
// Explanation: The linked-lists are:
// [
//   1->4->5,
//   1->3->4,
//   2->6
// ]
// merging them into one sorted linked list:
// 1->1->2->3->4->4->5->6
//
// Constraints:
// k == lists.length
// 	0 <= k <= 104
// 	0 <= lists[i].length <= 500
// 	-104 <= lists[i][j] <= 104
// 	lists[i] is sorted in ascending order.
// 	The sum of lists[i].length will not exceed 104.
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
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

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode mergeKLists(ListNode[] lists) {

        if (lists == null || lists.length == 0) {
                return null;
            }
    
            PriorityQueue<ListNode> minHeap = new PriorityQueue<>((a, b) -> a.val - b.val);
    
            // Add the head of each list to the min-heap
            for (ListNode head : lists) {
                if (head != null) {
                    minHeap.offer(head);
                }
            }
    
            ListNode dummy = new ListNode(0);
            ListNode current = dummy;
    
            while (!minHeap.isEmpty()) {
                ListNode node = minHeap.poll();
                current.next = node;
                current = current.next;
    
                if (node.next != null) {
                    minHeap.offer(node.next);
                }
            }
    
            return dummy.next;  
    }
}
