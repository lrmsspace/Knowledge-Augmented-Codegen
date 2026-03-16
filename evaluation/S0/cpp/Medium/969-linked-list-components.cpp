// Source: https://leetcode.com/problems/linked-list-components/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a linked list containing unique integer values and an integer array nums that is a subset of the linked list values.
//
// Return the number of connected components in nums where two values are connected if they appear consecutively in the linked list.
//
// Example:
// Input: head = [0,1,2,3], nums = [0,1,3]
// Output: 2
// Explanation: 0 and 1 are connected, so [0, 1] and [3] are the two connected components.
//
// Constraints:
// The number of nodes in the linked list is n.
// 	1 <= n <= 104
// 	0 <= Node.val < n
// 	All the values Node.val are unique.
// 	1 <= nums.length <= n
// 	0 <= nums[i] < n
// 	All the values of nums are unique.
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    int numComponents(ListNode* head, vector<int>& nums) {
        unordered_set<int> numSet(nums.begin(), nums.end());
        int components = 0;
        bool inComponent = false;

        ListNode* current = head;
        while (current != nullptr) {
            if (numSet.count(current->val)) {
                if (!inComponent) {
                    components++;
                    inComponent = true;
                }
            } else {
                inComponent = false;
            }
            current = current->next;
        }

        return components;          
    }
};
