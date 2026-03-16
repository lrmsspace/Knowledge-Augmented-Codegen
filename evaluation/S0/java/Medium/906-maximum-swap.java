// Source: https://leetcode.com/problems/maximum-swap/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer num. You can swap two digits at most once to get the maximum valued number.
//
// Return the maximum valued number you can get.
//
// Example:
// Input: num = 2736
// Output: 7236
// Explanation: Swap the number 2 and the number 7.
//
// Constraints:
// 0 <= num <= 108
//

class Solution {
    public int maximumSwap(int num) {
        char[] digits = Integer.toString(num).toCharArray();
        int n = digits.length;
        int[] last = new int[10];

        for (int i = 0; i < n; i++) {
            last[digits[i] - '0'] = i;
        }

        for (int i = 0; i < n; i++) {
            for (int d = 9; d > digits[i] - '0'; d--) {
                if (last[d] > i) {
                    char temp = digits[i];
                    digits[i] = digits[last[d]];
                    digits[last[d]] = temp;
                    return Integer.parseInt(new String(digits));
                }
            }
        }

        return num;         
    }
}
