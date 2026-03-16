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

int countNumbersWithUniqueDigits(int n) {
    if (n == 0) {
        return 1;
    }
    
    int count = 10; // For n = 1, we have 10 unique digit numbers: 0-9
    int uniqueDigits = 9; // First digit can be from 1-9
    int availableDigits = 9; // Remaining digits (0-9 excluding the first digit)
    
    for (int i = 2; i <= n && i <= 10; i++) {
        uniqueDigits *= availableDigits;
        count += uniqueDigits;
        availableDigits--;
    }
    
    return count;       
}
