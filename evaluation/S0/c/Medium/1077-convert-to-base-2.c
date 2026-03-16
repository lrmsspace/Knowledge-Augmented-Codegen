// Source: https://leetcode.com/problems/convert-to-base-2/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return a binary string representing its representation in base -2.
//
// Note that the returned string should not have leading zeros unless the string is "0".
//
// Example:
// Input: n = 2
// Output: "110"
// Explantion: (-2)2 + (-2)1 = 2
//
// Constraints:
// 0 <= n <= 109
//

char* baseNeg2(int n) {
    if (n == 0) return "0";

    char* result = (char*)malloc(32 * sizeof(char));
    int index = 0;

    while (n != 0) {
        int remainder = n % -2;
        n /= -2;

        if (remainder < 0) {
            remainder += 2;
            n += 1;
        }

        result[index++] = remainder + '0';
    }

    // Reverse the result string
    for (int i = 0; i < index / 2; i++) {
        char temp = result[i];
        result[i] = result[index - i - 1];
        result[index - i - 1] = temp;
    }

    result[index] = '\0';
    return result;      
}
