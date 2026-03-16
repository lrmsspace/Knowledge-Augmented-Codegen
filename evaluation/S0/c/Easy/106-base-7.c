// Source: https://leetcode.com/problems/base-7/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer num, return a string of its base 7 representation.
//
// Example:
// Input: num = 100
// Output: "202"
//
// Constraints:
// -107 <= num <= 107
//

char* convertToBase7(int num) {
    if (num == 0) {
        char* result = (char*)malloc(2 * sizeof(char));
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    int isNegative = num < 0 ? 1 : 0;
    if (isNegative) {
        num = -num;
    }

    char buffer[32];
    int index = 0;

    while (num > 0) {
        int remainder = num % 7;
        buffer[index++] = '0' + remainder;
        num /= 7;
    }

    if (isNegative) {
        buffer[index++] = '-';
    }

    char* result = (char*)malloc((index + 1) * sizeof(char));
    for (int i = 0; i < index; i++) {
        result[i] = buffer[index - 1 - i];
    }
    result[index] = '\0';

    return result;      
}
