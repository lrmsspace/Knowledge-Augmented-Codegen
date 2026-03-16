// Source: https://leetcode.com/problems/number-of-black-blocks/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers m and n representing the dimensions of a 0-indexed m x n grid.
//
// You are also given a 0-indexed 2D integer matrix coordinates, where coordinates[i] = [x, y] indicates that the cell with coordinates [x, y] is colored black. All cells in the grid that do not appear in coordinates are white.
//
// A block is defined as a 2 x 2 submatrix of the grid. More formally, a block with cell [x, y] as its top-left corner where 0 <= x < m - 1 and 0 <= y < n - 1 contains the coordinates [x, y], [x + 1, y], [x, y + 1], and [x + 1, y + 1].
//
// Return a 0-indexed integer array arr of size 5 such that arr[i] is the number of blocks that contains exactly i black cells.
//
// Example:
// Input: m = 3, n = 3, coordinates = [[0,0]]
// Output: [3,1,0,0,0]
// Explanation: The grid looks like this:
//
// There is only 1 block with one black cell, and it is the block starting with cell [0,0].
// The other 3 blocks start with cells [0,1], [1,0] and [1,1]. They all have zero black cells. 
// Thus, we return [3,1,0,0,0].
//
// Constraints:
// 2 <= m <= 105
// 	2 <= n <= 105
// 	0 <= coordinates.length <= 104
// 	coordinates[i].length == 2
// 	0 <= coordinates[i][0] < m
// 	0 <= coordinates[i][1] < n
// 	It is guaranteed that coordinates contains pairwise distinct coordinates.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
long long* countBlackBlocks(int m, int n, int** coordinates, int coordinatesSize, int* coordinatesColSize, int* returnSize) {
    // Initialize the return size and the result array
    *returnSize = 5;
    long long* result = (long long*)calloc(5, sizeof(long long));
    
    // Hash map to count black cells in each 2x2 block
    typedef struct {
        long long key;
        int count;
    } HashEntry;
    
    #define HASH_SIZE 20011
    HashEntry* hashMap[HASH_SIZE];
    for (int i = 0; i < HASH_SIZE; i++) {
        hashMap[i] = NULL;
    }
    
    // Function to compute hash key
    long long computeKey(int x, int y) {
        return ((long long)x << 32) | (long long)y;
    }
    
    // Function to get hash index
    int getHashIndex(long long key) {
        return (int)(key % HASH_SIZE);
    }
    
    // Process each black cell
    for (int i = 0; i < coordinatesSize; i++) {
        int x = coordinates[i][0];
        int y = coordinates[i][1];
        
        // Check the four possible 2x2 blocks that can include this black cell
        for (int dx = -1; dx <= 0; dx++) {
            for (int dy = -1; dy <= 0; dy++) {
                int bx = x + dx;
                int by = y + dy;
                
                if (bx >= 0 && by >= 0 && bx < m - 1 && by < n - 1) {
                    long long key = computeKey(bx, by);
                    int index = getHashIndex(key);
                    
                    // Insert or update the hash map
                    HashEntry* entry = hashMap[index];
                    while (entry != NULL && entry->key != key) {
                        entry = entry->next;
                    }
                    
                    if (entry == NULL) {
                        entry = (HashEntry*)malloc(sizeof(HashEntry));
                        entry->key = key;
                        entry->count = 1;
                        entry->next = hashMap[index];
                        hashMap[index] = entry;
                    } else {
                        entry->count++;
                    }
                }
            }
        }
    }
    
    // Count the number of blocks with different counts of black cells
    for (int i = 0; i < HASH_SIZE; i++) {
        HashEntry* entry = hashMap[i];
        while (entry != NULL) {
            result[entry->count]++;
            entry = entry->next;
        }
    }
    
    // Calculate the number of blocks with zero black cells
    long long totalBlocks = (long long)(m - 1) * (n - 1);
    long long countedBlocks = 0;
    for (int i = 1; i <= 4; i++) {
        countedBlocks += result[i];
    }
    result[0] = totalBlocks - countedBlocks;

    return result;
}