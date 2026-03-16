// Source: https://leetcode.com/problems/k-th-smallest-prime-fraction/   |   Difficulty: Medium
//
// Problem Description:
// You are given a sorted integer array arr containing 1 and prime numbers, where all the integers of arr are unique. You are also given an integer k.
//
// For every i and j where 0 <= i < j < arr.length, we consider the fraction arr[i] / arr[j].
//
// Return the kth smallest fraction considered. Return your answer as an array of integers of size 2, where answer[0] == arr[i] and answer[1] == arr[j].
//
// Example:
// Input: arr = [1,2,3,5], k = 3
// Output: [2,5]
// Explanation: The fractions to be considered in sorted order are:
// 1/5, 1/3, 2/5, 1/2, 3/5, and 2/3.
// The third fraction is 2/5.
//
// Constraints:
// 2 <= arr.length <= 1000
// 	1 <= arr[i] <= 3 * 104
// 	arr[0] == 1
// 	arr[i] is a prime number for i > 0.
// 	All the numbers of arr are unique and sorted in strictly increasing order.
// 	1 <= k <= arr.length * (arr.length - 1) / 2
//
//
//  
// Follow up: Can you solve the problem with better than O(n2) complexity?
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* kthSmallestPrimeFraction(int* arr, int arrSize, int k, int* returnSize) {
    int left_numerator = 0, left_denominator = 1;
    int right_numerator = 1, right_denominator = 1;
    int *result = (int *)malloc(2 * sizeof(int));
    *returnSize = 2;

    while (1) {
        int count = 0;
        int max_numerator = 0;
        int max_denominator = 1;

        for (int i = 0, j = 1; j < arrSize; ++j) {
            while (i < j && arr[i] * right_denominator < arr[j] * right_numerator) {
                ++i;
            }
            count += i;

            if (i > 0) {
                if (max_numerator * arr[j] < arr[i - 1] * max_denominator) {
                    max_numerator = arr[i - 1];
                    max_denominator = arr[j];
                }
            }
        }

        if (count == k) {
            result[0] = max_numerator;
            result[1] = max_denominator;
            return result;
        } else if (count < k) {
            left_numerator = max_numerator;
            left_denominator = max_denominator;
        } else {
            right_numerator = max_numerator;
            right_denominator = max_denominator;
        }
    }    
}
