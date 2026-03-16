// Source: https://leetcode.com/problems/add-two-numbers-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.
//
// You may assume the two numbers do not contain any leading zero, except the number 0 itself.
//
// Example:
// Input: l1 = [7,2,4,3], l2 = [5,6,4]
// Output: [7,8,0,7]
//
// Constraints:
// The number of nodes in each linked list is in the range [1, 100].
// 	0 <= Node.val <= 9
// 	It is guaranteed that the list represents a number that does not have leading zeros.
//
//
//  
// Follow up: Could you solve it without reversing the input lists?
//
// Helpful references (internal KB):
// - Linked-list implementations of collections (linked-list, stack, simulation)
//   • When to use: Use when a Last-In, First-Out (LIFO) data structure is required, and dynamic size with efficient O(1) push and pop operations is crucial, especially without a fixed capacity.
//   • Idea: This describes implementing a stack using a singly linked list, where elements are added and removed from the head of the list. Both push and pop operations achieve O(1) time complexity.
//   • Invariants: The 'first' pointer always points to the top element of the stack, or is null if the stack is empty.; Each node's 'next' pointer correctly links to the subsequent element in the stack, maintaining the LIFO order.
//   • Tips: Maintain a 'first' pointer to the head of the linked list, representing the stack's top.; Push operation involves creating a new node, linking it to the current 'first', then updating 'first'.
//   • Pitfalls: Forgetting to handle the empty stack case for pop, leading to `NoSuchElementException`.; Incorrectly updating the 'first' pointer during push or pop, which can break the list structure.
// - Expression parsing (stack, simulation)
//   • When to use: This algorithm is used to evaluate expressions given in Reverse Polish Notation (postfix notation) to compute their final numerical value.
//   • Idea: This algorithm evaluates an expression in Reverse Polish Notation by processing elements sequentially. Numbers are pushed onto a stack, and operators pop two operands, compute, and push the result.
//   • Invariants: The stack always contains only numbers (operands or intermediate results).; For a valid RPN expression, the stack will have at least two elements when an operator is processed.
//   • Tips: Process the RPN expression from left to right, token by token.; Push numerical operands directly onto the stack.
//   • Pitfalls: Attempting to pop from an empty stack when an operator is encountered, indicating an invalid RPN expression.; Incorrect order of operands for non-commutative operations like subtraction or division.
// - Linked-list implementations of collections (linked-list, ds, simulation)
//   • When to use: When you need dynamic collections that efficiently support insertions and deletions at specific points, or when memory usage needs to be precisely managed without contiguous memory allocation.
//   • Idea: This describes how fundamental data structures like stacks, queues, and bags can be implemented using linked lists, providing dynamic resizing and efficient element manipulation. Operations typically achieve O(1) time complexity for additions and removals at the ends.
//   • Invariants: The head pointer always points to the first element, or is null if the list is empty.; The tail pointer always points to the last element, or is null if the list is empty.
//   • Tips: Use a Node class to encapsulate data and a reference to the next element.; Maintain head and tail pointers for efficient O(1) operations in queues.
//   • Pitfalls: Forgetting to handle edge cases like empty lists or single-element lists.; Introducing 'loitering' by not nullifying references to removed objects, preventing garbage collection.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} l1
 * @param {ListNode} l2
 * @return {ListNode}
 */
var addTwoNumbers = function(l1, l2) {
    // Helper function to push values of a linked list onto a stack
    const pushToStack = (head) => {
        const stack = [];
        while (head) {
            stack.push(head.val);
            head = head.next;
        }
        return stack;
    };

    const stack1 = pushToStack(l1);
    const stack2 = pushToStack(l2);
    let carry = 0;
    let resultHead = null;

    // Add digits from the stacks until both are empty and no carry remains
    while (stack1.length > 0 || stack2.length > 0 || carry > 0) {
        const sum = (stack1.pop() || 0) + (stack2.pop() || 0) + carry; // Pop from stacks or use 0 if empty
        carry = Math.floor(sum / 10); // Calculate new carry
        const newNode = new ListNode(sum % 10); // Create new node with the last digit of sum
        newNode.next = resultHead; // Point new node to the current head of result
        resultHead = newNode; // Update head of result to the new node
    }

    return resultHead; // Return the head of the resulting linked list
};
