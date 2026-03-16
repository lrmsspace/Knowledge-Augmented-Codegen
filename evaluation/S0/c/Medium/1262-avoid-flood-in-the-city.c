// Source: https://leetcode.com/problems/avoid-flood-in-the-city/   |   Difficulty: Medium
//
// Problem Description:
// Your country has an infinite number of lakes. Initially, all the lakes are empty, but when it rains over the nth lake, the nth lake becomes full of water. If it rains over a lake that is full of water, there will be a flood. Your goal is to avoid floods in any lake.
//
// Given an integer array rains where:
//
//
// 	rains[i] > 0 means there will be rains over the rains[i] lake.
// 	rains[i] == 0 means there are no rains this day and you can choose one lake this day and dry it.
//
//
// Return an array ans where:
//
//
// 	ans.length == rains.length
// 	ans[i] == -1 if rains[i] > 0.
// 	ans[i] is the lake you choose to dry in the ith day if rains[i] == 0.
//
//
// If there are multiple valid answers return any of them. If it is impossible to avoid flood return an empty array.
//
// Notice that if you chose to dry a full lake, it becomes empty, but if you chose to dry an empty lake, nothing changes.
//
// Example:
// Input: rains = [1,2,3,4]
// Output: [-1,-1,-1,-1]
// Explanation: After the first day full lakes are [1]
// After the second day full lakes are [1,2]
// After the third day full lakes are [1,2,3]
// After the fourth day full lakes are [1,2,3,4]
// There's no day to dry any lake and there is no flood in any lake.
//
// Constraints:
// 1 <= rains.length <= 105
// 	0 <= rains[i] <= 109
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* avoidFlood(int* rains, int rainsSize, int* returnSize) {
    int *res = (int *)malloc(sizeof(int) * rainsSize);
    int *full = (int *)calloc(rainsSize + 1, sizeof(int));
    int *dry = (int *)malloc(sizeof(int) * rainsSize);
    int drySize = 0;
    int i, lake, j;

    for (i = 0; i < rainsSize; i++) {
        lake = rains[i];
        if (lake == 0) {
            dry[drySize++] = i;
            res[i] = 1; // default value
        } else {
            if (full[lake]) {
                // need to dry this lake before
                int found = 0;
                for (j = 0; j < drySize; j++) {
                    if (dry[j] > full[lake]) {
                        res[dry[j]] = lake; // dry this lake
                        // remove dry[j] from dry array
                        dry[j] = dry[drySize - 1];
                        drySize--;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    // cannot find a day to dry this lake
                    free(res);
                    free(full);
                    free(dry);
                    *returnSize = 0;
                    return NULL;
                }
            }
            full[lake] = i; // mark this lake as full
            res[i] = -1;
        }
    }

    free(full);
    free(dry);
    *returnSize = rainsSize;
    return res;     
}
