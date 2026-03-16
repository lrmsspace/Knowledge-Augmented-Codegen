// Source: https://leetcode.com/problems/partition-list/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
//
// You should preserve the original relative order of the nodes in each of the two partitions.
//
// Example:
// Input: head = [1,4,3,2,5,2], x = 3
// Output: [1,2,2,4,3,5]
//
// Constraints:
// The number of nodes in the list is in the range [0, 200].
// 	-100 <= Node.val <= 100
// 	-200 <= x <= 200
//
// Helpful references (internal KB):
// - Linked-list implementations of collections (linked-list, ds, simulation)
//   • When to use: When you need dynamic collections that efficiently support insertions and deletions at specific points, or when memory usage needs to be precisely managed without contiguous memory allocation.
//   • Idea: This describes how fundamental data structures like stacks, queues, and bags can be implemented using linked lists, providing dynamic resizing and efficient element manipulation. Operations typically achieve O(1) time complexity for additions and removals at the ends.
//   • Invariants: The head pointer always points to the first element, or is null if the list is empty.; The tail pointer always points to the last element, or is null if the list is empty.
//   • Tips: Use a Node class to encapsulate data and a reference to the next element.; Maintain head and tail pointers for efficient O(1) operations in queues.
//   • Pitfalls: Forgetting to handle edge cases like empty lists or single-element lists.; Introducing 'loitering' by not nullifying references to removed objects, preventing garbage collection.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
//   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
//   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
//   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
//   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
//   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
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
    public ListNode partition(ListNode head, int x) {
        ListNode beforeHead = new ListNode(0);
        ListNode before = beforeHead;
        ListNode afterHead = new ListNode(0);
        ListNode after = afterHead;

        while (head != null) {
            if (head.val < x) {
                before.next = head;
                before = before.next;
            } else {
                after.next = head;
                after = after.next;
            }
            head = head.next;
        }

        after.next = null; // Important to avoid cycle in linked list
        before.next = afterHead.next;

        return beforeHead.next;         
    }
}
