// Source: https://leetcode.com/problems/maximum-difference-by-remapping-a-digit/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer num. You know that Bob will sneakily remap one of the 10 possible digits (0 to 9) to another digit.
//
// Return the difference between the maximum and minimum values Bob can make by remapping exactly one digit in num.
//
// 	The resulting number after remapping can contain leading zeroes.
//
// Example:
// Input: num = 11891
// Output: 99009
// Explanation: 
// To achieve the maximum value, Bob can remap the digit 1 to the digit 9 to yield 99899.
// To achieve the minimum value, Bob can remap the digit 1 to the digit 0, yielding 890.
// The difference between these two numbers is 99009.
//
// Constraints:
// 1 <= num <= 108
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minMaxDifference(int num) {
    char numStr[12];
    snprintf(numStr, sizeof(numStr), "%d", num);

    // Calculate maximum value
    char maxStr[12];
    strcpy(maxStr, numStr);
    char toReplaceMax = '\0';
    for (int i = 0; maxStr[i] != '\0'; i++) {
        if (maxStr[i] != '9') {
            toReplaceMax = maxStr[i];
            break;
        }
    }
    if (toReplaceMax != '\0') {
        for (int i = 0; maxStr[i] != '\0'; i++) {
            if (maxStr[i] == toReplaceMax) {
                maxStr[i] = '9';
            }
        }
    }
    int maxValue = atoi(maxStr);

    // Calculate minimum value
    char minStr[12];
    strcpy(minStr, numStr);
    char toReplaceMin = '\0';
    for (int i = 0; minStr[i] != '\0'; i++) {
        if (i == 0 && minStr[i] != '1') {
            toReplaceMin = minStr[i];
            break;
        } else if (i > 0 && minStr[i] != '0' && minStr[i] != minStr[0]) {
            toReplaceMin = minStr[i];
            break;
        }
    }
    if (toReplaceMin != '\0') {
        char replacementChar = (minStr[0] == toReplaceMin) ? '1' : '0';
        for (int i = 0; minStr[i] != '\0'; i++) {
            if (minStr[i] == toReplaceMin) {
                minStr[i] = replacementChar;
            }
        }
    }
    int minValue = atoi(minStr);

    return maxValue - minValue;     
}
