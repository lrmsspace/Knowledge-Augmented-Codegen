// Source: https://leetcode.com/problems/maximum-building-height/   |   Difficulty: Hard
//
// Problem Description:
// You want to build n new buildings in a city. The new buildings will be built in a line and are labeled from 1 to n.
//
// However, there are city restrictions on the heights of the new buildings:
//
//
// 	The height of each building must be a non-negative integer.
// 	The height of the first building must be 0.
// 	The height difference between any two adjacent buildings cannot exceed 1.
//
//
// Additionally, there are city restrictions on the maximum height of specific buildings. These restrictions are given as a 2D integer array restrictions where restrictions[i] = [idi, maxHeighti] indicates that building idi must have a height less than or equal to maxHeighti.
//
// It is guaranteed that each building will appear at most once in restrictions, and building 1 will not be in restrictions.
//
// Return the maximum possible height of the tallest building.
//
// Example:
// Input: n = 5, restrictions = [[2,1],[4,1]]
// Output: 2
// Explanation: The green area in the image indicates the maximum allowed height for each building.
// We can build the buildings with heights [0,1,2,1,2], and the tallest building has a height of 2.
//
// Constraints:
// 2 <= n <= 109
// 	0 <= restrictions.length <= min(n - 1, 105)
// 	2 <= idi <= n
// 	idi is unique.
// 	0 <= maxHeighti <= 109
//

int maxBuilding(int n, int** restrictions, int restrictionsSize, int* restrictionsColSize) {
    /* add default restriction for building 1 */
    int totalRestrictions = restrictionsSize + 1;
    int (*allRestrictions)[2] = malloc(totalRestrictions * sizeof(*allRestrictions));
    if (!allRestrictions) return -1; /* allocation failure */
    allRestrictions[0][0] = 1; allRestrictions[0][1] = 0;
    for (int i = 0; i < restrictionsSize; ++i) {
        allRestrictions[i + 1][0] = restrictions[i][0];
        allRestrictions[i + 1][1] = restrictions[i][1];
    }

    /* sort restrictions by building id */
    qsort(allRestrictions, totalRestrictions, sizeof(*allRestrictions),
          (int (*)(const void*, const void*))[](const int a[2], const int b[2]) {
              return a[0] - b[0];
          });

    /* propagate max heights left to right */
    for (int i = 1; i < totalRestrictions; ++i) {
        int dist = allRestrictions[i][0] - allRestrictions[i - 1][0];
        int allowedHeight = allRestrictions[i - 1][1] + dist;
        if (allRestrictions[i][1] > allowedHeight) {
            allRestrictions[i][1] = allowedHeight;
        }
    }

    /* propagate max heights right to left */
    for (int i = totalRestrictions - 2; i >= 0; --i) {
        int dist = allRestrictions[i + 1][0] - allRestrictions[i][0];
        int allowedHeight = allRestrictions[i + 1][1] + dist;
        if (allRestrictions[i][1] > allowedHeight) {
            allRestrictions[i][1] = allowedHeight;
        }
    }

    /* find maximum possible height between each pair of restrictions */
    int maxHeight = 0;
    for (int i = 0; i < totalRestrictions - 1; ++i) {
        int id1 = allRestrictions[i][0], h1 = allRestrictions[i][1];
        int id2 = allRestrictions[i + 1][0], h2 = allRestrictions[i + 1][1];
        int dist = id2 - id1;
        if (h1 > h2) {
            int temp = h1; h1 = h2; h2 = temp;
        }  
        int localMax = (h1 + h2 + dist) / 2;
        if (localMax > maxHeight) {
            maxHeight = localMax;
        }
    }

    free(allRestrictions);
    return maxHeight;
}