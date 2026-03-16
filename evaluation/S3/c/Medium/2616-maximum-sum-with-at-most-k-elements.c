// Source: https://leetcode.com/problems/maximum-sum-with-at-most-k-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer matrix grid of size n x m, an integer array limits of length n, and an integer k. The task is to find the maximum sum of at most k elements from the matrix grid such that:
//
//
// 	
// 	The number of elements taken from the ith row of grid does not exceed limits[i].
// 	
//
//
// Return the maximum sum.
//
// Example:
// Input: grid = [[1,2],[3,4]], limits = [1,2], k = 2
//
// Output: 7
//
// Explanation:
//
//
// 	From the second row, we can take at most 2 elements. The elements taken are 4 and 3.
// 	The maximum possible sum of at most 2 selected elements is 4 + 3 = 7.
//
// Constraints:
// n == grid.length == limits.length
// 	m == grid[i].length
// 	1 <= n, m <= 500
// 	0 <= grid[i][j] <= 105
// 	0 <= limits[i] <= m
// 	0 <= k <= min(n * m, sum(limits))
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Finding the rank of a matrix (matrix, simulation, enumeration)
//   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
//   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
//   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
//   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
//   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long maxSum(int** grid, int gridSize, int* gridColSize, int* limits, int limitsSize, int k) {
    // Step 1: Create an array to hold the maximum sums for each row based on the limits
    long long maxRowSums[gridSize];
    
    for (int i = 0; i < gridSize; i++) {
        // Sort the current row in descending order to get the largest elements first
        qsort(grid[i], gridColSize[i], sizeof(int), (int(*)(const void*, const void*))compare);
        
        // Calculate the sum of the top 'limits[i]' elements for the current row
        long long sum = 0;
        for (int j = 0; j < limits[i] && j < gridColSize[i]; j++) {
            sum += grid[i][j];
        }
        maxRowSums[i] = sum;
    }
    
    // Step 2: Sort the maxRowSums in descending order to get the largest sums first
    qsort(maxRowSums, gridSize, sizeof(long long), (int(*)(const void*, const void*))compare);
    
    // Step 3: Calculate the maximum sum by taking the top 'k' elements from maxRowSums
    long long totalSum = 0;
    for (int i = 0; i < k && i < gridSize; i++) {
        totalSum += maxRowSums[i];
    }
    
    return totalSum;        
}
