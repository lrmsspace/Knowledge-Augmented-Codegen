// Source: https://leetcode.com/problems/circular-array-loop/   |   Difficulty: Medium
//
// Problem Description:
// You are playing a game involving a circular array of non-zero integers nums. Each nums[i] denotes the number of indices forward/backward you must move if you are located at index i:
//
//
// 	If nums[i] is positive, move nums[i] steps forward, and
// 	If nums[i] is negative, move nums[i] steps backward.
//
//
// Since the array is circular, you may assume that moving forward from the last element puts you on the first element, and moving backwards from the first element puts you on the last element.
//
// A cycle in the array consists of a sequence of indices seq of length k where:
//
//
// 	Following the movement rules above results in the repeating index sequence seq[0] -> seq[1] -> ... -> seq[k - 1] -> seq[0] -> ...
// 	Every nums[seq[j]] is either all positive or all negative.
// 	k > 1
//
//
// Return true if there is a cycle in nums, or false otherwise.
//
// Example:
// Input: nums = [2,-1,1,2,2]
// Output: true
// Explanation: The graph shows how the indices are connected. White nodes are jumping forward, while red is jumping backward.
// We can see the cycle 0 --> 2 --> 3 --> 0 --> ..., and all of its nodes are white (jumping in the same direction).
//
// Constraints:
// 1 <= nums.length <= 5000
// 	-1000 <= nums[i] <= 1000
// 	nums[i] != 0
//
//
//  
// Follow up: Could you solve it in O(n) time complexity and O(1) extra space complexity?
//

bool circularArrayLoop(int* nums, int numsSize) {
    #define GET_NEXT_INDEX(idx) (((idx) + nums[(idx)] + numsSize) % numsSize)

    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] == 0) {
            continue;
        }

        int slow = i, fast = i;
        bool is_forward = nums[i] > 0;

        while (true) {
            slow = GET_NEXT_INDEX(slow);
            if (nums[slow] == 0 || (nums[slow] > 0) != is_forward) {
                break;
            }

            fast = GET_NEXT_INDEX(fast);
            if (nums[fast] == 0 || (nums[fast] > 0) != is_forward) {
                break;
            }
            fast = GET_NEXT_INDEX(fast);
            if (nums[fast] == 0 || (nums[fast] > 0) != is_forward) {
                break;
            }

            if (slow == fast) {
                if (slow == GET_NEXT_INDEX(slow)) {
                    break;
                }
                return true;
            }
        }

        slow = i;
        int val = nums[i];
        while ((nums[slow] > 0) == is_forward) {
            int next = GET_NEXT_INDEX(slow);
            nums[slow] = 0;
            slow = next;
        }
    }

    return false;       
}
