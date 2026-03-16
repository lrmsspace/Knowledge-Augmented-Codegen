// Source: https://leetcode.com/problems/convert-a-number-to-hexadecimal/   |   Difficulty: Easy
//
// Problem Description:
// Given a 32-bit integer num, return a string representing its hexadecimal representation. For negative integers, two’s complement method is used.
//
// All the letters in the answer string should be lowercase characters, and there should not be any leading zeros in the answer except for the zero itself.
//
// Note: You are not allowed to use any built-in library method to directly solve this problem.
//
// Example:
// Input: num = 26
// Output: "1a"
//
// Constraints:
// -231 <= num <= 231 - 1
//

char* toHex(int num) {
    if (num == 0) {
        char* result = (char*)malloc(2 * sizeof(char));
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    const char hexChars[] = "0123456789abcdef";
    char buffer[9]; // Maximum 8 hex digits + null terminator
    int index = 8;  // Start from the end of the buffer
    buffer[index] = '\0';

    unsigned int n = (unsigned int)num; // Handle negative numbers using two's complement

    while (n > 0) {
        index--;
        buffer[index] = hexChars[n & 0xF]; // Get the last 4 bits
        n >>= 4; // Shift right by 4 bits
    }

    // Allocate memory for the result string
    int length = 8 - index;
    char* result = (char*)malloc((length + 1) * sizeof(char));
    strcpy(result, &buffer[index]);

    return result;      
}
