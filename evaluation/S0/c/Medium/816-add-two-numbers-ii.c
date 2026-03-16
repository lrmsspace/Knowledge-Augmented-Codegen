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

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode *stack1[100], *stack2[100];
    int top1 = -1, top2 = -1;
    while (l1) {
        stack1[++top1] = l1;
        l1 = l1->next;
    }
    while (l2) {
        stack2[++top2] = l2;
        l2 = l2->next;
    }
    struct ListNode *head = NULL;
    int carry = 0;
    while (top1 >= 0 || top2 >= 0 || carry) {
        int sum = carry;
        if (top1 >= 0) {
            sum += stack1[top1--]->val;
        }
        if (top2 >= 0) {
            sum += stack2[top2--]->val;
        }
        struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
        newNode->val = sum % 10;
        newNode->next = head;
        head = newNode;
        carry = sum / 10;
    }
    return head;        
}
