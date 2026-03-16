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

/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode[]} lists
 * @return {ListNode}
 */
var mergeKLists = function(lists) {
    if (lists.length === 0) return null;
    if (lists.length === 1) return lists[0];
    const mergeTwoLists = (l1, l2) => {
        const dummy = new ListNode(0);
        let current = dummy;
        while (l1 !== null && l2 !== null) {
            if (l1.val < l2.val) {
                current.next = l1;
                l1 = l1.next;
            } else {
                current.next = l2;
                l2 = l2.next;
            }
            current = current.next;
        }
        if (l1 !== null) {
            current.next = l1;
        } else {
            current.next = l2;
        }
        return dummy.next;
    };
    while (lists.length > 1) {
        const mergedLists = [];
        for (let i = 0; i < lists.length; i += 2) {
            const l1 = lists[i];
            const l2 = i + 1 < lists.length ? lists[i + 1] : null;
            mergedLists.push(mergeTwoLists(l1, l2));
        }
        lists = mergedLists;
    }
    return lists[0];
            
};
