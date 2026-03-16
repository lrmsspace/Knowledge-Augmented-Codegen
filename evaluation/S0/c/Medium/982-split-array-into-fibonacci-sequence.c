// Source: https://leetcode.com/problems/split-array-into-fibonacci-sequence/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string of digits num, such as "123456579". We can split it into a Fibonacci-like sequence [123, 456, 579].
//
// Formally, a Fibonacci-like sequence is a list f of non-negative integers such that:
//
//
// 	0 <= f[i] < 231, (that is, each integer fits in a 32-bit signed integer type),
// 	f.length >= 3, and
// 	f[i] + f[i + 1] == f[i + 2] for all 0 <= i < f.length - 2.
//
//
// Note that when splitting the string into pieces, each piece must not have extra leading zeroes, except if the piece is the number 0 itself.
//
// Return any Fibonacci-like sequence split from num, or return [] if it cannot be done.
//
// Example:
// Input: num = "1101111"
// Output: [11,0,11,11]
// Explanation: The output [110, 1, 111] would also be accepted.
//
// Constraints:
// 1 <= num.length <= 200
// 	num contains only digits.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* splitIntoFibonacci(char* num, int* returnSize) {
    #define MAX_LEN 200
    #define MAX_FIB_SIZE 100

    long fib[MAX_FIB_SIZE];
    int fibSize = 0;
    int len = strlen(num);

    for (int i = 1; i <= fmin(10, len - 2); i++) {
        if (num[0] == '0' && i > 1) break;
        long first = strtol(num, NULL, 10);
        if (first > INT_MAX) break;

        for (int j = 1; j <= fmin(10, len - i - 1); j++) {
            if (num[i] == '0' && j > 1) break;
            long second = strtol(num + i, NULL, 10);
            if (second > INT_MAX) break;

            fib[0] = first;
            fib[1] = second;
            fibSize = 2;

            int k = i + j;
            while (k < len) {
                long next = fib[fibSize - 1] + fib[fibSize - 2];
                if (next > INT_MAX) break;

                char nextStr[12];
                sprintf(nextStr, "%ld", next);
                int nextLen = strlen(nextStr);

                if (k + nextLen > len || strncmp(num + k, nextStr, nextLen) != 0) {
                    break;
                }

                fib[fibSize++] = next;
                k += nextLen;
            }

            if (k == len && fibSize >= 3) {
                int* result = (int*)malloc(fibSize * sizeof(int));
                for (int m = 0; m < fibSize; m++) {
                    result[m] = (int)fib[m];
                }
                *returnSize = fibSize;
                return result;
            }
        }
    }

    *returnSize = 0;
    return NULL;        
}
