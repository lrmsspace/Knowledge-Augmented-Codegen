// Source: https://leetcode.com/problems/3sum-with-multiplicity/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array arr, and an integer target, return the number of tuples i, j, k such that i < j < k and arr[i] + arr[j] + arr[k] == target.
//
// As the answer can be very large, return it modulo 109 + 7.
//
// Example:
// Input: arr = [1,1,2,2,3,3,4,4,5,5], target = 8
// Output: 20
// Explanation: 
// Enumerating by the values (arr[i], arr[j], arr[k]):
// (1, 2, 5) occurs 8 times;
// (1, 3, 4) occurs 8 times;
// (2, 2, 4) occurs 2 times;
// (2, 3, 3) occurs 2 times.
//
// Constraints:
// 3 <= arr.length <= 3000
// 	0 <= arr[i] <= 100
// 	0 <= target <= 300
//

class Solution {
    public int threeSumMulti(int[] arr, int target) {
        long mod = 1_000_000_007;
        long result = 0;
        int[] count = new int[101];

        for (int num : arr) {
            count[num]++;
        }

        for (int i = 0; i <= 100; i++) {
            for (int j = i; j <= 100; j++) {
                int k = target - i - j;
                if (k < 0 || k > 100) continue;

                if (i == j && j == k) {
                    result += (long) count[i] * (count[i] - 1) * (count[i] - 2) / 6;
                } else if (i == j && j != k) {
                    result += (long) count[i] * (count[i] - 1) / 2 * count[k];
                } else if (i < j && j < k) {
                    result += (long) count[i] * count[j] * count[k];
                }
            }
        }

        return (int) (result % mod);            
    }
}
