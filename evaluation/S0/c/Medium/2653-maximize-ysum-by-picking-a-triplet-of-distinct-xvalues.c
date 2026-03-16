// Source: https://leetcode.com/problems/maximize-ysum-by-picking-a-triplet-of-distinct-xvalues/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays x and y, each of length n. You must choose three distinct indices i, j, and k such that:
//
//
// 	x[i] != x[j]
// 	x[j] != x[k]
// 	x[k] != x[i]
//
//
// Your goal is to maximize the value of y[i] + y[j] + y[k] under these conditions. Return the maximum possible sum that can be obtained by choosing such a triplet of indices.
//
// If no such triplet exists, return -1.
//
// Example:
// Input: x = [1,2,1,3,2], y = [5,3,4,6,2]
//
// Output: 14
//
// Explanation:
//
//
// 	Choose i = 0 (x[i] = 1, y[i] = 5), j = 1 (x[j] = 2, y[j] = 3), k = 3 (x[k] = 3, y[k] = 6).
// 	All three values chosen from x are distinct. 5 + 3 + 6 = 14 is the maximum we can obtain. Hence, the output is 14.
//
// Constraints:
// n == x.length == y.length
// 	3 <= n <= 105
// 	1 <= x[i], y[i] <= 106
//

int maxSumDistinctTriplet(int* x, int xSize, int* y, int ySize) {
    // Create an array of pairs (x[i], y[i])
    typedef struct {
        int x;
        int y;
    } Pair;

    Pair* pairs = (Pair*)malloc(xSize * sizeof(Pair));
    for (int i = 0; i < xSize; i++) {
        pairs[i].x = x[i];
        pairs[i].y = y[i];
    }

    // Sort pairs by y in descending order
    int compare(const void* a, const void* b) {
        return ((Pair*)b)->y - ((Pair*)a)->y;
    }
    qsort(pairs, xSize, sizeof(Pair), compare);

    int distinctCount = 0;
    int sum = 0;
    int lastX = -1;

    // Iterate through sorted pairs and pick distinct x values
    for (int i = 0; i < xSize && distinctCount < 3; i++) {
        if (pairs[i].x != lastX) {
            sum += pairs[i].y;
            lastX = pairs[i].x;
            distinctCount++;
        }
    }

    free(pairs);

    // If we found less than 3 distinct x values, return -1
    return (distinctCount < 3) ? -1 : sum;      
}
