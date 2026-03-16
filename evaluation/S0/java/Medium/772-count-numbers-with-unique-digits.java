// Source: https://leetcode.com/problems/count-numbers-with-unique-digits/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the count of all numbers with unique digits, x, where 0 <= x < 10n.
//
// Example:
// Input: n = 2
// Output: 91
// Explanation: The answer should be the total numbers in the range of 0 ≤ x < 100, excluding 11,22,33,44,55,66,77,88,99
//
// Constraints:
// 0 <= n <= 8
//

class Solution {
    public int countNumbersWithUniqueDigits(int n) {
        if (n == 0) return 1;
        int count = 10; // for n = 1
        int uniqueDigits = 9;
        int availableNumber = 9;

        for (int i = 2; i <= n && availableNumber > 0; i++) {
            uniqueDigits *= availableNumber;
            count += uniqueDigits;
            availableNumber--;
        }

        return count;           
    }
}
