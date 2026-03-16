// Source: https://leetcode.com/problems/sort-even-and-odd-indices-independently/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed integer array nums. Rearrange the values of nums according to the following rules:
//
//
// 	Sort the values at odd indices of nums in non-increasing order.
//
// 	
// 		For example, if nums = [4,1,2,3] before this step, it becomes [4,3,2,1] after. The values at odd indices 1 and 3 are sorted in non-increasing order.
// 	
// 	
// 	Sort the values at even indices of nums in non-decreasing order.
// 	
// 		For example, if nums = [4,1,2,3] before this step, it becomes [2,1,4,3] after. The values at even indices 0 and 2 are sorted in non-decreasing order.
// 	
// 	
//
//
// Return the array formed after rearranging the values of nums.
//
// Example:
// Input: nums = [4,1,2,3]
// Output: [2,3,4,1]
// Explanation: 
// First, we sort the values present at odd indices (1 and 3) in non-increasing order.
// So, nums changes from [4,1,2,3] to [4,3,2,1].
// Next, we sort the values present at even indices (0 and 2) in non-decreasing order.
// So, nums changes from [4,1,2,3] to [2,3,4,1].
// Thus, the array formed after rearranging the values is [2,3,4,1].
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 100
//

class Solution {
    public int[] sortEvenOdd(int[] nums) {
        List<Integer> evenList = new ArrayList<>();
        List<Integer> oddList = new ArrayList<>();

        for (int i = 0; i < nums.length; i++) {
            if (i % 2 == 0) {
                evenList.add(nums[i]);
            } else {
                oddList.add(nums[i]);
            }
        }

        Collections.sort(evenList);
        Collections.sort(oddList, Collections.reverseOrder());

        int evenIndex = 0;
        int oddIndex = 0;

        for (int i = 0; i < nums.length; i++) {
            if (i % 2 == 0) {
                nums[i] = evenList.get(evenIndex++);
            } else {
                nums[i] = oddList.get(oddIndex++);
            }
        }

        return nums;            
    }
}
