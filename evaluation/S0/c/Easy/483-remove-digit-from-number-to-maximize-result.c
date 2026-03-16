// Source: https://leetcode.com/problems/remove-digit-from-number-to-maximize-result/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string number representing a positive integer and a character digit.
//
// Return the resulting string after removing exactly one occurrence of digit from number such that the value of the resulting string in decimal form is maximized. The test cases are generated such that digit occurs at least once in number.
//
// Example:
// Input: number = "123", digit = "3"
// Output: "12"
// Explanation: There is only one '3' in "123". After removing '3', the result is "12".
//
// Constraints:
// 2 <= number.length <= 100
// 	number consists of digits from '1' to '9'.
// 	digit is a digit from '1' to '9'.
// 	digit occurs at least once in number.
//

char* removeDigit(char* number, char digit) {
    int len = strlen(number);
    char* result = NULL;

    for (int i = 0; i < len; i++) {
        if (number[i] == digit) {
            // Create a new string by removing the digit at index i
            char* candidate = (char*)malloc(len); // len - 1 + 1 for null terminator
            strncpy(candidate, number, i);
            strcpy(candidate + i, number + i + 1);

            // Compare with the current result
            if (result == NULL || strcmp(candidate, result) > 0) {
                free(result);
                result = candidate;
            } else {
                free(candidate);
            }
        }
    }

    return result;      
}
