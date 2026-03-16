// Source: https://leetcode.com/problems/peak-index-in-a-mountain-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer mountain array arr of length n where the values increase to a peak element and then decrease.
//
// Return the index of the peak element.
//
// Your task is to solve it in O(log(n)) time complexity.
//
// Example:
// Input: arr = [0,1,0]
//
// Output: 1
//
// Constraints:
// 3 <= arr.length <= 105
// 	0 <= arr[i] <= 106
// 	arr is guaranteed to be a mountain array.
//

class Solution {
    public int peakIndexInMountainArray(int[] arr) {
        int left = 0;
        int right = arr.length - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] < arr[mid + 1]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left;            
    }
}
