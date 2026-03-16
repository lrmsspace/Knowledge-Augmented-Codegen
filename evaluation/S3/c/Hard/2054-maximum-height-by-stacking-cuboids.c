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
// - Burnside's lemma / Pólya enumeration theorem (array, number, enumeration, simulation)
//   • When to use: Use when counting the number of distinct configurations or arrangements of objects under a set of symmetry operations, where configurations are considered identical if one can be transformed into another by a group action.
//   • Idea: Burnside's Lemma and Pólya Enumeration Theorem are combinatorial tools used to count the number of distinct objects under a group of symmetries. Both typically involve iterating through group elements and analyzing permutation cycle structures, often resulting in polynomial time complexity depending on group size and element analysis.
//   • Invariants: The set of group elements considered remains consistent throughout the summation.; Each group element's cycle decomposition is correctly identified.
//   • Tips: Identify the group of symmetry operations acting on the objects.; For each group element, determine its permutation cycle structure.
//   • Pitfalls: Incorrectly identifying the full set of distinct group operations.; Errors in determining the cycle structure of permutations.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Finding the equation of a line for a segment (geometry, number, enumeration)
//   • When to use: Use when the problem asks to count or list all possible combinations, permutations, or arrangements of elements. It's suitable when a brute-force check of all possibilities is feasible.
//   • Idea: Enumeration systematically generates and examines all possible solutions to a problem. This approach guarantees finding the correct answer if one exists, typically with exponential time complexity O(k^N) or O(N!).
//   • Invariants: At each step, the current partial solution is valid according to problem constraints.; All previously explored partial solutions have been processed or discarded.
//   • Tips: Clearly define the search space and the properties of valid solutions.; Use recursion or iterative loops to explore all branches of the solution space.
//   • Pitfalls: Overlooking edge cases or constraints that limit the search space.; Generating duplicate solutions if not handled carefully.
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
        int* c = cuboids[i];
        // Simple bubble sort for three dimensions
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2 - j; k++) {
                if (c[k] > c[k + 1]) {
                    int temp = c[k];
                    c[k] = c[k + 1];
                    c[k + 1] = temp;
                }
            }
        }
    }

    // Step 2: Sort cuboids based on their dimensions
    qsort(cuboids, cuboidsSize, sizeof(int*), [](const void* a, const void* b) {
        int* c1 = *(int**)a;
        int* c2 = *(int**)b;
        for (int i = 0; i < 3; i++) {
            if (c1[i] != c2[i]) {
                return c1[i] - c2[i];
            }
        }
        return 0;
    });

    // Step 3: Dynamic Programming to find the maximum height
    int dp[cuboidsSize];
    for (int i = 0; i < cuboidsSize; i++) {
        dp[i] = cuboids[i][2]; // Start with the height of the current cuboid
    }

    for (int i = 1; i < cuboidsSize; i++) {
        for (int j = 0; j < i; j++) {
            if (cuboids[j][0] <= cuboids[i][0] && 
                cuboids[j][1] <= cuboids[i][1] && 
                cuboids[j][2] <= cuboids[i][2]) {
                dp[i] = dp[i] > dp[j] + cuboids[i][2] ? dp[i] : dp[j] + cuboids[i][2];
            }
        }
    }

    // Step 4: Find the maximum height from dp array
    int maxHeight = 0;
    for (int i = 0; i < cuboidsSize; i++) {
        if (dp[i] > maxHeight) {
            maxHeight = dp[i];
        }
    }
    return maxHeight;
}
