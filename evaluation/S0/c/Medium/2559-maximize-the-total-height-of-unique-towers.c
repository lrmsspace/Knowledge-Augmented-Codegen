// Source: https://leetcode.com/problems/maximize-the-total-height-of-unique-towers/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array maximumHeight, where maximumHeight[i] denotes the maximum height the ith tower can be assigned.
//
// Your task is to assign a height to each tower so that:
//
//
// 	The height of the ith tower is a positive integer and does not exceed maximumHeight[i].
// 	No two towers have the same height.
//
//
// Return the maximum possible total sum of the tower heights. If it's not possible to assign heights, return -1.
//
// Example:
// Input: maximumHeight = [2,3,4,3]
//
// Output: 10
//
// Explanation:
//
// We can assign heights in the following way: [1, 2, 4, 3].
//
// Constraints:
// 1 <= maximumHeight.length <= 105
// 	1 <= maximumHeight[i] <= 109
//

long long maximumTotalSum(int* maximumHeight, int maximumHeightSize) {
    // Sort the maximumHeight array in descending order
    qsort(maximumHeight, maximumHeightSize, sizeof(int), [](const void* a, const void* b) {
        return (*(int*)b - *(int*)a);
    });

    long long totalSum = 0;
    long long currentMaxHeight = (long long)maximumHeight[0] + 1; // Start with one more than the first tower's max height

    for (int i = 0; i < maximumHeightSize; i++) {
        if (currentMaxHeight > 1) {
            currentMaxHeight = (long long)maximumHeight[i] < currentMaxHeight - 1 ? (long long)maximumHeight[i] : currentMaxHeight - 1;
            totalSum += currentMaxHeight;
        } else {
            return -1; // Not possible to assign unique heights
        }
    }

    return totalSum;        
}
