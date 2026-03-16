// Source: https://leetcode.com/problems/find-lucky-integer-in-an-array/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of integers arr, a lucky integer is an integer that has a frequency in the array equal to its value.
//
// Return the largest lucky integer in the array. If there is no lucky integer return -1.
//
// Example:
// Input: arr = [2,2,3,4]
// Output: 2
// Explanation: The only lucky number in the array is 2 because frequency[2] == 2.
//
// Constraints:
// 1 <= arr.length <= 500
// 	1 <= arr[i] <= 500
//

class Solution {
    public int findLucky(int[] arr) {
        int[] frequency = new int[501];

        for (int num : arr) {
            frequency[num]++;
        }

        for (int i = 500; i >= 1; i--) {
            if (frequency[i] == i) {
                return i;
            }
        }

        return -1;          
    }
}
