// Source: https://leetcode.com/problems/alternating-groups-iii/   |   Difficulty: Hard
//
// Problem Description:
// There are some red and blue tiles arranged circularly. You are given an array of integers colors and a 2D integers array queries.
//
// The color of tile i is represented by colors[i]:
//
//
//  colors[i] == 0 means that tile i is red.
//  colors[i] == 1 means that tile i is blue.
//
//
// An alternating group is a contiguous subset of tiles in the circle with alternating colors (each tile in the group except the first and last one has a different color from its adjacent tiles in the group).
//
// You have to process queries of two types:
//
//
//  queries[i] = [1, sizei], determine the count of alternating groups with size sizei.
//  queries[i] = [2, indexi, colori], change colors[indexi] to colori.
//
//
// Return an array answer containing the results of the queries of the first type in order.
//
// Note that since colors represents a circle, the first and the last tiles are considered to be next to each other.
//
// Example:
// Input: colors = [0,1,1,0,1], queries = [[2,1,0],[1,4]]
//
// Output: [2]
//
// Explanation:
//
//
//
// First query:
//
// Change colors[1] to 0.
//
//
//
// Second query:
//
// Count of the alternating groups with size 4:
//
// Constraints:
// 4 <= colors.length <= 5 * 104
//  0 <= colors[i] <= 1
//  1 <= queries.length <= 5 * 104
//  queries[i][0] == 1 or queries[i][0] == 2
//  For all i that:
//  
//   queries[i][0] == 1: queries[i].length == 2, 3 <= queries[i][1] <= colors.length - 1
//   queries[i][0] == 2: queries[i].length == 3, 0 <= queries[i][1] <= colors.length - 1, 0 <= queries[i][2] <= 1
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* numberOfAlternatingGroups(int* colors, int colorsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    if (!returnSize) return NULL;
    int *results = (int*)malloc(queriesSize * sizeof(int));
    if (!results) return NULL;
    int resIndex = 0;

    // Helper function to count alternating groups of a given size
    int countAlternatingGroups(int size) {
        int count = 0;
        int n = colorsSize;
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && colors[j] == colors[i]) j++;
            int groupSize = j - i;
            if (groupSize >= size) {
                count += groupSize - size + 1;
            }
            i = j;
        }
        // Check circular case
        if (colors[0] != colors[n - 1]) {
            int left = 0, right = n - 1;
            while (left < n && colors[left] == colors[0]) left++;
            while (right >= 0 && colors[right] == colors[n - 1]) right--;
            int circularGroupSize = left + (n - 1 - right);
            if (circularGroupSize >= size) {
                count += circularGroupSize - size + 1;
            }
        }
        return count;
    }

    for (int i = 0; i < queriesSize; ++i) {
        if (queries[i][0] == 1) {
            int size = queries[i][1];
            results[resIndex++] = countAlternatingGroups(size);
        } else if (queries[i][0] == 2) {
            int index = queries[i][1];
            int color = queries[i][2];
            colors[index] = color;
        }
    }

    *returnSize = resIndex;
    return results;     
}
