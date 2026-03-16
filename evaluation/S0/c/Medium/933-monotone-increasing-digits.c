// Source: https://leetcode.com/problems/monotone-increasing-digits/   |   Difficulty: Medium
//
// Problem Description:
// An integer has monotone increasing digits if and only if each pair of adjacent digits x and y satisfy x <= y.
//
// Given an integer n, return the largest number that is less than or equal to n with monotone increasing digits.
//
// Example:
// Input: n = 10
// Output: 9
//
// Constraints:
// 0 <= n <= 109
//

int monotoneIncreasingDigits(int n) {
    char digits[11];
    int length = 0;

    // Convert integer to string representation
    while (n > 0) {
        digits[length++] = (n % 10) + '0';
        n /= 10;
    }

    // Reverse the string to get the correct order
    for (int i = 0; i < length / 2; ++i) {
        char temp = digits[i];
        digits[i] = digits[length - i - 1];
        digits[length - i - 1] = temp;
    }
    digits[length] = '\0';

    // Find the first decrease from left to right
    int marker = length;
    for (int i = length - 1; i > 0; --i) {
        if (digits[i] < digits[i - 1]) {
            marker = i - 1;
            digits[i - 1]--;
        }
    }

    // Set all digits after the marker to '9'
    for (int i = marker + 1; i < length; ++i) {
        digits[i] = '9';
    }

    // Handle any cascading decreases
    for (int i = marker; i > 0; --i) {
        if (digits[i] < digits[i - 1]) {
            digits[i - 1]--;
            for (int j = i; j < length; ++j) {
                digits[j] = '9';
            }
        }
    }

    // Convert back to integer
    int result = 0;
    for (int i = 0; i < length; ++i) {
        result = result * 10 + (digits[i] - '0');
    }

    return result;      
}
