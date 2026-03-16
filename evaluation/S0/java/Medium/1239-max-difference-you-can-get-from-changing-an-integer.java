// Source: https://leetcode.com/problems/max-difference-you-can-get-from-changing-an-integer/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer num. You will apply the following steps to num two separate times:
//
//
// 	Pick a digit x (0 <= x <= 9).
// 	Pick another digit y (0 <= y <= 9). Note y can be equal to x.
// 	Replace all the occurrences of x in the decimal representation of num by y.
//
//
// Let a and b be the two results from applying the operation to num independently.
//
// Return the max difference between a and b.
//
// Note that neither a nor b may have any leading zeros, and must not be 0.
//
// Example:
// Input: num = 555
// Output: 888
// Explanation: The first time pick x = 5 and y = 9 and store the new integer in a.
// The second time pick x = 5 and y = 1 and store the new integer in b.
// We have now a = 999 and b = 111 and max difference = 888
//
// Constraints:
// 1 <= num <= 108
//

class Solution {
    public int maxDiff(int num) {
        String numStr = Integer.toString(num);

        // Find maximum number
        char xMax = ' ';
        char yMax = '9';
        for (char c : numStr.toCharArray()) {
            if (c != '9') {
                xMax = c;
                break;
            }
        }
        String maxStr = (xMax == ' ') ? numStr : numStr.replace(xMax, yMax);
        int maxNum = Integer.parseInt(maxStr);

        // Find minimum number
        char xMin = ' ';
        char yMin = ' ';
        if (numStr.charAt(0) != '1') {
            xMin = numStr.charAt(0);
            yMin = '1';
        } else {
            for (char c : numStr.toCharArray()) {
                if (c != '0' && c != '1') {
                    xMin = c;
                    yMin = '0';
                    break;
                }
            }
        }
        String minStr = (xMin == ' ') ? numStr : numStr.replace(xMin, yMin);
        int minNum = Integer.parseInt(minStr);

        return maxNum - minNum;         
    }
}
