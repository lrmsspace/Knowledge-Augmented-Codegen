// Source: https://leetcode.com/problems/sort-the-people/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of strings names, and an array heights that consists of distinct positive integers. Both arrays are of length n.
//
// For each index i, names[i] and heights[i] denote the name and height of the ith person.
//
// Return names sorted in descending order by the people's heights.
//
// Example:
// Input: names = ["Mary","John","Emma"], heights = [180,165,170]
// Output: ["Mary","Emma","John"]
// Explanation: Mary is the tallest, followed by Emma and John.
//
// Constraints:
// n == names.length == heights.length
// 	1 <= n <= 103
// 	1 <= names[i].length <= 20
// 	1 <= heights[i] <= 105
// 	names[i] consists of lower and upper case English letters.
// 	All the values of heights are distinct.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** sortPeople(char** names, int namesSize, int* heights, int heightsSize, int* returnSize) {
    // Create an array of indices
    int* indices = (int*)malloc(namesSize * sizeof(int));
    for (int i = 0; i < namesSize; i++) {
        indices[i] = i;
    }

    // Sort indices based on corresponding heights in descending order
    for (int i = 0; i < namesSize - 1; i++) {
        for (int j = 0; j < namesSize - i - 1; j++) {
            if (heights[indices[j]] < heights[indices[j + 1]]) {
                // Swap indices
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }

    // Create the result array
    char** sortedNames = (char**)malloc(namesSize * sizeof(char*));
    for (int i = 0; i < namesSize; i++) {
        sortedNames[i] = names[indices[i]];
    }

    // Clean up
    free(indices);

    *returnSize = namesSize;
    return sortedNames;     
}
