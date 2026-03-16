// Source: https://leetcode.com/problems/remove-trailing-zeros-from-a-string/   |   Difficulty: Easy
//
// Problem Description:
// Given a positive integer num represented as a string, return the integer num without trailing zeros as a string.
//
// Example:
// Input: num = "51230100"
// Output: "512301"
// Explanation: Integer "51230100" has 2 trailing zeros, we remove them and return integer "512301".
//
// Constraints:
// 1 <= num.length <= 1000
// 	num consists of only digits.
// 	num doesn't have any leading zeros.
//

char* removeTrailingZeros(char* num) {
    int len = strlen(num);
    int i;

    // Find the position of the last non-zero character
    for (i = len - 1; i >= 0; i--) {
        if (num[i] != '0') {
            break;
        }
    }

    // If all characters are zeros, return "0"
    if (i == -1) {
        char* result = (char*)malloc(2 * sizeof(char));
        strcpy(result, "0");
        return result;
    }

    // Allocate memory for the result string
    char* result = (char*)malloc((i + 2) * sizeof(char));
    strncpy(result, num, i + 1);
    result[i + 1] = '\0';

    return result;      
}
