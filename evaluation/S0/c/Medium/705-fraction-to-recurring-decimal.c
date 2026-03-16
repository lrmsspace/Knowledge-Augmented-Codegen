// Source: https://leetcode.com/problems/fraction-to-recurring-decimal/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.
//
// If the fractional part is repeating, enclose the repeating part in parentheses
//
// If multiple answers are possible, return any of them.
//
// It is guaranteed that the length of the answer string is less than 104 for all the given inputs.
//
// Note that if the fraction can be represented as a finite length string, you must return it.
//
// Example:
// Input: numerator = 1, denominator = 2
// Output: "0.5"
//
// Constraints:
// -231 <= numerator, denominator <= 231 - 1
// 	denominator != 0
//

char* fractionToDecimal(int numerator, int denominator) {
    if (numerator == 0) return "0";

    char* result = (char*)malloc(20500 * sizeof(char));
    int index = 0;

    // Handle sign
    if ((numerator < 0) ^ (denominator < 0)) {
        result[index++] = '-';
    }

    // Convert to long long to avoid overflow
    long long n = llabs((long long)numerator);
    long long d = llabs((long long)denominator);

    // Integer part
    long long integerPart = n / d;
    index += sprintf(result + index, "%lld", integerPart);

    // Remainder
    long long remainder = n % d;
    if (remainder == 0) {
        result[index] = '\0';
        return result;
    }

    result[index++] = '.';

    // Map to store remainder positions
    int* remainderMap = (int*)calloc(d, sizeof(int));
    int pos = index;

    while (remainder != 0) {
        if (remainderMap[remainder] != 0) {
            int insertPos = remainderMap[remainder];
            // Insert parentheses
            for (int i = index; i >= insertPos; i--) {
                result[i + 1] = result[i];
            }
            result[insertPos] = '(';
            index++;
            result[index++] = ')';
            break;
        }

        remainderMap[remainder] = pos++;

        remainder *= 10;
        long long digit = remainder / d;
        result[index++] = '0' + digit;
        remainder %= d;
    }

    result[index] = '\0';
    free(remainderMap);
    return result;      
}
