// Source: https://leetcode.com/problems/minimum-operations-to-make-a-special-number/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string num representing a non-negative integer.
//
// In one operation, you can pick any digit of num and delete it. Note that if you delete all the digits of num, num becomes 0.
//
// Return the minimum number of operations required to make num special.
//
// An integer x is considered special if it is divisible by 25.
//
// Example:
// Input: num = "2245047"
// Output: 2
// Explanation: Delete digits num[5] and num[6]. The resulting number is "22450" which is special since it is divisible by 25.
// It can be shown that 2 is the minimum number of operations required to get a special number.
//
// Constraints:
// 1 <= num.length <= 100
// 	num only consists of digits '0' through '9'.
// 	num does not contain any leading zeros.
//

class Solution {
    public int minimumOperations(String num) {
        String[] targets = {"00", "25", "50", "75"};
        int minOperations = Integer.MAX_VALUE;

        for (String target : targets) {
            int operations = 0;
            int j = num.length() - 1;

            // Find the last digit of the target
            while (j >= 0 && num.charAt(j) != target.charAt(1)) {
                operations++;
                j--;
            }

            // If we didn't find the last digit, skip to the next target
            if (j < 0) continue;

            j--; // Move to the next position for finding the first digit

            // Find the first digit of the target
            while (j >= 0 && num.charAt(j) != target.charAt(0)) {
                operations++;
                j--;
            }

            // If we found both digits, update the minimum operations
            if (j >= 0) {
                minOperations = Math.min(minOperations, operations);
            }
        }

        return minOperations == Integer.MAX_VALUE ? num.length() : minOperations;           
    }
}
