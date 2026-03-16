// Source: https://leetcode.com/problems/maximum-height-by-stacking-cuboids/   |   Difficulty: Hard
//
// Problem Description:
// Given n cuboids where the dimensions of the ith cuboid is cuboids[i] = [widthi, lengthi, heighti] (0-indexed). Choose a subset of cuboids and place them on each other.
//
// You can place cuboid i on cuboid j if widthi <= widthj and lengthi <= lengthj and heighti <= heightj. You can rearrange any cuboid's dimensions by rotating it to put it on another cuboid.
//
// Return the maximum height of the stacked cuboids.
//
// Example:
// Input: cuboids = [[50,45,20],[95,37,53],[45,23,12]]
// Output: 190
// Explanation:
// Cuboid 1 is placed on the bottom with the 53x37 side facing down with height 95.
// Cuboid 0 is placed next with the 45x20 side facing down with height 50.
// Cuboid 2 is placed next with the 23x12 side facing down with height 45.
// The total height is 95 + 50 + 45 = 190.
//
// Constraints:
// n == cuboids.length
// 	1 <= n <= 100
// 	1 <= widthi, lengthi, heighti <= 100
//



int maxHeight(int** cuboids, int cuboidsSize, int* cuboidsColSize){
    for (int i = 0; i < cuboidsSize; ++i) {
        qsort(cuboids[i], 3, sizeof(int), cmpInt);
    }
    qsort(cuboids, cuboidsSize, sizeof(int*), cmpInt);

    int *dp = (int*)calloc(cuboidsSize, sizeof(int));
    int maxH = 0;
    for (int i = 0; i < cuboidsSize; ++i) {
        dp[i] = cuboids[i][2];
        for (int j = 0; j < i; ++j) {
            if (cuboids[j][0] <= cuboids[i][0] &&
                cuboids[j][1] <= cuboids[i][1] &&
                cuboids[j][2] <= cuboids[i][2]) {
                if (dp[j] + cuboids[i][2] > dp[i]) {
                    dp[i] = dp[j] + cuboids[i][2];
                }
            }
        }
        if (dp[i] > maxH) maxH = dp[i];
    }
    free(dp);
    return maxH;
}
