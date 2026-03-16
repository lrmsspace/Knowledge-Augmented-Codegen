// Source: https://leetcode.com/problems/count-symmetric-integers/   |   Difficulty: Easy
//
// Problem Description:
// You are given two positive integers low and high.
//
// An integer x consisting of 2 * n digits is symmetric if the sum of the first n digits of x is equal to the sum of the last n digits of x. Numbers with an odd number of digits are never symmetric.
//
// Return the number of symmetric integers in the range [low, high].
//
// Example:
// Input: low = 1, high = 100
// Output: 9
// Explanation: There are 9 symmetric integers between 1 and 100: 11, 22, 33, 44, 55, 66, 77, 88, and 99.
//
// Constraints:
// 1 <= low <= high <= 104
//

int countSymmetricIntegers(int low, int high) {
    int count = 0;

    for (int num = low; num <= high; num++) {
        char str[6];
        sprintf(str, "%d", num);
        int len = strlen(str);

        if (len % 2 != 0) {
            continue; // Skip numbers with odd number of digits
        }

        int half = len / 2;
        int sum1 = 0, sum2 = 0;

        for (int i = 0; i < half; i++) {
            sum1 += str[i] - '0';
            sum2 += str[i + half] - '0';
        }

        if (sum1 == sum2) {
            count++;
        }
    }

    return count;       
}
