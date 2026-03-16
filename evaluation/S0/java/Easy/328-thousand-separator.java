// Source: https://leetcode.com/problems/thousand-separator/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, add a dot (".") as the thousands separator and return it in string format.
//
// Example:
// Input: n = 987
// Output: "987"
//
// Constraints:
// 0 <= n <= 231 - 1
//

class Solution {
    public String thousandSeparator(int n) {
        String numStr = Integer.toString(n);
        StringBuilder sb = new StringBuilder();

        int count = 0;
        for (int i = numStr.length() - 1; i >= 0; i--) {
            sb.append(numStr.charAt(i));
            count++;
            if (count == 3 && i != 0) {
                sb.append('.');
                count = 0;
            }
        }

        return sb.reverse().toString();         
    }
}
