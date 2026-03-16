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
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
//   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
//   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
//   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
//   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
//   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
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
	const stack1 = [];
	const stack2 = [];

	while (l1) {
		stack1.push(l1.val);
		l1 = l1.next;
	}

	while (l2) {
		stack2.push(l2.val);
		l2 = l2.next;
	}

	let carry = 0;
	let head = null;

	while (stack1.length > 0 || stack2.length > 0 || carry > 0) {
		const x = stack1.length > 0 ? stack1.pop() : 0;
		const y = stack2.length > 0 ? stack2.pop() : 0;

		const sum = x + y + carry;
		carry = Math.floor(sum / 10);

		const newNode = new ListNode(sum % 10);
		newNode.next = head;
		head = newNode;
	}

	return head;
};
