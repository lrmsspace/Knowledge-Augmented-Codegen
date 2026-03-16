// Source: https://leetcode.com/problems/sum-of-subarray-minimums/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. Since the answer may be large, return the answer modulo 109 + 7.
//
// Example:
// Input: arr = [3,1,2,4]
// Output: 17
// Explanation: 
// Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4]. 
// Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
// Sum is 17.
//
// Constraints:
// 1 <= arr.length <= 3 * 104
// 	1 <= arr[i] <= 3 * 104
//

int sumSubarrayMins(int* arr, int arrSize) {
    int MOD = 1e9 + 7;
    int *stack = (int *)malloc(sizeof(int) * (arrSize + 1));
    int top = -1;
    long long result = 0;

    for (int i = 0; i <= arrSize; i++) {
        int currentValue = (i < arrSize) ? arr[i] : 0;

        while (top != -1 && arr[stack[top]] > currentValue) {
            int midIndex = stack[top--];
            int leftIndex = (top == -1) ? -1 : stack[top];
            int rightIndex = i;

            long long countLeft = midIndex - leftIndex;
            long long countRight = rightIndex - midIndex;
            long long contribution = (countLeft * countRight) % MOD * arr[midIndex] % MOD;

            result = (result + contribution) % MOD;
        }

        stack[++top] = i;
    }

    free(stack);
    return (int)result;     
}
