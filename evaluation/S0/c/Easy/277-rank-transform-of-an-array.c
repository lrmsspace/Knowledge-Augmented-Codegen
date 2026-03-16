// Source: https://leetcode.com/problems/rank-transform-of-an-array/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of integers arr, replace each element with its rank.
//
// The rank represents how large the element is. The rank has the following rules:
//
//
// 	Rank is an integer starting from 1.
// 	The larger the element, the larger the rank. If two elements are equal, their rank must be the same.
// 	Rank should be as small as possible.
//
// Example:
// Input: arr = [40,10,20,30]
// Output: [4,1,2,3]
// Explanation: 40 is the largest element. 10 is the smallest. 20 is the second smallest. 30 is the third smallest.
//
// Constraints:
// 0 <= arr.length <= 105
// 	-109 <= arr[i] <= 109
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* arrayRankTransform(int* arr, int arrSize, int* returnSize) {
    int* sorted = (int*)malloc(arrSize * sizeof(int));
    int* ranks = (int*)malloc(arrSize * sizeof(int));
    int* result = (int*)malloc(arrSize * sizeof(int));
    int i, rank = 1;

    for (i = 0; i < arrSize; i++) {
        sorted[i] = arr[i];
    }

    // Sort the array
    qsort(sorted, arrSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    // Assign ranks
    for (i = 0; i < arrSize; i++) {
        if (i == 0 || sorted[i] != sorted[i - 1]) {
            ranks[i] = rank++;
        } else {
            ranks[i] = ranks[i - 1];
        }
    }

    // Map original values to their ranks
    for (i = 0; i < arrSize; i++) {
        for (int j = 0; j < arrSize; j++) {
            if (arr[i] == sorted[j]) {
                result[i] = ranks[j];
                break;
            }
        }
    }

    free(sorted);
    free(ranks);

    *returnSize = arrSize;
    return result;      
}
