// Source: https://leetcode.com/problems/bitwise-ors-of-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array arr, return the number of distinct bitwise ORs of all the non-empty subarrays of arr.
//
// The bitwise OR of a subarray is the bitwise OR of each integer in the subarray. The bitwise OR of a subarray of one integer is that integer.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: arr = [0]
// Output: 1
// Explanation: There is only one possible result: 0.
//
// Constraints:
// 1 <= arr.length <= 5 * 104
// 	0 <= arr[i] <= 109
//

class Solution {
    public int subarrayBitwiseORs(int[] arr) {
        Set<Integer> result = new HashSet<>();
        Set<Integer> current = new HashSet<>();

        for (int num : arr) {
            Set<Integer> next = new HashSet<>();
            next.add(num);
            for (int prev : current) {
                next.add(prev | num);
            }
            result.addAll(next);
            current = next;
        }

        return result.size();           
    }
}
