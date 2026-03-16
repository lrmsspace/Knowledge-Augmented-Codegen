// Source: https://leetcode.com/problems/flip-columns-for-maximum-number-of-equal-rows/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n binary matrix matrix.
//
// You can choose any number of columns in the matrix and flip every cell in that column (i.e., Change the value of the cell from 0 to 1 or vice versa).
//
// Return the maximum number of rows that have all values equal after some number of flips.
//
// Example:
// Input: matrix = [[0,1],[1,1]]
// Output: 1
// Explanation: After flipping no values, 1 row has all values equal.
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 300
// 	matrix[i][j] is either 0 or 1.
//

int maxEqualRowsAfterFlips(int** matrix, int matrixSize, int* matrixColSize) {
    int maxCount = 0;
    int n = *matrixColSize;
    // Use a hash map to count the frequency of each row pattern
    typedef struct {
        int* key;
        int count;
    } HashEntry;

    HashEntry* hashMap = (HashEntry*)calloc(matrixSize, sizeof(HashEntry));
    int hashSize = 0;

    for (int i = 0; i < matrixSize; i++) {
        // Create a normalized key for the current row
        int* key = (int*)malloc(n * sizeof(int));
        int flip = matrix[i][0];
        for (int j = 0; j < n; j++) {
            key[j] = matrix[i][j] ^ flip;
        }

        // Check if this key already exists in the hash map
        int found = 0;
        for (int k = 0; k < hashSize; k++) {
            int match = 1;
            for (int j = 0; j < n; j++) {
                if (hashMap[k].key[j] != key[j]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                hashMap[k].count++;
                if (hashMap[k].count > maxCount) {
                    maxCount = hashMap[k].count;
                }
                found = 1;
                break;
            }
        }

        // If not found, add a new entry to the hash map
        if (!found) {
            hashMap[hashSize].key = key;
            hashMap[hashSize].count = 1;
            if (maxCount < 1) {
                maxCount = 1;
            }
            hashSize++;
        } else {
            free(key);
        }
    }

    // Free allocated memory
    for (int i = 0; i < hashSize; i++) {
        free(hashMap[i].key);
    }
    free(hashMap);

    return maxCount;        
}
