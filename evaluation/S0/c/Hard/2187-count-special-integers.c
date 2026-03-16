// Source: https://leetcode.com/problems/count-special-integers/   |   Difficulty: Hard
//
// Problem Description:
// We call a positive integer special if all of its digits are distinct.
//
// Given a positive integer n, return the number of special integers that belong to the interval [1, n].
//
// Example:
// Input: n = 20
// Output: 19
// Explanation: All the integers from 1 to 20, except 11, are special. Thus, there are 19 special integers.
//
// Constraints:
// 1 <= n <= 2 * 109
//

int countSpecialNumbers(int n) {
    int digits[10];
    int len = 0;
    int temp = n;
    while (temp > 0) {
        digits[len++] = temp % 10;
        temp /= 10;
    }
    int count = 0;
    for (int i = 1; i < len; i++) {
        int choices = 9;
        for (int j = 0; j < i - 1; j++) {
            count += choices;
            choices--;
        }
    }
    int used[10] = {0};
    for (int i = len - 1; i >= 0; i--) {
        int d = digits[i];
        for (int j = (i == len - 1) ? 1 : 0; j < d; j++) {
            if (!used[j]) {
                int choices = 10 - (len - i) - 1;
                int prod = 1;
                for (int k = 0; k < i; k++) {
                    prod *= choices;
                    choices--;
                }
                count += prod;
            }
        }
        if (used[d]) break;
        used[d] = 1;
        if (i == 0) count++;
    }
    return count;       
}
