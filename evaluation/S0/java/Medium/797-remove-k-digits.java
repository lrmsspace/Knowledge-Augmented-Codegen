// Source: https://leetcode.com/problems/remove-k-digits/   |   Difficulty: Medium
//
// Problem Description:
// Given string num representing a non-negative integer num, and an integer k, return the smallest possible integer after removing k digits from num.
//
// Example:
// Input: num = "1432219", k = 3
// Output: "1219"
// Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
//
// Constraints:
// 1 <= k <= num.length <= 105
// 	num consists of only digits.
// 	num does not have any leading zeros except for the zero itself.
//

class Solution {
    public String removeKdigits(String num, int k) {
        StringBuilder sb = new StringBuilder();
        for (char digit : num.toCharArray()) {
            while (k > 0 && sb.length() > 0 && sb.charAt(sb.length() - 1) > digit) {
                sb.deleteCharAt(sb.length() - 1);
                k--;
            }
            sb.append(digit);
        }
        // If k > 0, remove the last k digits
        sb.setLength(sb.length() - k);

        // Remove leading zeros
        int index = 0;
        while (index < sb.length() && sb.charAt(index) == '0') {
            index++;
        }
        sb.delete(0, index);

        return sb.length() == 0 ? "0" : sb.toString();          
    }
}
