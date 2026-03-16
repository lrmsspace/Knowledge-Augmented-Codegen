// Source: https://leetcode.com/problems/double-modular-exponentiation/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed 2D array variables where variables[i] = [ai, bi, ci, mi], and an integer target.
//
// An index i is good if the following formula holds:
//
//
// 	0 <= i < variables.length
// 	((aibi % 10)ci) % mi == target
//
//
// Return an array consisting of good indices in any order.
//
// Example:
// Input: variables = [[2,3,3,10],[3,3,3,1],[6,1,1,4]], target = 2
// Output: [0,2]
// Explanation: For each index i in the variables array:
// 1) For the index 0, variables[0] = [2,3,3,10], (23 % 10)3 % 10 = 2.
// 2) For the index 1, variables[1] = [3,3,3,1], (33 % 10)3 % 1 = 0.
// 3) For the index 2, variables[2] = [6,1,1,4], (61 % 10)1 % 4 = 2.
// Therefore we return [0,2] as the answer.
//
// Constraints:
// 1 <= variables.length <= 100
// 	variables[i] == [ai, bi, ci, mi]
// 	1 <= ai, bi, ci, mi <= 103
// 	0 <= target <= 103
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getGoodIndices(int** variables, int variablesSize, int* variablesColSize, int target, int* returnSize) {
    int* result = (int*)malloc(variablesSize * sizeof(int));
    *returnSize = 0;

    for (int i = 0; i < variablesSize; i++) {
        int a = variables[i][0];
        int b = variables[i][1];
        int c = variables[i][2];
        int m = variables[i][3];

        // Compute a^b % 10
        int modBase = 10;
        int aMod = 1;
        for (int j = 0; j < b; j++) {
            aMod = (aMod * a) % modBase;
        }

        // Compute (a^b % 10)^c % m
        int finalMod = 1;
        for (int j = 0; j < c; j++) {
            finalMod = (finalMod * aMod) % m;
        }

        if (finalMod == target) {
            result[*returnSize] = i;
            (*returnSize)++;
        }
    }

    return result;      
}
