// Source: https://leetcode.com/problems/split-linked-list-in-parts/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a singly linked list and an integer k, split the linked list into k consecutive linked list parts.
//
// The length of each part should be as equal as possible: no two parts should have a size differing by more than one. This may lead to some parts being null.
//
// The parts should be in the order of occurrence in the input list, and parts occurring earlier should always have a size greater than or equal to parts occurring later.
//
// Return an array of the k parts.
//
// Example:
// Input: head = [1,2,3], k = 5
// Output: [[1],[2],[3],[],[]]
// Explanation:
// The first element output[0] has output[0].val = 1, output[0].next = null.
// The last element output[4] is null, but its string representation as a ListNode is [].
//
// Constraints:
// The number of nodes in the list is in the range [0, 1000].
// 	0 <= Node.val <= 1000
// 	1 <= k <= 50
//

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
    public ListNode[] splitListToParts(ListNode head, int k) {
        // Calculate the length of the linked list
        int length = 0;
        ListNode current = head;
        while (current != null) {
            length++;
            current = current.next;
        }

        // Determine the size of each part and the number of longer parts
        int partSize = length / k;
        int extraNodes = length % k;

        ListNode[] result = new ListNode[k];
        current = head;

        for (int i = 0; i < k; i++) {
            ListNode partHead = current;
            int currentPartSize = partSize + (extraNodes > 0 ? 1 : 0);
            extraNodes--;

            for (int j = 0; j < currentPartSize - 1; j++) {
                if (current != null) {
                    current = current.next;
                }
            }

            if (current != null) {
                ListNode nextPartHead = current.next;
                current.next = null; // Terminate the current part
                current = nextPartHead; // Move to the next part
            }

            result[i] = partHead;
        }

        return result;          
    }
}
