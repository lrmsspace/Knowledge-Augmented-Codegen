// Source: https://leetcode.com/problems/add-strings/   |   Difficulty: Easy
//
// Problem Description:
// Given two non-negative integers, num1 and num2 represented as string, return the sum of num1 and num2 as a string.
//
// You must solve the problem without using any built-in library for handling large integers (such as BigInteger). You must also not convert the inputs to integers directly.
//
// Example:
// Input: num1 = "11", num2 = "123"
// Output: "134"
//
// Constraints:
// 1 <= num1.length, num2.length <= 104
// 	num1 and num2 consist of only digits.
// 	num1 and num2 don't have any leading zeros except for the zero itself.
//

char* addStrings(char* num1, char* num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxLen = len1 > len2 ? len1 : len2;
    char* result = (char*)malloc(maxLen + 2); // +1 for possible carry, +1 for null terminator
    result[maxLen + 1] = '\0';

    int carry = 0;
    int i = len1 - 1;
    int j = len2 - 1;
    int k = maxLen;

    while (i >= 0 || j >= 0 || carry) {
        int digit1 = (i >= 0) ? num1[i--] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j--] - '0' : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result[k--] = (sum % 10) + '0';
    }

    // If there's no carry, move the result pointer to skip leading zero
    if (k == 0) {
        return result + 1;
    }
    return result;      
}
