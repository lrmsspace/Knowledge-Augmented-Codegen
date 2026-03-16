// Source: https://leetcode.com/problems/minimum-sum-of-four-digit-number-after-splitting-digits/   |   Difficulty: Easy
//
// Problem Description:
// You are given a positive integer num consisting of exactly four digits. Split num into two new integers new1 and new2 by using the digits found in num. Leading zeros are allowed in new1 and new2, and all the digits found in num must be used.
//
//
// 	For example, given num = 2932, you have the following digits: two 2's, one 9 and one 3. Some of the possible pairs [new1, new2] are [22, 93], [23, 92], [223, 9] and [2, 329].
//
//
// Return the minimum possible sum of new1 and new2.
//
// Example:
// Input: num = 2932
// Output: 52
// Explanation: Some possible pairs [new1, new2] are [29, 23], [223, 9], etc.
// The minimum sum can be obtained by the pair [29, 23]: 29 + 23 = 52.
//
// Constraints:
// 1000 <= num <= 9999
//

int minimumSum(int num) {
    int digits[4];
    for (int i = 0; i < 4; i++) {
        digits[i] = num % 10;
        num /= 10;
    }

    // Simple bubble sort for 4 elements
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i; j++) {
            if (digits[j] > digits[j + 1]) {
                int temp = digits[j];
                digits[j] = digits[j + 1];
                digits[j + 1] = temp;
            }
        }
    }

    int new1 = digits[0] * 10 + digits[2];
    int new2 = digits[1] * 10 + digits[3];

    return new1 + new2;     
}
