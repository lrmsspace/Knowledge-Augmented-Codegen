// Source: https://leetcode.com/problems/add-binary/   |   Difficulty: Easy
//
// Problem Description:
// Given two binary strings a and b, return their sum as a binary string.
//
// Example:
// Input: a = "11", b = "1"
// Output: "100"
//
// Constraints:
// 1 <= a.length, b.length <= 104
// 	a and b consist only of '0' or '1' characters.
// 	Each string does not contain leading zeros except for the zero itself.
//

char* addBinary(char* a, char* b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int max_len = len_a > len_b ? len_a : len_b;
    char* result = (char*)malloc(max_len + 2); // +1 for possible carry, +1 for null terminator
    result[max_len + 1] = '\0';

    int carry = 0;
    int i = len_a - 1;
    int j = len_b - 1;
    int k = max_len;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) {
            sum += a[i] - '0';
            i--;
        }
        if (j >= 0) {
            sum += b[j] - '0';
            j--;
        }
        result[k] = (sum % 2) + '0';
        carry = sum / 2;
        k--;
    }

    // If there's no carry left, move the result pointer to skip leading zero
    if (k == 0) {
        return result + 1;
    }
    return result;      
}
