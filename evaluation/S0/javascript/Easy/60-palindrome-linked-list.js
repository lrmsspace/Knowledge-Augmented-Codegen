// Source: https://leetcode.com/problems/palindrome-linked-list/   |   Difficulty: Easy
//
// Problem Description:
// Given the head of a singly linked list, return true if it is a palindrome or false otherwise.
//
// Example:
// Input: head = [1,2,2,1]
// Output: true
//
// Constraints:
// The number of nodes in the list is in the range [1, 105].
// 	0 <= Node.val <= 9
//
//
//  
// Follow up: Could you do it in O(n) time and O(1) space?
//

/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} head
 * @return {boolean}
 */
var isPalindrome = function(head) {
    let slow = head;
    let fast = head;
    const stack = [];   
    while (fast !== null && fast.next !== null) {
        stack.push(slow.val);
        slow = slow.next;
        fast = fast.next.next;
    }
    if (fast !== null) {
        slow = slow.next;
    }
    while (slow !== null) { 
        if (slow.val !== stack.pop()) {
            return false;
        }
        slow = slow.next;
    }
    return true;
};      