// Source: https://leetcode.com/problems/find-all-lonely-numbers-in-the-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. A number x is lonely when it appears only once, and no adjacent numbers (i.e. x + 1 and x - 1) appear in the array.
//
// Return all lonely numbers in nums. You may return the answer in any order.
//
// Example:
// Input: nums = [10,6,5,8]
// Output: [10,8]
// Explanation: 
// - 10 is a lonely number since it appears exactly once and 9 and 11 does not appear in nums.
// - 8 is a lonely number since it appears exactly once and 7 and 9 does not appear in nums.
// - 5 is not a lonely number since 6 appears in nums and vice versa.
// Hence, the lonely numbers in nums are [10, 8].
// Note that [8, 10] may also be returned.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 106
//

class Solution {
    public List<Integer> findLonely(int[] nums) {
        Map<Integer, Integer> frequencyMap = new HashMap<>();
        List<Integer> lonelyNumbers = new ArrayList<>();

        // Count the frequency of each number in the array
        for (int num : nums) {
            frequencyMap.put(num, frequencyMap.getOrDefault(num, 0) + 1);
        }

        // Identify lonely numbers
        for (int num : nums) {
            if (frequencyMap.get(num) == 1 && 
                !frequencyMap.containsKey(num - 1) && 
                !frequencyMap.containsKey(num + 1)) {
                lonelyNumbers.add(num);
            }
        }

        return lonelyNumbers;           
    }
}
