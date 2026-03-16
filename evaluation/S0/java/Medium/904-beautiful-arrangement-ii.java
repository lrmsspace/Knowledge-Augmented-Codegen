// Source: https://leetcode.com/problems/beautiful-arrangement-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers n and k, construct a list answer that contains n different positive integers ranging from 1 to n and obeys the following requirement:
//
//
// 	Suppose this list is answer = [a1, a2, a3, ... , an], then the list [|a1 - a2|, |a2 - a3|, |a3 - a4|, ... , |an-1 - an|] has exactly k distinct integers.
//
//
// Return the list answer. If there multiple valid answers, return any of them.
//
// Example:
// Input: n = 3, k = 1
// Output: [1,2,3]
// Explanation: The [1,2,3] has three different positive integers ranging from 1 to 3, and the [1,1] has exactly 1 distinct integer: 1
//
// Constraints:
// 1 <= k < n <= 104
//

class Solution {
    public int[] constructArray(int n, int k) {
        int[] result = new int[n];
        int index = 0;

        // Step 1: Fill the first part with sequential numbers
        for (int i = 1; i <= n - k - 1; i++) {
            result[index++] = i;
        }

        // Step 2: Create the alternating high-low pattern for the last k + 1 numbers
        int low = n - k;
        int high = n;
        boolean addHigh = true;

        while (low <= high) {
            if (addHigh) {
                result[index++] = high--;
            } else {
                result[index++] = low++;
            }
            addHigh = !addHigh;
        }

        return result;          
    }
}
