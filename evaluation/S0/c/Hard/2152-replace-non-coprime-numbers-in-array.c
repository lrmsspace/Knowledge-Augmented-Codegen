// Source: https://leetcode.com/problems/replace-non-coprime-numbers-in-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of integers nums. Perform the following steps:
//
//
// 	Find any two adjacent numbers in nums that are non-coprime.
// 	If no such numbers are found, stop the process.
// 	Otherwise, delete the two numbers and replace them with their LCM (Least Common Multiple).
// 	Repeat this process as long as you keep finding two adjacent non-coprime numbers.
//
//
// Return the final modified array. It can be shown that replacing adjacent non-coprime numbers in any arbitrary order will lead to the same result.
//
// The test cases are generated such that the values in the final array are less than or equal to 108.
//
// Two values x and y are non-coprime if GCD(x, y) > 1 where GCD(x, y) is the Greatest Common Divisor of x and y.
//
// Example:
// Input: nums = [6,4,3,2,7,6,2]
// Output: [12,7,6]
// Explanation: 
// - (6, 4) are non-coprime with LCM(6, 4) = 12. Now, nums = [12,3,2,7,6,2].
// - (12, 3) are non-coprime with LCM(12, 3) = 12. Now, nums = [12,2,7,6,2].
// - (12, 2) are non-coprime with LCM(12, 2) = 12. Now, nums = [12,7,6,2].
// - (6, 2) are non-coprime with LCM(6, 2) = 6. Now, nums = [12,7,6].
// There are no more adjacent non-coprime numbers in nums.
// Thus, the final modified array is [12,7,6].
// Note that there are other ways to obtain the same resultant array.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
// 	The test cases are generated such that the values in the final array are less than or equal to 108.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* replaceNonCoprimes(int* nums, int numsSize, int* returnSize) {
    if (!returnSize || numsSize <= 0 || !nums) return NULL;

    /* Helper function to compute GCD using Euclidean algorithm */
    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    /* Stack to hold the processed numbers */
    int *stack = (int*)malloc(numsSize * sizeof(int));
    if (!stack) return NULL;
    int top = -1;

    for (int i = 0; i < numsSize; ++i) {
        int current = nums[i];
        while (top >= 0) {
            int g = gcd(stack[top], current);
            if (g == 1) break; /* Coprime, stop merging */
            /* Merge non-coprime numbers */
            current = (stack[top] / g) * current; /* LCM calculation */
            top--; /* Pop from stack */
        }
        stack[++top] = current; /* Push the merged or original number */
    }

    /* Prepare the result */
    int *result = (int*)malloc((top + 1) * sizeof(int));
    if (!result) {
        free(stack);
        return NULL;
    }
    for (int i = 0; i <= top; ++i) {
        result[i] = stack[i];
    }
    free(stack);

    *returnSize = top + 1;
    return result;      
}
