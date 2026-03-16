// Source: https://leetcode.com/problems/linked-list-cycle-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a linked list, return the node where the cycle begins. If there is no cycle, return null.
//
// There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to (0-indexed). It is -1 if there is no cycle. Note that pos is not passed as a parameter.
//
// Do not modify the linked list.
//
// Example:
// Input: head = [3,2,0,-4], pos = 1
// Output: tail connects to node index 1
// Explanation: There is a cycle in the linked list, where tail connects to the second node.
//
// Constraints:
// The number of the nodes in the list is in the range [0, 104].
// 	-105 <= Node.val <= 105
// 	pos is -1 or a valid index in the linked-list.
//
//
//  
// Follow up: Can you solve it using O(1) (i.e. constant) memory?
//
// Helpful references (internal KB):
// - Floyd's Linked List Cycle Finding Algorithm (linked-list, two-pointers, simulation)
//   • When to use: Use this algorithm to efficiently detect if a linked list contains a cycle and, optionally, find the entry point of that cycle, using only constant extra space.
//   • Idea: This algorithm uses two pointers, one moving faster than the other, to detect if a cycle exists in a linked list. If a cycle is found, it can then determine the cycle's starting node in O(N) time complexity and O(1) space complexity.
//   • Invariants: The slow and fast pointers are always valid nodes or null.; In the detection phase, the fast pointer always covers twice the distance of the slow pointer.
//   • Tips: Initialize both slow and fast pointers at the head of the list.; Move the slow pointer by one step and the fast pointer by two steps in each iteration.
//   • Pitfalls: Forgetting to check for null on 'fast' and 'fast.next' before dereferencing them.; Incorrectly assuming the list is non-empty or has at least two nodes.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Second Best Minimum Spanning Tree (graph, tree, mst-kruskal, lca, binary-lifting, enumeration)
//   • When to use: When you need to find a spanning tree with the second smallest total edge weight, typically after finding the primary Minimum Spanning Tree.
//   • Idea: This algorithm finds the second best Minimum Spanning Tree by iterating through non-MST edges, adding each to the MST to form a cycle, and then removing the maximum weight edge on that cycle (excluding the added edge). It leverages Kruskal's for the initial MST and LCA with binary lifting for efficient path maximum queries, achieving an overall time complexity of O(E log E + E log V).
//   • Invariants: The initial MST is always a valid spanning tree with minimum total weight.; For any non-MST edge (u, v) added, a unique cycle is formed in the current graph.
//   • Tips: Precompute LCA and maximum edge weights on paths using binary lifting for efficiency.; The initial MST can be found using Kruskal's or Prim's algorithm.
//   • Pitfalls: Incorrectly identifying the maximum weight edge on the cycle when adding a non-MST edge.; Forgetting to exclude the newly added edge itself when finding the maximum edge on the cycle.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for singly-linked list.
 * class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) {
 *         val = x;
 *         next = null;
 *     }
 * }
 */
public class Solution {
    public ListNode detectCycle(ListNode head) {
        if (head == null) {
            return null;
        }

        ListNode slow = head;
        ListNode fast = head;

        // Phase 1: Determine whether a cycle exists
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;

            if (slow == fast) {
                // Cycle detected
                break;
            }
        }

        // If no cycle was detected, return null
        if (fast == null || fast.next == null) {
            return null;
        }

        // Phase 2: Find the entry point of the cycle
        slow = head; // Reset slow to the head

        while (slow != fast) {
            slow = slow.next;
            fast = fast.next;
        }

        // Both pointers meet at the start of the cycle
        return slow;            
    }
}
