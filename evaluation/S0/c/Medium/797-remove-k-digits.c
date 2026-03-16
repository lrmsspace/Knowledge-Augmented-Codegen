// Source: https://leetcode.com/problems/remove-k-digits/   |   Difficulty: Medium
//
// Problem Description:
// Given string num representing a non-negative integer num, and an integer k, return the smallest possible integer after removing k digits from num.
//
// Example:
// Input: num = "1432219", k = 3
// Output: "1219"
// Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
//
// Constraints:
// 1 <= k <= num.length <= 105
// 	num consists of only digits.
// 	num does not have any leading zeros except for the zero itself.
//

char* removeKdigits(char* num, int k) {
    int len = strlen(num);
    if (k >= len) return "0";

    char* stack = (char*)malloc((len + 1) * sizeof(char));
    int top = -1;

    for (int i = 0; i < len; i++) {
        while (top >= 0 && k > 0 && stack[top] > num[i]) {
            top--;
            k--;
        }
        stack[++top] = num[i];
    }

    // If there are still digits to remove, remove from the end
    top -= k;

    // Remove leading zeros
    int start = 0;
    while (start <= top && stack[start] == '0') {
        start++;
    }

    // If all digits are removed, return "0"
    if (start > top) {
        free(stack);
        return "0";
    }

    // Create the result string
    int resultLen = top - start + 1;
    char* result = (char*)malloc((resultLen + 1) * sizeof(char));
    strncpy(result, stack + start, resultLen);
    result[resultLen] = '\0';

    free(stack);
    return result;      
}
