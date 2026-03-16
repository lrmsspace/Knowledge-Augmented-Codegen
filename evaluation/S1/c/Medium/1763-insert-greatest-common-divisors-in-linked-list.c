// Source: https://leetcode.com/problems/insert-greatest-common-divisors-in-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a linked list head, in which each node contains an integer value.
//
// Between every pair of adjacent nodes, insert a new node with a value equal to the greatest common divisor of them.
//
// Return the linked list after insertion.
//
// The greatest common divisor of two numbers is the largest positive integer that evenly divides both numbers.
//
// Example:
// Input: head = [18,6,10,3]
// Output: [18,6,6,2,10,1,3]
// Explanation: The 1st diagram denotes the initial linked list and the 2nd diagram denotes the linked list after inserting the new nodes (nodes in blue are the inserted nodes).
// - We insert the greatest common divisor of 18 and 6 = 6 between the 1st and the 2nd nodes.
// - We insert the greatest common divisor of 6 and 10 = 2 between the 2nd and the 3rd nodes.
// - We insert the greatest common divisor of 10 and 3 = 1 between the 3rd and the 4th nodes.
// There are no more adjacent nodes, so we return the linked list.
//
// Constraints:
// The number of nodes in the list is in the range [1, 5000].
// 	1 <= Node.val <= 1000
//
// Helpful references (internal KB):
// - Euclidean algorithm for computing the greatest common divisor (number, gcd)
//   • When to use: Use this algorithm to efficiently find the greatest common divisor of two non-negative integers, or as a subroutine for calculating the least common multiple.
//   • Idea: The Euclidean algorithm is an efficient method for computing the greatest common divisor (GCD) of two integers by repeatedly applying the division algorithm. It has a logarithmic time complexity, typically O(log(min(a,b))).
//   • Invariants: The GCD of the current pair (a, b) is always equal to the GCD of the original input numbers.; If a and b are non-negative, then the current values of a and b remain non-negative.
//   • Tips: The GCD of any number and zero is the number itself (e.g., gcd(a, 0) = a).; To calculate LCM, use the formula lcm(a, b) = (a / gcd(a, b)) * b to prevent potential overflow.
//   • Pitfalls: Ensure inputs are non-negative; if negative, take absolute values first.; Be careful with `gcd(0, 0)` definition, which is often undefined or 0.
// - Floyd's Linked List Cycle Finding Algorithm (linked-list, two-pointers, simulation)
//   • When to use: Use this algorithm to efficiently detect if a linked list contains a cycle and, optionally, find the entry point of that cycle, using only constant extra space.
//   • Idea: This algorithm uses two pointers, one moving faster than the other, to detect if a cycle exists in a linked list. If a cycle is found, it can then determine the cycle's starting node in O(N) time complexity and O(1) space complexity.
//   • Invariants: The slow and fast pointers are always valid nodes or null.; In the detection phase, the fast pointer always covers twice the distance of the slow pointer.
//   • Tips: Initialize both slow and fast pointers at the head of the list.; Move the slow pointer by one step and the fast pointer by two steps in each iteration.
//   • Pitfalls: Forgetting to check for null on 'fast' and 'fast.next' before dereferencing them.; Incorrectly assuming the list is non-empty or has at least two nodes.
// - Linked-list implementations of collections (linked-list, ds, simulation)
//   • When to use: When you need dynamic collections that efficiently support insertions and deletions at specific points, or when memory usage needs to be precisely managed without contiguous memory allocation.
//   • Idea: This describes how fundamental data structures like stacks, queues, and bags can be implemented using linked lists, providing dynamic resizing and efficient element manipulation. Operations typically achieve O(1) time complexity for additions and removals at the ends.
//   • Invariants: The head pointer always points to the first element, or is null if the list is empty.; The tail pointer always points to the last element, or is null if the list is empty.
//   • Tips: Use a Node class to encapsulate data and a reference to the next element.; Maintain head and tail pointers for efficient O(1) operations in queues.
//   • Pitfalls: Forgetting to handle edge cases like empty lists or single-element lists.; Introducing 'loitering' by not nullifying references to removed objects, preventing garbage collection.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* insertGreatestCommonDivisors(struct ListNode* head) {
    // Helper function to compute GCD using the Euclidean algorithm
    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    struct ListNode* current = head;

    // Traverse the linked list
    while (current != NULL && current->next != NULL) {
        // Compute GCD of current node and next node
        int gcdValue = gcd(current->val, current->next->val);

        // Create a new node with the GCD value
        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = gcdValue;

        // Insert the new node between current and current->next
        newNode->next = current->next;
        current->next = newNode;

        // Move to the next original node
        current = newNode->next;
    }

    return head;        
}
