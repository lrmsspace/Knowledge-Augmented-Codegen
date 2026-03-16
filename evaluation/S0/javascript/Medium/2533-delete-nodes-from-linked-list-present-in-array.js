// Source: https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers nums and the head of a linked list. Return the head of the modified linked list after removing all nodes from the linked list that have a value that exists in nums.
//
// Example:
// Input: nums = [1,2,3], head = [1,2,3,4,5]
//
// Output: [4,5]
//
// Explanation:
//
//
//
// Remove the nodes with values 1, 2, and 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
// 	All elements in nums are unique.
// 	The number of nodes in the given list is in the range [1, 105].
// 	1 <= Node.val <= 105
// 	The input is generated such that there is at least one node in the linked list that has a value not present in nums.
//

/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {number[]} nums
 * @param {ListNode} head
 * @return {ListNode}
 */
var modifiedList = function(nums, head) {
    const numSet = new Set(nums);
    let dummy = new ListNode(0);
    dummy.next = head;
    let current = dummy;
    while (current.next !== null) {
        if (numSet.has(current.next.val)) {
            current.next = current.next.next;
        } else {
            current = current.next;
        }
    }
    return dummy.next;
};