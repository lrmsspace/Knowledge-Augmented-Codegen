// Source: https://leetcode.com/problems/find-kth-largest-xor-coordinate-value/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D matrix of size m x n, consisting of non-negative integers. You are also given an integer k.
//
// The value of coordinate (a, b) of the matrix is the XOR of all matrix[i][j] where 0 <= i <= a < m and 0 <= j <= b < n (0-indexed).
//
// Find the kth largest value (1-indexed) of all the coordinates of matrix.
//
// Example:
// Input: matrix = [[5,2],[1,6]], k = 1
// Output: 7
// Explanation: The value of coordinate (0,1) is 5 XOR 2 = 7, which is the largest value.
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 1000
// 	0 <= matrix[i][j] <= 106
// 	1 <= k <= m * n
//

int kthLargestValue(int** matrix, int matrixSize, int* matrixColSize, int k) {
    int m = matrixSize;
    int n = matrixColSize[0];
    int* xorValues = (int*)malloc(sizeof(int) * m * n);
    int index = 0;

    // Create a 2D array to store the prefix XOR values
    int** prefixXOR = (int**)malloc(sizeof(int*) * (m + 1));
    for (int i = 0; i <= m; i++) {
        prefixXOR[i] = (int*)calloc(n + 1, sizeof(int));
    }

    // Calculate the prefix XOR values
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            prefixXOR[i][j] = prefixXOR[i - 1][j] ^ prefixXOR[i][j - 1] ^ prefixXOR[i - 1][j - 1] ^ matrix[i - 1][j - 1];
            xorValues[index++] = prefixXOR[i][j];
        }
    }

    // Free the prefixXOR array
    for (int i = 0; i <= m; i++) {
        free(prefixXOR[i]);
    }
    free(prefixXOR);

    // Sort the xorValues array in descending order
    qsort(xorValues, m * n, sizeof(int), [](const void* a, const void* b) {
        return (*(int*)b - *(int*)a);
    });

    int result = xorValues[k - 1];
    free(xorValues);
    return result;      
}
