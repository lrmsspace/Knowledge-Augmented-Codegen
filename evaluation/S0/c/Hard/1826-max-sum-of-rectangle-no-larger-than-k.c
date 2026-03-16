// Source: https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/   |   Difficulty: Hard
//
// Problem Description:
// Given an m x n matrix matrix and an integer k, return the max sum of a rectangle in the matrix such that its sum is no larger than k.
//
// It is guaranteed that there will be a rectangle with a sum no larger than k.
//
// Example:
// Input: matrix = [[1,0,1],[0,-2,3]], k = 2
// Output: 2
// Explanation: Because the sum of the blue rectangle [[0, 1], [-2, 3]] is 2, and 2 is the max number no larger than k (k = 2).
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 100
// 	-100 <= matrix[i][j] <= 100
// 	-105 <= k <= 105
//
//
//  
// Follow up: What if the number of rows is much larger than the number of columns?
//

int maxSumSubmatrix(int** matrix, int matrixSize, int* matrixColSize, int k) {
    int rows = matrixSize;
    int cols = matrixColSize[0];
    int maxSum = -2147483648; /* INT_MIN */

    for (int left = 0; left < cols; ++left) {
        int *rowSums = (int*)calloc(rows, sizeof(int));
        if (!rowSums) return maxSum; /* allocation failure, return current maxSum */

        for (int right = left; right < cols; ++right) {
            for (int r = 0; r < rows; ++r) {
                rowSums[r] += matrix[r][right];
            }

            /* Find the max subarray no larger than k using prefix sums and a sorted array */
            int currSum = 0;
            int *prefixSums = (int*)malloc((rows + 1) * sizeof(int));
            if (!prefixSums) {
                free(rowSums);
                return maxSum; /* allocation failure, return current maxSum */
            }
            prefixSums[0] = 0;
            int prefixCount = 1;

            for (int r = 0; r < rows; ++r) {
                currSum += rowSums[r];

                /* We want to find the smallest prefix sum >= currSum - k */
                int target = currSum - k;
                int lo = 0, hi = prefixCount - 1;
                while (lo <= hi) {
                    int mid = lo + (hi - lo) / 2;
                    if (prefixSums[mid] >= target) {
                        hi = mid - 1;
                    } else {
                        lo = mid + 1;
                    }
                }

                if (lo < prefixCount) {
                    int candidate = currSum - prefixSums[lo];
                    if (candidate <= k && candidate > maxSum) {
                        maxSum = candidate;
                    }
                }

                /* Insert currSum into prefixSums in sorted order */
                int insertPos = prefixCount;
                for (int i = 0; i < prefixCount; ++i) {
                    if (prefixSums[i] > currSum) {
                        insertPos = i;
                        break;
                    }
                }
                for (int i = prefixCount; i > insertPos; --i) {
                    prefixSums[i] = prefixSums[i - 1];
                }       
                prefixSums[insertPos] = currSum;
                prefixCount++;
            }
            free(prefixSums);
        }
        free(rowSums);
        
    }
    return maxSum;
}
