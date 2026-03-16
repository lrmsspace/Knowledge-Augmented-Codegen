// Source: https://leetcode.com/problems/maximum-value-after-insertion/   |   Difficulty: Medium
//
// Problem Description:
// You are given a very large integer n, represented as a string,​​​​​​ and an integer digit x. The digits in n and the digit x are in the inclusive range [1, 9], and n may represent a negative number.
//
// You want to maximize n's numerical value by inserting x anywhere in the decimal representation of n​​​​​​. You cannot insert x to the left of the negative sign.
//
//
// 	For example, if n = 73 and x = 6, it would be best to insert it between 7 and 3, making n = 763.
// 	If n = -55 and x = 2, it would be best to insert it before the first 5, making n = -255.
//
//
// Return a string representing the maximum value of n​​​​​​ after the insertion.
//
// Example:
// Input: n = "99", x = 9
// Output: "999"
// Explanation: The result is the same regardless of where you insert 9.
//
// Constraints:
// 1 <= n.length <= 105
// 	1 <= x <= 9
// 	The digits in n​​​ are in the range [1, 9].
// 	n is a valid representation of an integer.
// 	In the case of a negative n,​​​​​​ it will begin with '-'.
//

class Solution {
    public String maxValue(String n, int x) {
        StringBuilder result = new StringBuilder();
        char digit = (char) (x + '0');
        boolean inserted = false;

        if (n.charAt(0) == '-') {
            result.append('-');
            for (int i = 1; i < n.length(); i++) {
                if (!inserted && n.charAt(i) > digit) {
                    result.append(digit);
                    inserted = true;
                }
                result.append(n.charAt(i));
            }
        } else {
            for (int i = 0; i < n.length(); i++) {
                if (!inserted && n.charAt(i) < digit) {
                    result.append(digit);
                    inserted = true;
                }
                result.append(n.charAt(i));
            }
        }

        if (!inserted) {
            result.append(digit);
        }

        return result.toString();           
    }
}
