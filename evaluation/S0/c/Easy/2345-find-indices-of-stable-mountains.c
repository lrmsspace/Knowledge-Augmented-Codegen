// Source: https://leetcode.com/problems/find-indices-of-stable-mountains/   |   Difficulty: Easy
//
// Problem Description:
// There are n mountains in a row, and each mountain has a height. You are given an integer array height where height[i] represents the height of mountain i, and an integer threshold.
//
// A mountain is called stable if the mountain just before it (if it exists) has a height strictly greater than threshold. Note that mountain 0 is not stable.
//
// Return an array containing the indices of all stable mountains in any order.
//
// Example:
// Input: height = [1,2,3,4,5], threshold = 2
//
// Output: [3,4]
//
// Explanation:
//
//
// 	Mountain 3 is stable because height[2] == 3 is greater than threshold == 2.
// 	Mountain 4 is stable because height[3] == 4 is greater than threshold == 2.
//
// Constraints:
// 2 <= n == height.length <= 100
// 	1 <= height[i] <= 100
// 	1 <= threshold <= 100
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* stableMountains(int* height, int heightSize, int threshold, int* returnSize) {
    int* result = (int*)malloc(heightSize * sizeof(int));
    int count = 0;

    for (int i = 1; i < heightSize; i++) {
        if (height[i - 1] > threshold) {
            result[count++] = i;
        }
    }

    *returnSize = count;
    return result;      
}
