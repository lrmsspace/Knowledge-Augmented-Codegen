// Source: https://leetcode.com/problems/reverse-nodes-in-even-length-groups/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a linked list.
//
// The nodes in the linked list are sequentially assigned to non-empty groups whose lengths form the sequence of the natural numbers (1, 2, 3, 4, ...). The length of a group is the number of nodes assigned to it. In other words,
//
//
// 	The 1st node is assigned to the first group.
// 	The 2nd and the 3rd nodes are assigned to the second group.
// 	The 4th, 5th, and 6th nodes are assigned to the third group, and so on.
//
//
// Note that the length of the last group may be less than or equal to 1 + the length of the second to last group.
//
// Reverse the nodes in each group with an even length, and return the head of the modified linked list.
//
// Example:
// Input: head = [5,2,6,3,9,1,7,3,8,4]
// Output: [5,6,2,3,9,1,4,8,3,7]
// Explanation:
// - The length of the first group is 1, which is odd, hence no reversal occurs.
// - The length of the second group is 2, which is even, hence the nodes are reversed.
// - The length of the third group is 3, which is odd, hence no reversal occurs.
// - The length of the last group is 4, which is even, hence the nodes are reversed.
//
// Constraints:
// The number of nodes in the list is in the range [1, 105].
// 	0 <= Node.val <= 105
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseEvenLengthGroups(struct ListNode* head) {
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode* prevGroupEnd = &dummy;
    struct ListNode* curr = head;
    int groupSize = 1;

    while (curr) {
        struct ListNode* groupStart = curr;
        int count = 0;

        // Count nodes in the current group
        while (curr && count < groupSize) {
            curr = curr->next;
            count++;
        }

        // If the group size is even, reverse the group
        if (count % 2 == 0) {
            struct ListNode* prev = curr;
            struct ListNode* node = groupStart;

            for (int i = 0; i < count; i++) {
                struct ListNode* nextNode = node->next;
                node->next = prev;
                prev = node;
                node = nextNode;
            }

            // Connect the previous group to the reversed group
            prevGroupEnd->next = prev;
            prevGroupEnd = groupStart; // groupStart is now the end of the reversed group
        } else {
            // Move prevGroupEnd to the end of the current group
            prevGroupEnd = groupStart;
            for (int i = 1; i < count; i++) {
                prevGroupEnd = prevGroupEnd->next;
            }
        }

        groupSize++;
    }

    return dummy.next;      
}
