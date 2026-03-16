// Source: https://leetcode.com/problems/greatest-common-divisor-of-strings/   |   Difficulty: Easy
//
// Problem Description:
// For two strings s and t, we say "t divides s" if and only if s = t + t + t + ... + t + t (i.e., t is concatenated with itself one or more times).
//
// Given two strings str1 and str2, return the largest string x such that x divides both str1 and str2.
//
// Example:
// Input: str1 = "ABCABC", str2 = "ABC"
// Output: "ABC"
//
// Constraints:
// 1 <= str1.length, str2.length <= 1000
// 	str1 and str2 consist of English uppercase letters.
//

char* gcdOfStrings(char* str1, char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // Function to compute GCD of two numbers
    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    // Check if str1 + str2 is equal to str2 + str1
    char* concat1 = (char*)malloc(len1 + len2 + 1);
    char* concat2 = (char*)malloc(len1 + len2 + 1);
    strcpy(concat1, str1);
    strcat(concat1, str2);
    strcpy(concat2, str2);
    strcat(concat2, str1);

    if (strcmp(concat1, concat2) != 0) {
        free(concat1);
        free(concat2);
        return "";
    }

    free(concat1);
    free(concat2);

    // Compute GCD of lengths
    int gcdLen = gcd(len1, len2);

    // Return the substring of str1 from index 0 to gcdLen
    char* result = (char*)malloc(gcdLen + 1);
    strncpy(result, str1, gcdLen);
    result[gcdLen] = '\0';

    return result;      
}
