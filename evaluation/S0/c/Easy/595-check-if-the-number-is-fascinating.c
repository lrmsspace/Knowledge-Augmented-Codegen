// Source: https://leetcode.com/problems/check-if-the-number-is-fascinating/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer n that consists of exactly 3 digits.
//
// We call the number n fascinating if, after the following modification, the resulting number contains all the digits from 1 to 9 exactly once and does not contain any 0's:
//
//
// 	Concatenate n with the numbers 2 * n and 3 * n.
//
//
// Return true if n is fascinating, or false otherwise.
//
// Concatenating two numbers means joining them together. For example, the concatenation of 121 and 371 is 121371.
//
// Example:
// Input: n = 192
// Output: true
// Explanation: We concatenate the numbers n = 192 and 2 * n = 384 and 3 * n = 576. The resulting number is 192384576. This number contains all the digits from 1 to 9 exactly once.
//
// Constraints:
// 100 <= n <= 999
//

bool isFascinating(int n) {
    int count[10] = {0};
    for (int i = 1; i <= 3; i++) {
        int num = n * i;
        while (num > 0) {
            int digit = num % 10;
            if (digit == 0) {
                return false;
            }
            count[digit]++;
            num /= 10;
        }
    }
    for (int i = 1; i <= 9; i++) {
        if (count[i] != 1) {
            return false;
        }
    }
    return true;        
}
