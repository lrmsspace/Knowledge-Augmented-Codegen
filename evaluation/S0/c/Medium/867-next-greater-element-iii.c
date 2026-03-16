// Source: https://leetcode.com/problems/next-greater-element-iii/   |   Difficulty: Medium
//
// Problem Description:
// Given a positive integer n, find the smallest integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive integer exists, return -1.
//
// Note that the returned integer should fit in 32-bit integer, if there is a valid answer but it does not fit in 32-bit integer, return -1.
//
// Example:
// Input: n = 12
// Output: 21
//
// Constraints:
// 1 <= n <= 231 - 1
//

int nextGreaterElement(int n) {
    char digits[10];
    int len = 0;
    int original_n = n;

    // Extract digits from n and store them in reverse order
    while (n > 0) {
        digits[len++] = (n % 10) + '0';
        n /= 10;
    }

    // Find the first decreasing element from the right
    int i;
    for (i = 1; i < len; i++) {
        if (digits[i] < digits[i - 1]) {
            break;
        }
    }

    // If no such element is found, return -1
    if (i == len) {
        return -1;
    }

    // Find the smallest digit on right side of (i-1)'th digit that is larger than digits[i]
    int j;
    for (j = 0; j < i; j++) {
        if (digits[j] > digits[i]) {
            break;
        }
    }

    // Swap the found digits
    char temp = digits[i];
    digits[i] = digits[j];
    digits[j] = temp;

    // Sort the digits to the right of (i-1) in ascending order
    for (int x = 0; x < i / 2; x++) {
        temp = digits[x];
        digits[x] = digits[i - 1 - x];
        digits[i - 1 - x] = temp;
    }

    // Reconstruct the number from digits
    long long result = 0;
    for (int k = len - 1; k >= 0; k--) {
        result = result * 10 + (digits[k] - '0');
        if (result > INT32_MAX) {
            return -1;
        }
    }

    return (result > original_n) ? (int)result : -1;        
}
