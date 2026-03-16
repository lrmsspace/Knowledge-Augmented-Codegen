// Source: https://leetcode.com/problems/merge-two-2d-arrays-by-summing-values/   |   Difficulty: Easy
//
// Problem Description:
// You are given two 2D integer arrays nums1 and nums2.
//
//
// 	nums1[i] = [idi, vali] indicate that the number with the id idi has a value equal to vali.
// 	nums2[i] = [idi, vali] indicate that the number with the id idi has a value equal to vali.
//
//
// Each array contains unique ids and is sorted in ascending order by id.
//
// Merge the two arrays into one array that is sorted in ascending order by id, respecting the following conditions:
//
//
// 	Only ids that appear in at least one of the two arrays should be included in the resulting array.
// 	Each id should be included only once and its value should be the sum of the values of this id in the two arrays. If the id does not exist in one of the two arrays, then assume its value in that array to be 0.
//
//
// Return the resulting array. The returned array must be sorted in ascending order by id.
//
// Example:
// Input: nums1 = [[1,2],[2,3],[4,5]], nums2 = [[1,4],[3,2],[4,1]]
// Output: [[1,6],[2,3],[3,2],[4,6]]
// Explanation: The resulting array contains the following:
// - id = 1, the value of this id is 2 + 4 = 6.
// - id = 2, the value of this id is 3.
// - id = 3, the value of this id is 2.
// - id = 4, the value of this id is 5 + 1 = 6.
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 200
// 	nums1[i].length == nums2[j].length == 2
// 	1 <= idi, vali <= 1000
// 	Both arrays contain unique ids.
// 	Both arrays are in strictly ascending order by id.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** mergeArrays(int** nums1, int nums1Size, int* nums1ColSize, int** nums2, int nums2Size, int* nums2ColSize, int* returnSize, int** returnColumnSizes) {
    int maxId = 1000;
    int* values = (int*)calloc((maxId + 1), sizeof(int));
    for (int i = 0; i < nums1Size; i++) {
        int id = nums1[i][0];
        int val = nums1[i][1];
        values[id] += val;
    }
    for (int i = 0; i < nums2Size; i++) {
        int id = nums2[i][0];
        int val = nums2[i][1];
        values[id] += val;
    }

    int count = 0;
    for (int id = 1; id <= maxId; id++) {
        if (values[id] > 0) {
            count++;
        }
    }

    int** result = (int**)malloc(count * sizeof(int*));
    *returnColumnSizes = (int*)malloc(count * sizeof(int));
    *returnSize = count;

    int index = 0;
    for (int id = 1; id <= maxId; id++) {
        if (values[id] > 0) {
            result[index] = (int*)malloc(2 * sizeof(int));
            result[index][0] = id;
            result[index][1] = values[id];
            (*returnColumnSizes)[index] = 2;
            index++;
        }
    }

    free(values);
    return result;      
}
