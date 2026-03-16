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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.



int maxHeight(int** cuboids, int cuboidsSize, int* cuboidsColSize){
    // Step 1: Sort dimensions of each cuboid
    for (int i = 0; i < cuboidsSize; i++) {
        int* dims = cuboids[i];
        // Simple bubble sort for 3 dimensions
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2 - j; k++) {
                if (dims[k] > dims[k + 1]) {
                    int temp = dims[k];
                    dims[k] = dims[k + 1];
                    dims[k + 1] = temp;
                }
            }
        }
    }

    // Step 2: Sort cuboids based on their dimensions
    qsort(cuboids, cuboidsSize, sizeof(int*), [](const void* a, const void* b) {
        int* cuboidA = *(int**)a;
        int* cuboidB = *(int**)b;
        for (int i = 0; i < 3; i++) {
            if (cuboidA[i] != cuboidB[i]) {
                return cuboidA[i] - cuboidB[i];
            }
        }
        return 0;
    });

    // Step 3: Dynamic programming to find the maximum stack height
    int dp[cuboidsSize];
    for (int i = 0; i < cuboidsSize; i++) {
        dp[i] = cuboids[i][2]; // Start with the height of the current cuboid
        for (int j = 0; j < i; j++) {
            if (cuboids[j][0] <= cuboids[i][0] && 
                cuboids[j][1] <= cuboids[i][1] && 
                cuboids[j][2] <= cuboids[i][2]) {
                dp[i] = dp[i] > dp[j] + cuboids[i][2] ? dp[i] : dp[j] + cuboids[i][2];
            }
        }
    }

    // Step 4: Find the maximum height from the dp array
    int maxHeight = 0;
    for (int i = 0; i < cuboidsSize; i++) {
        if (dp[i] > maxHeight) {
            maxHeight = dp[i];
        }
    }

    return maxHeight;
}
