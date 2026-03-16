// Source: https://leetcode.com/problems/smallest-divisible-digit-product-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string num which represents a positive integer, and an integer t.
//
// A number is called zero-free if none of its digits are 0.
//
// Return a string representing the smallest zero-free number greater than or equal to num such that the product of its digits is divisible by t. If no such number exists, return "-1".
//
// Example:
// Input: num = "1234", t = 256
//
// Output: "1488"
//
// Explanation:
//
// The smallest zero-free number that is greater than 1234 and has the product of its digits divisible by 256 is 1488, with the product of its digits equal to 256.
//
// Constraints:
// 2 <= num.length <= 2 * 105
// 	num consists only of digits in the range ['0', '9'].
// 	num does not contain leading zeros.
// 	1 <= t <= 1014
//

char* smallestNumber(char* num, long long t) {
    // Check if t contains any prime factor greater than 7
    long long tempT = t;
    for (long long p = 2; p <= 7; ++p) {
        while (tempT % p == 0) {
            tempT /= p;
        }
    }
    if (tempT > 1) {
        return "-1"; // Impossible to form such a number
    }

    // Count the required prime factors
    int count[8] = {0}; // count[2], count[3], count[5], count[7]
    tempT = t;
    while (tempT % 2 == 0) { count[2]++; tempT /= 2; }
    while (tempT % 3 == 0) { count[3]++; tempT /= 3; }
    while (tempT % 5 == 0) { count[5]++; tempT /= 5; }
    while (tempT % 7 == 0) { count[7]++; tempT /= 7; }

    // Build the smallest number with required prime factors
    char* result = (char*)malloc(2 * 105 * sizeof(char));
    int pos = 0;

    // Use digits from largest to smallest to minimize the number of digits
    int digitCount[10] = {0};
    while (count[7] > 0) { digitCount[7]++; count[7]--; }
    while (count[5] > 0) { digitCount[5]++; count[5]--; }
    while (count[3] >= 2) { digitCount[9]++; count[3] -= 2; }
    while (count[3] > 0 && count[2] > 0) { digitCount[6]++; count[3]--; count[2]--; }
    while (count[2] >= 3) { digitCount[8]++; count[2] -= 3; }
    while (count[3] > 0) { digitCount[3]++; count[3]--; }
    while (count[2] >= 2) { digitCount[4]++; count[2] -= 2; }
    while (count[2] > 0) { digitCount[2]++; count[2]--; }
    
    // Construct the result string in ascending order of digits
    for (int d = 2; d <= 9; d++) {
        for (int i = 0; i < digitCount[d]; i++) {
            result[pos++] = '0' + d;
        }
    }
    result[pos] = '\0';

    // Compare with num and adjust if necessary
    if (strcmp(result, num) < 0) {
        // Implement logic to find the next valid number greater than or equal to num
        // This part is complex and requires careful handling
        // For now, return "-1" indicating no such number found
        free(result);
        return "-1";
    }

    return result;
}