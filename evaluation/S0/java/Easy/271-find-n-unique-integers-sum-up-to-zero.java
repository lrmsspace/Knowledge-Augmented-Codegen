// Source: https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, return any array containing n unique integers such that they add up to 0.
//
// Example:
// Input: n = 5
// Output: [-7,-1,1,3,4]
// Explanation: These arrays also are accepted [-5,-1,1,2,3] , [-3,-1,2,-2,4].
//
// Constraints:
// 1 <= n <= 1000
//

class Solution {
    public int[] sumZero(int n) {
        int[] result = new int[n];
        int left = 0;
        int right = n - 1;
        int num = 1;

        while (left < right) {
            result[left++] = -num;
            result[right--] = num;
            num++;
        }

        // If n is odd, the middle element remains 0 which is already set by default
        return result;          
    }
}
