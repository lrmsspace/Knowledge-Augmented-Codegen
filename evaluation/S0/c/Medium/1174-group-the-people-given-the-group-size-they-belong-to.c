// Source: https://leetcode.com/problems/group-the-people-given-the-group-size-they-belong-to/   |   Difficulty: Medium
//
// Problem Description:
// There are n people that are split into some unknown number of groups. Each person is labeled with a unique ID from 0 to n - 1.
//
// You are given an integer array groupSizes, where groupSizes[i] is the size of the group that person i is in. For example, if groupSizes[1] = 3, then person 1 must be in a group of size 3.
//
// Return a list of groups such that each person i is in a group of size groupSizes[i].
//
// Each person should appear in exactly one group, and every person must be in a group. If there are multiple answers, return any of them. It is guaranteed that there will be at least one valid solution for the given input.
//
// Example:
// Input: groupSizes = [3,3,3,3,3,1,3]
// Output: [[5],[0,1,2],[3,4,6]]
// Explanation: 
// The first group is [5]. The size is 1, and groupSizes[5] = 1.
// The second group is [0,1,2]. The size is 3, and groupSizes[0] = groupSizes[1] = groupSizes[2] = 3.
// The third group is [3,4,6]. The size is 3, and groupSizes[3] = groupSizes[4] = groupSizes[6] = 3.
// Other possible solutions are [[2,1,6],[5],[0,4,3]] and [[5],[0,6,2],[4,3,1]].
//
// Constraints:
// groupSizes.length == n
// 	1 <= n <= 500
// 	1 <= groupSizes[i] <= n
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** groupThePeople(int* groupSizes, int groupSizesSize, int* returnSize, int** returnColumnSizes) {
    int** result = (int**)malloc(sizeof(int*) * groupSizesSize);
    *returnColumnSizes = (int*)malloc(sizeof(int) * groupSizesSize);
    int returnCount = 0;

    // Map to hold groups based on their sizes
    typedef struct {
        int* members;
        int count;
        int capacity;
    } Group;

    Group* groups = (Group*)calloc(groupSizesSize + 1, sizeof(Group));

    for (int i = 0; i < groupSizesSize; i++) {
        int size = groupSizes[i];
        if (groups[size].members == NULL) {
            groups[size].capacity = size;
            groups[size].members = (int*)malloc(sizeof(int) * size);
            groups[size].count = 0;
        }

        groups[size].members[groups[size].count++] = i;

        // If the group is full, add it to the result
        if (groups[size].count == size) {
            result[returnCount] = (int*)malloc(sizeof(int) * size);
            memcpy(result[returnCount], groups[size].members, sizeof(int) * size);
            (*returnColumnSizes)[returnCount] = size;
            returnCount++;

            // Reset the group
            free(groups[size].members);
            groups[size].members = NULL;
            groups[size].count = 0;
        }
    }

    free(groups);
    *returnSize = returnCount;
    return result;      
}
