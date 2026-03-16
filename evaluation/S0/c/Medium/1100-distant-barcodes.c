// Source: https://leetcode.com/problems/distant-barcodes/   |   Difficulty: Medium
//
// Problem Description:
// In a warehouse, there is a row of barcodes, where the ith barcode is barcodes[i].
//
// Rearrange the barcodes so that no two adjacent barcodes are equal. You may return any answer, and it is guaranteed an answer exists.
//
// Example:
// Input: barcodes = [1,1,1,2,2,2]
// Output: [2,1,2,1,2,1]
//
// Constraints:
// 1 <= barcodes.length <= 10000
// 	1 <= barcodes[i] <= 10000
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* rearrangeBarcodes(int* barcodes, int barcodesSize, int* returnSize) {
    int count[10001] = {0};
    for (int i = 0; i < barcodesSize; i++) {
        count[barcodes[i]]++;
    }

    int maxCount = 0;
    int maxNum = 0;
    for (int i = 0; i <= 10000; i++) {
        if (count[i] > maxCount) {
            maxCount = count[i];
            maxNum = i;
        }
    }

    int* result = (int*)malloc(barcodesSize * sizeof(int));
    int index = 0;

    // Place the most frequent barcode at even indices
    while (count[maxNum] > 0) {
        result[index] = maxNum;
        index += 2;
        count[maxNum]--;
    }

    // Place the remaining barcodes
    for (int i = 0; i <= 10000; i++) {
        while (count[i] > 0) {
            if (index >= barcodesSize) {
                index = 1; // Switch to odd indices
            }
            result[index] = i;
            index += 2;
            count[i]--;
        }
    }

    *returnSize = barcodesSize;
    return result;      
}
