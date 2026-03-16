// Source: https://leetcode.com/problems/maximize-consecutive-elements-in-an-array-after-modification/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array nums consisting of positive integers.
//
// Initially, you can increase the value of any element in the array by at most 1.
//
// After that, you need to select one or more elements from the final array such that those elements are consecutive when sorted in increasing order. For example, the elements [3, 4, 5] are consecutive while [3, 4, 6] and [1, 1, 2, 3] are not.
//
// Return the maximum number of elements that you can select.
//
// Example:
// Input: nums = [2,1,5,1,1]
// Output: 3
// Explanation: We can increase the elements at indices 0 and 3. The resulting array is nums = [3,1,5,2,1].
// We select the elements [3,1,5,2,1] and we sort them to obtain [1,2,3], which are consecutive.
// It can be shown that we cannot select more than 3 consecutive elements.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 106
//

class Solution {
    public int maxSelectedElements(int[] nums) {
        Arrays.sort(nums);
        int maxCount = 1;
        int currentCount = 1;
        int previous = nums[0] - 1; // considering we can increase the first element by 1

        for (int i = 1; i < nums.length; i++) {
            int current = nums[i];

            if (current <= previous) {
                current = previous + 1; // increase current to maintain consecutiveness
            } else if (current == previous + 1) {
                // do nothing, it's already consecutive
            } else if (current == previous + 2) {
                current -= 1; // decrease current by 1 to make it consecutive
            } else {
                currentCount = 0; // reset count if gap is too large
            }

            currentCount++;
            maxCount = Math.max(maxCount, currentCount);
            previous = current;
        }

        return maxCount;            
    }
}
