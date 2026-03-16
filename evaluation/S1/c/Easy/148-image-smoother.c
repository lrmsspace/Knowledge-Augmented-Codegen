// Source: https://leetcode.com/problems/image-smoother/   |   Difficulty: Easy
//
// Problem Description:
// An image smoother is a filter of the size 3 x 3 that can be applied to each cell of an image by rounding down the average of the cell and the eight surrounding cells (i.e., the average of the nine cells in the blue smoother). If one or more of the surrounding cells of a cell is not present, we do not consider it in the average (i.e., the average of the four cells in the red smoother).
//
// Given an m x n integer matrix img representing the grayscale of an image, return the image after applying the smoother on each cell of it.
//
// Example:
// Input: img = [[1,1,1],[1,0,1],[1,1,1]]
// Output: [[0,0,0],[0,0,0],[0,0,0]]
// Explanation:
// For the points (0,0), (0,2), (2,0), (2,2): floor(3/4) = floor(0.75) = 0
// For the points (0,1), (1,0), (1,2), (2,1): floor(5/6) = floor(0.83333333) = 0
// For the point (1,1): floor(8/9) = floor(0.88888889) = 0
//
// Constraints:
// m == img.length
// 	n == img[i].length
// 	1 <= m, n <= 200
// 	0 <= img[i][j] <= 255
//
// Helpful references (internal KB):
// - Simulated Annealing (array, number, randomized, simulation)
//   • When to use: Use when seeking a near-optimal solution for complex optimization problems with many local optima, especially when exact solutions are computationally infeasible or too slow.
//   • Idea: Simulated Annealing is a probabilistic metaheuristic for global optimization, inspired by the annealing process in metallurgy. It explores the search space by accepting worse solutions with a probability that decreases over time, aiming to escape local optima.
//   • Invariants: The `s_best` state always represents the lowest energy found across all iterations so far.; The temperature `T` is always non-negative and decreases monotonically with each iteration.
//   • Tips: Start with a sufficiently high initial temperature to allow broad exploration.; Choose a slow cooling schedule (decay rate) for better solution quality, at the cost of longer runtime.
//   • Pitfalls: Getting stuck in local minima if the cooling schedule is too fast.; Excessive runtime if the cooling schedule is too slow or initial temperature is too high.
// - Finding the rank of a matrix (matrix, simulation, enumeration)
//   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
//   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
//   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
//   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
//   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
// - Lattice points inside non-lattice polygon (geometry, number, counting, recursion)
//   • When to use: Use this when you need to count integer coordinate points strictly inside a polygon whose vertices are not restricted to integer coordinates. It's suitable for problems requiring precise geometric counting with non-lattice boundaries.
//   • Idea: This algorithm counts lattice points within a polygon with arbitrary vertices by summing signed contributions from each edge. It reduces the problem to evaluating sums of floor functions, sum(floor(kx+b)), which is solved recursively, typically achieving logarithmic complexity per edge.
//   • Invariants: The sum sum(floor(kx+b)) correctly accumulates points below the current edge segment.; After coordinate transformations, the problem reduces to a sum over a non-negative range with non-negative k and b.
//   • Tips: Decompose the polygon into signed areas under each edge, similar to the shoelace formula.; Handle edge cases where k or b are negative by appropriate transformations.
//   • Pitfalls: Floating point precision issues when calculating k and b or during transformations.; Incorrectly handling boundary points (points on edges or vertices).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** imageSmoother(int** img, int imgSize, int* imgColSize, int* returnSize, int** returnColumnSizes) {
    int directions[9][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},  {0, 0},  {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };
    
    int** result = (int**)malloc(imgSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(imgSize * sizeof(int));
    *returnSize = imgSize;
    
    for (int i = 0; i < imgSize; i++) {
        result[i] = (int*)malloc(imgColSize[i] * sizeof(int));
        (*returnColumnSizes)[i] = imgColSize[i];
        
        for (int j = 0; j < imgColSize[i]; j++) {
            int sum = 0;
            int count = 0;
            
            for (int d = 0; d < 9; d++) {
                int ni = i + directions[d][0];
                int nj = j + directions[d][1];
                
                if (ni >= 0 && ni < imgSize && nj >= 0 && nj < imgColSize[i]) {
                    sum += img[ni][nj];
                    count++;
                }
            }
            
            result[i][j] = sum / count;
        }
    }
    
    return result;      
}
