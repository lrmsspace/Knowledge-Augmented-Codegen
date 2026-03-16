// Source: https://leetcode.com/problems/intersection-of-multiple-arrays/   |   Difficulty: Easy
//
// Problem Description:
// Given a 2D integer array nums where nums[i] is a non-empty array of distinct positive integers, return the list of integers that are present in each array of nums sorted in ascending order.
//
// Example:
// Input: nums = [[3,1,2,4,5],[1,2,3,4],[3,4,5,6]]
// Output: [3,4]
// Explanation: 
// The only integers present in each of nums[0] = [3,1,2,4,5], nums[1] = [1,2,3,4], and nums[2] = [3,4,5,6] are 3 and 4, so we return [3,4].
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= sum(nums[i].length) <= 1000
// 	1 <= nums[i][j] <= 1000
// 	All the values of nums[i] are unique.
//

class Solution {
    public List<Integer> intersection(int[][] nums) {
        Map<Integer, Integer> countMap = new HashMap<>();
        int arraysCount = nums.length;

        for (int[] array : nums) {
            for (int num : array) {
                countMap.put(num, countMap.getOrDefault(num, 0) + 1);
            }
        }

        List<Integer> result = new ArrayList<>();
        for (Map.Entry<Integer, Integer> entry : countMap.entrySet()) {
            if (entry.getValue() == arraysCount) {
                result.add(entry.getKey());
            }
        }

        Collections.sort(result);
        return result;          
    }
}
