// Source: https://leetcode.com/problems/array-of-doubled-pairs/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array of even length arr, return true if it is possible to reorder arr such that arr[2 * i + 1] = 2 * arr[2 * i] for every 0 <= i < len(arr) / 2, or false otherwise.
//
// Example:
// Input: arr = [3,1,3,6]
// Output: false
//
// Constraints:
// 2 <= arr.length <= 3 * 104
// 	arr.length is even.
// 	-105 <= arr[i] <= 105
//

class Solution {
    public boolean canReorderDoubled(int[] arr) {
        Map<Integer, Integer> countMap = new HashMap<>();
        for (int num : arr) {
            countMap.put(num, countMap.getOrDefault(num, 0) + 1);
        }

        Arrays.sort(arr);

        for (int num : arr) {
            if (countMap.get(num) == 0) {
                continue;
            }

            int target = num < 0 ? num / 2 : num * 2;

            if (num < 0 && num % 2 != 0) {
                return false;
            }

            if (!countMap.containsKey(target) || countMap.get(target) == 0) {
                return false;
            }

            countMap.put(num, countMap.get(num) - 1);
            countMap.put(target, countMap.get(target) - 1);
        }

        return true;            
    }
}
