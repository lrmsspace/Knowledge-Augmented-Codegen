// Source: https://leetcode.com/problems/sum-of-all-odd-length-subarrays/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of positive integers arr, return the sum of all possible odd-length subarrays of arr.
//
// A subarray is a contiguous subsequence of the array.
//
// Example:
// Input: arr = [1,4,2,5,3]
// Output: 58
// Explanation: The odd-length subarrays of arr and their sums are:
// [1] = 1
// [4] = 4
// [2] = 2
// [5] = 5
// [3] = 3
// [1,4,2] = 7
// [4,2,5] = 11
// [2,5,3] = 10
// [1,4,2,5,3] = 15
// If we add all these together we get 1 + 4 + 2 + 5 + 3 + 7 + 11 + 10 + 15 = 58
//
// Constraints:
// 1 <= arr.length <= 100
// 	1 <= arr[i] <= 1000
//
//
//  
// Follow up:
//
// Could you solve this problem in O(n) time complexity?
//

class Solution {
    public int sumOddLengthSubarrays(int[] arr) {
        int n = arr.length;
        int totalSum = 0;

        for (int i = 0; i < n; i++) {
            int leftCount = i;          // Number of elements to the left of arr[i]
            int rightCount = n - i - 1; // Number of elements to the right of arr[i]

            // Calculate the number of odd-length subarrays that include arr[i]
            int leftOdd = (leftCount + 1) / 2;
            int leftEven = (leftCount / 2) + 1;
            int rightOdd = (rightCount + 1) / 2;
            int rightEven = (rightCount / 2) + 1;

            // Total odd-length subarrays including arr[i]
            int totalOddSubarrays = (leftOdd * rightOdd) + (leftEven * rightEven);

            // Contribution of arr[i] to the total sum
            totalSum += arr[i] * totalOddSubarrays;
        }

        return totalSum;            
    }
}
