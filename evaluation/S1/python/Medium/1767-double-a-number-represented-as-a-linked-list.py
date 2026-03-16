# Source: https://leetcode.com/problems/double-a-number-represented-as-a-linked-list/   |   Difficulty: Medium
#
# Problem Description:
# You are given the head of a non-empty linked list representing a non-negative integer without leading zeroes.
#
# Return the head of the linked list after doubling it.
#
# Example:
# Input: head = [1,8,9]
# Output: [3,7,8]
# Explanation: The figure above corresponds to the given linked list which represents the number 189. Hence, the returned linked list represents the number 189 * 2 = 378.
#
# Constraints:
# The number of nodes in the list is in the range [1, 104]
# 	0 <= Node.val <= 9
# 	The input is generated such that the list represents a number that does not have leading zeros, except the number 0 itself.
#
# Helpful references (internal KB):
# - Linked-list implementations of collections (linked-list, ds, simulation)
#   • When to use: When you need dynamic collections that efficiently support insertions and deletions at specific points, or when memory usage needs to be precisely managed without contiguous memory allocation.
#   • Idea: This describes how fundamental data structures like stacks, queues, and bags can be implemented using linked lists, providing dynamic resizing and efficient element manipulation. Operations typically achieve O(1) time complexity for additions and removals at the ends.
#   • Invariants: The head pointer always points to the first element, or is null if the list is empty.; The tail pointer always points to the last element, or is null if the list is empty.
#   • Tips: Use a Node class to encapsulate data and a reference to the next element.; Maintain head and tail pointers for efficient O(1) operations in queues.
#   • Pitfalls: Forgetting to handle edge cases like empty lists or single-element lists.; Introducing 'loitering' by not nullifying references to removed objects, preventing garbage collection.
# - Expression parsing (stack, simulation)
#   • When to use: Use this algorithm to evaluate an arithmetic expression given in infix notation, respecting operator precedence and parentheses. It is suitable for expressions with binary, left-associative operators.
#   • Idea: This algorithm evaluates an infix arithmetic expression using two stacks: one for operands and one for operators. It processes the expression from left to right, applying operator precedence and associativity rules to achieve an O(N) time complexity.
#   • Invariants: The operand stack always contains valid numerical values or intermediate results.; The operator stack maintains operators such that operators with higher or equal precedence are processed before lower precedence ones.
#   • Tips: Clearly define operator precedence and associativity rules for all operators.; Use a separate stack for operands (numbers) and operators (including parentheses).
#   • Pitfalls: Misinterpreting operator precedence or associativity rules can lead to incorrect results.; Failure to handle mismatched or unbalanced parentheses can cause runtime errors.
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def doubleIt(self, head):
        """
        :type head: Optional[ListNode]
        :rtype: Optional[ListNode]
        """
        # Initialize a dummy node to simplify edge cases
        dummy = ListNode(0)
        dummy.next = head
        carry = 0
        current = head
        prev = dummy

        # Traverse the linked list from least significant digit to most
        while current:
            # Double the current digit and add any carry from the previous digit
            total = current.val * 2 + carry
            current.val = total % 10  # Update the current node's value
            carry = total // 10  # Calculate new carry

            prev = current
            current = current.next

        # If there's a carry left after processing all digits, add a new node
        if carry > 0:
            prev.next = ListNode(carry)

        return dummy.next