// Source: https://leetcode.com/problems/k-th-smallest-prime-fraction/   |   Difficulty: Medium
//
// Problem Description:
// You are given a sorted integer array arr containing 1 and prime numbers, where all the integers of arr are unique. You are also given an integer k.
//
// For every i and j where 0 <= i < j < arr.length, we consider the fraction arr[i] / arr[j].
//
// Return the kth smallest fraction considered. Return your answer as an array of integers of size 2, where answer[0] == arr[i] and answer[1] == arr[j].
//
// Example:
// Input: arr = [1,2,3,5], k = 3
// Output: [2,5]
// Explanation: The fractions to be considered in sorted order are:
// 1/5, 1/3, 2/5, 1/2, 3/5, and 2/3.
// The third fraction is 2/5.
//
// Constraints:
// 2 <= arr.length <= 1000
// 	1 <= arr[i] <= 3 * 104
// 	arr[0] == 1
// 	arr[i] is a prime number for i > 0.
// 	All the numbers of arr are unique and sorted in strictly increasing order.
// 	1 <= k <= arr.length * (arr.length - 1) / 2
//
//
//  
// Follow up: Can you solve the problem with better than O(n2) complexity?
//

class Solution {
    public int[] kthSmallestPrimeFraction(int[] arr, int k) {
        int n = arr.length;
        double left = 0.0, right = 1.0;
        int p = 0, q = 1;

        while (left < right) {
            double mid = (left + right) / 2.0;
            int count = 0;
            p = 0;
            q = 1;
            int j = 1;

            for (int i = 0; i < n - 1; i++) {
                while (j < n && arr[i] > mid * arr[j]) {
                    j++;
                }
                if (j == n) {
                    break;
                }
                count += n - j;

                if (p * arr[j] < q * arr[i]) {
                    p = arr[i];
                    q = arr[j];
                }
            }

            if (count == k) {
                break;
            } else if (count < k) {
                left = mid;
            } else {
                right = mid;
            }
        }

        return new int[]{p, q};         
    }
}
