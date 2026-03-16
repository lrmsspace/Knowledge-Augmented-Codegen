// Source: https://leetcode.com/problems/self-dividing-numbers/   |   Difficulty: Easy
//
// Problem Description:
// A self-dividing number is a number that is divisible by every digit it contains.
//
//
// 	For example, 128 is a self-dividing number because 128 % 1 == 0, 128 % 2 == 0, and 128 % 8 == 0.
//
//
// A self-dividing number is not allowed to contain the digit zero.
//
// Given two integers left and right, return a list of all the self-dividing numbers in the range [left, right] (both inclusive).
//
// Example:
// Input: left = 1, right = 22
// Output: [1,2,3,4,5,6,7,8,9,11,12,15,22]
//
// Constraints:
// 1 <= left <= right <= 104
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* selfDividingNumbers(int left, int right, int* returnSize) {
    int *result = (int *)malloc(sizeof(int) * (right - left + 1));
    int count = 0;

    for (int num = left; num <= right; num++) {
        int temp = num;
        int isSelfDividing = 1;

        while (temp > 0) {
            int digit = temp % 10;
            if (digit == 0 || num % digit != 0) {
                isSelfDividing = 0;
                break;
            }
            temp /= 10;
        }

        if (isSelfDividing) {
            result[count++] = num;
        }
    }

    *returnSize = count;
    return result;      
}
