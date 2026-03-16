// Source: https://leetcode.com/problems/matrix-similarity-after-cyclic-shifts/   |   Difficulty: Easy
//
// Problem Description:
// You are given an m x n integer matrix mat and an integer k. The matrix rows are 0-indexed.
//
// The following proccess happens k times:
//
//
// 	Even-indexed rows (0, 2, 4, ...) are cyclically shifted to the left.
//
//
//
//
//
// 	Odd-indexed rows (1, 3, 5, ...) are cyclically shifted to the right.
//
//
//
//
// Return true if the final modified matrix after k steps is identical to the original matrix, and false otherwise.
//
// Example:
// Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 4
//
// Output: false
//
// Explanation:
//
// In each step left shift is applied to rows 0 and 2 (even indices), and right shift to row 1 (odd index).
//
// Constraints:
// 1 <= mat.length <= 25
// 	1 <= mat[i].length <= 25
// 	1 <= mat[i][j] <= 25
// 	1 <= k <= 50
//
// Helpful references (internal KB):
// - Finding the rank of a matrix (matrix, simulation, enumeration)
//   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
//   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
//   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
//   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
//   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
// - Burnside's lemma / Pólya enumeration theorem (array, number, enumeration, simulation)
//   • When to use: Use when counting the number of distinct configurations or arrangements of objects under a set of symmetry operations, where configurations are considered identical if one can be transformed into another by a group action.
//   • Idea: Burnside's Lemma and Pólya Enumeration Theorem are combinatorial tools used to count the number of distinct objects under a group of symmetries. Both typically involve iterating through group elements and analyzing permutation cycle structures, often resulting in polynomial time complexity depending on group size and element analysis.
//   • Invariants: The set of group elements considered remains consistent throughout the summation.; Each group element's cycle decomposition is correctly identified.
//   • Tips: Identify the group of symmetry operations acting on the objects.; For each group element, determine its permutation cycle structure.
//   • Pitfalls: Incorrectly identifying the full set of distinct group operations.; Errors in determining the cycle structure of permutations.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool areSimilar(int** mat, int matSize, int* matColSize, int k) {
    int m = matSize, n = matColSize[0];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (mat[i][j] != mat[i][(j + (i % 2 == 0 ? k : n - k)) % n]) {
                return false;
            }
        }
    }
    return true;        
}
