// Source: https://leetcode.com/problems/largest-number-after-digit-swaps-by-parity/   |   Difficulty: Easy
//
// Problem Description:
// You are given a positive integer num. You may swap any two digits of num that have the same parity (i.e. both odd digits or both even digits).
//
// Return the largest possible value of num after any number of swaps.
//
// Example:
// Input: num = 1234
// Output: 3412
// Explanation: Swap the digit 3 with the digit 1, this results in the number 3214.
// Swap the digit 2 with the digit 4, this results in the number 3412.
// Note that there may be other sequences of swaps but it can be shown that 3412 is the largest possible number.
// Also note that we may not swap the digit 4 with the digit 1 since they are of different parities.
//
// Constraints:
// 1 <= num <= 109
//

int largestInteger(int num) {
    int even_digits[10], odd_digits[10];
    int even_count = 0, odd_count = 0;
    int temp = num;

    // Separate digits into even and odd arrays
    while (temp > 0) {
        int digit = temp % 10;
        if (digit % 2 == 0) {
            even_digits[even_count++] = digit;
        } else {
            odd_digits[odd_count++] = digit;
        }
        temp /= 10;
    }

    // Sort even and odd digits in descending order
    for (int i = 0; i < even_count - 1; i++) {
        for (int j = i + 1; j < even_count; j++) {
            if (even_digits[i] < even_digits[j]) {
                int swap = even_digits[i];
                even_digits[i] = even_digits[j];
                even_digits[j] = swap;
            }
        }
    }

    for (int i = 0; i < odd_count - 1; i++) {
        for (int j = i + 1; j < odd_count; j++) {
            if (odd_digits[i] < odd_digits[j]) {
                int swap = odd_digits[i];
                odd_digits[i] = odd_digits[j];
                odd_digits[j] = swap;
            }
        }
    }

    // Reconstruct the largest number
    int result = 0;
    int even_index = 0, odd_index = 0;
    temp = num;

    while (temp > 0) {
        int digit = temp % 10;
        if (digit % 2 == 0) {
            result += even_digits[even_index++] * pow(10, (int)log10(num) - (int)log10(temp));
        } else {
            result += odd_digits[odd_index++] * pow(10, (int)log10(num) - (int)log10(temp));
        }
        temp /= 10;
    }

    return result;      
}
