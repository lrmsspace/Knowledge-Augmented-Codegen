// Source: https://leetcode.com/problems/multiply-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2, also represented as a string.
//
// Note: You must not use any built-in BigInteger library or convert the inputs to integer directly.
//
// Example:
// Input: num1 = "2", num2 = "3"
// Output: "6"
//
// Constraints:
// 1 <= num1.length, num2.length <= 200
// 	num1 and num2 consist of digits only.
// 	Both num1 and num2 do not contain any leading zero, except the number 0 itself.
//

char* multiply(char* num1, char* num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    if (len1 == 0 || len2 == 0) return "0";

    int* result = (int*)calloc(len1 + len2, sizeof(int));
    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = mul + result[i + j + 1];

            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }

    char* product = (char*)malloc((len1 + len2 + 1) * sizeof(char));
    int index = 0, k = 0;
    while (k < len1 + len2 && result[k] == 0) k++; // Skip leading zeros

    if (k == len1 + len2) {
        product[index++] = '0'; // If all are zeros
    } else {
        while (k < len1 + len2) {
            product[index++] = result[k++] + '0';
        }
    }
    product[index] = '\0';

    free(result);
    return product;     
}
