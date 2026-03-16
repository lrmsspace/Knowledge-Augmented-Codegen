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

/**
 * @param {number[]} nums
 * @return {boolean}
 */
var circularArrayLoop = function(nums) {
    const n = nums.length;

    const getNextIndex = (current) => {
        return ((current + nums[current]) % n + n) % n;
    };
    for (let i = 0; i < n; i++) {
        if (nums[i] === 0) continue;
        let slow = i;
        let fast = i;
        const direction = Math.sign(nums[i]);
        while (true) {
            slow = getNextIndex(slow);
            fast = getNextIndex(getNextIndex(fast));
            if (Math.sign(nums[slow]) !== direction || Math.sign(nums[fast]) !== direction) {
                break;
            }
            if (slow === fast) {
                if (slow === getNextIndex(slow)) {
                    break;
                }
                return true;
            }
        }
        slow = i;
        const val = nums[i];
        while (Math.sign(nums[slow]) === direction) {
            const next = getNextIndex(slow);
            nums[slow] = 0;
            slow = next;
        }
    }
    return false;
};
