// Source: https://leetcode.com/problems/relative-ranks/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array score of size n, where score[i] is the score of the ith athlete in a competition. All the scores are guaranteed to be unique.
//
// The athletes are placed based on their scores, where the 1st place athlete has the highest score, the 2nd place athlete has the 2nd highest score, and so on. The placement of each athlete determines their rank:
//
//
// 	The 1st place athlete's rank is "Gold Medal".
// 	The 2nd place athlete's rank is "Silver Medal".
// 	The 3rd place athlete's rank is "Bronze Medal".
// 	For the 4th place to the nth place athlete, their rank is their placement number (i.e., the xth place athlete's rank is "x").
//
//
// Return an array answer of size n where answer[i] is the rank of the ith athlete.
//
// Example:
// Input: score = [5,4,3,2,1]
// Output: ["Gold Medal","Silver Medal","Bronze Medal","4","5"]
// Explanation: The placements are [1st, 2nd, 3rd, 4th, 5th].
//
// Constraints:
// n == score.length
// 	1 <= n <= 104
// 	0 <= score[i] <= 106
// 	All the values in score are unique.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findRelativeRanks(int* score, int scoreSize, int* returnSize) {
    // Create an array of indices
    int* indices = (int*)malloc(scoreSize * sizeof(int));
    for (int i = 0; i < scoreSize; i++) {
        indices[i] = i;
    }

    // Sort indices based on corresponding scores in descending order
    for (int i = 0; i < scoreSize - 1; i++) {
        for (int j = i + 1; j < scoreSize; j++) {
            if (score[indices[i]] < score[indices[j]]) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    // Prepare the result array
    char** result = (char**)malloc(scoreSize * sizeof(char*));
    for (int i = 0; i < scoreSize; i++) {
        result[i] = (char*)malloc(12 * sizeof(char)); // Enough to hold "Gold Medal" and numbers
    }

    // Assign ranks based on sorted indices
    for (int rank = 0; rank < scoreSize; rank++) {
        int idx = indices[rank];
        if (rank == 0) {
            strcpy(result[idx], "Gold Medal");
        } else if (rank == 1) {
            strcpy(result[idx], "Silver Medal");
        } else if (rank == 2) {
            strcpy(result[idx], "Bronze Medal");
        } else {
            sprintf(result[idx], "%d", rank + 1);
        }
    }

    free(indices);
    *returnSize = scoreSize;
    return result;      
}
