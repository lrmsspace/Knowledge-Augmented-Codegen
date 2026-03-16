// Source: https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and a positive integer k, check whether it is possible to divide this array into sets of k consecutive numbers.
//
// Return true if it is possible. Otherwise, return false.
//
// Example:
// Input: nums = [1,2,3,3,4,4,5,6], k = 4
// Output: true
// Explanation: Array can be divided into [1,2,3,4] and [3,4,5,6].
//
// Constraints:
// 1 <= k <= nums.length <= 105
// 	1 <= nums[i] <= 109
//
//
//  
// Note: This question is the same as 846: https://leetcode.com/problems/hand-of-straights/
//

class Solution {
    public boolean isPossibleDivide(int[] nums, int k) {
        if (nums.length % k != 0) {
            return false;
        }

        TreeMap<Integer, Integer> countMap = new TreeMap<>();
        for (int num : nums) {
            countMap.put(num, countMap.getOrDefault(num, 0) + 1);
        }

        while (!countMap.isEmpty()) {
            int start = countMap.firstKey();
            for (int i = 0; i < k; i++) {
                int currentNum = start + i;
                if (!countMap.containsKey(currentNum)) {
                    return false;
                }
                int count = countMap.get(currentNum);
                if (count == 1) {
                    countMap.remove(currentNum);
                } else {
                    countMap.put(currentNum, count - 1);
                }
            }
        }

        return true;            
    }
}
