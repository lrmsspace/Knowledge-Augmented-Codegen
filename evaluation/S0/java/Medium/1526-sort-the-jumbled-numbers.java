// Source: https://leetcode.com/problems/sort-the-jumbled-numbers/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array mapping which represents the mapping rule of a shuffled decimal system. mapping[i] = j means digit i should be mapped to digit j in this system.
//
// The mapped value of an integer is the new integer obtained by replacing each occurrence of digit i in the integer with mapping[i] for all 0 <= i <= 9.
//
// You are also given another integer array nums. Return the array nums sorted in non-decreasing order based on the mapped values of its elements.
//
// Example:
// Input: mapping = [8,9,4,0,2,1,3,5,7,6], nums = [991,338,38]
// Output: [338,38,991]
// Explanation: 
// Map the number 991 as follows:
// 1. mapping[9] = 6, so all occurrences of the digit 9 will become 6.
// 2. mapping[1] = 9, so all occurrences of the digit 1 will become 9.
// Therefore, the mapped value of 991 is 669.
// 338 maps to 007, or 7 after removing the leading zeros.
// 38 maps to 07, which is also 7 after removing leading zeros.
// Since 338 and 38 share the same mapped value, they should remain in the same relative order, so 338 comes before 38.
// Thus, the sorted array is [338,38,991].
//
// Constraints:
// mapping.length == 10
// 	0 <= mapping[i] <= 9
// 	All the values of mapping[i] are unique.
// 	1 <= nums.length <= 3 * 104
// 	0 <= nums[i] < 109
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] sortJumbled(int[] mapping, int[] nums) {
        Integer[] indices = new Integer[nums.length];
        for (int i = 0; i < nums.length; i++) {
            indices[i] = i;
        }

        java.util.Arrays.sort(indices, (a, b) -> {
            long mappedA = getMappedValue(nums[a], mapping);
            long mappedB = getMappedValue(nums[b], mapping);
            if (mappedA != mappedB) {
                return Long.compare(mappedA, mappedB);
            } else {
                return Integer.compare(a, b); // Maintain original order for equal mapped values
            }
        });

        int[] sortedNums = new int[nums.length];
        for (int i = 0; i < nums.length; i++) {
            sortedNums[i] = nums[indices[i]];
        }

        return sortedNums;          
    }
}
