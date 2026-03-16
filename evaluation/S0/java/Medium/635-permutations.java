// Source: https://leetcode.com/problems/permutations/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.
//
// Example:
// Input: nums = [1,2,3]
// Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
//
// Constraints:
// 1 <= nums.length <= 6
// 	-10 <= nums[i] <= 10
// 	All the integers of nums are unique.
//

class Solution {
    public List<List<Integer>> permute(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        backtrack(result, new ArrayList<>(), nums);
        return result;          
    }
}
