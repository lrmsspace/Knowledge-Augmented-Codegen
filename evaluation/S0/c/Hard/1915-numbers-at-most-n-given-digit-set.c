// Source: https://leetcode.com/problems/numbers-at-most-n-given-digit-set/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of digits which is sorted in non-decreasing order. You can write numbers using each digits[i] as many times as we want. For example, if digits = ['1','3','5'], we may write numbers such as '13', '551', and '1351315'.
//
// Return the number of positive integers that can be generated that are less than or equal to a given integer n.
//
// Example:
// Input: digits = ["1","3","5","7"], n = 100
// Output: 20
// Explanation: 
// The 20 numbers that can be written are:
// 1, 3, 5, 7, 11, 13, 15, 17, 31, 33, 35, 37, 51, 53, 55, 57, 71, 73, 75, 77.
//
// Constraints:
// 1 <= digits.length <= 9
// 	digits[i].length == 1
// 	digits[i] is a digit from '1' to '9'.
// 	All the values in digits are unique.
// 	digits is sorted in non-decreasing order.
// 	1 <= n <= 109
//

int atMostNGivenDigitSet(char** digits, int digitsSize, int n) {
    char nStr[11];
    int nLen = 0;
    {
        int tn = n;
        while (tn > 0) {
            nStr[nLen++] = (tn % 10) + '0';
            tn /= 10;
        }
        /* reverse nStr */
        for (int i = 0; i < nLen / 2; ++i) {
            char t = nStr[i];
            nStr[i] = nStr[nLen - 1 - i];
            nStr[nLen - 1 - i] = t;
        }
    }

    int total = 0;
    /* count numbers with fewer digits than n */
    for (int len = 1; len < nLen; ++len) {
        int count = 1;
        for (int i = 0; i < len; ++i) {
            count *= digitsSize;
        }
        total += count;
    }

    /* count numbers with the same number of digits as n */
    for (int i = 0; i < nLen; ++i) {
        int hasSameDigit = 0;
        for (int j = 0; j < digitsSize; ++j) {
            if (digits[j][0] < nStr[i]) {
                int count = 1;
                for (int k = i + 1; k < nLen; ++k) {
                    count *= digitsSize;
                }
                total += count;
            } else if (digits[j][0] == nStr[i]) {
                hasSameDigit = 1;
                break;
            }
        }
        if (!hasSameDigit) {
            return total;
        }
    }
    /* if we reach here, it means we can form n itself */
    total += 1;
    return total;       
}
