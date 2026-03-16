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
 * @param {number[]} barcodes
 * @return {number[]}
 */
var rearrangeBarcodes = function(barcodes) {
    const freqMap = new Map();
    for (const code of barcodes) {
        freqMap.set(code, (freqMap.get(code) || 0) + 1);
    }
    const sortedCodes = Array.from(freqMap.entries()).sort((a, b) => b[1] - a[1]);
    const result = new Array(barcodes.length);
    let index = 0;
    for (const [code, freq] of sortedCodes) {
        for (let i = 0; i < freq; i++) {
            result[index] = code;
            index += 2;
            if (index >= barcodes.length) {
                index = 1;
            }
        }
    }
    return result;
        
};
