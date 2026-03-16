// Source: https://leetcode.com/problems/minimum-deletions-to-make-array-beautiful/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums. The array nums is beautiful if:
//
//
// 	nums.length is even.
// 	nums[i] != nums[i + 1] for all i % 2 == 0.
//
//
// Note that an empty array is considered beautiful.
//
// You can delete any number of elements from nums. When you delete an element, all the elements to the right of the deleted element will be shifted one unit to the left to fill the gap created and all the elements to the left of the deleted element will remain unchanged.
//
// Return the minimum number of elements to delete from nums to make it beautiful.
//
// Example:
// Input: nums = [1,1,2,3,5]
// Output: 1
// Explanation: You can delete either nums[0] or nums[1] to make nums = [1,2,3,5] which is beautiful. It can be proven you need at least 1 deletion to make nums beautiful.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 105
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minDeletion(int[] nums) {
        int deletions = 0;
        int i = 0;

        while (i < nums.length - 1) {
            if (nums[i] == nums[i + 1]) {
                deletions++;
                i += 2; // Skip the next element as well
            } else {
                i++;
            }
        }

        // If the length of the array after deletions is odd, we need to delete one more element
        if ((nums.length - deletions) % 2 != 0) {
            deletions++;
        }

        return deletions;           
    }
}
