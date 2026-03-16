// Source: https://leetcode.com/problems/couples-holding-hands/   |   Difficulty: Hard
//
// Problem Description:
// There are n couples sitting in 2n seats arranged in a row and want to hold hands.
//
// The people and seats are represented by an integer array row where row[i] is the ID of the person sitting in the ith seat. The couples are numbered in order, the first couple being (0, 1), the second couple being (2, 3), and so on with the last couple being (2n - 2, 2n - 1).
//
// Return the minimum number of swaps so that every couple is sitting side by side. A swap consists of choosing any two people, then they stand up and switch seats.
//
// Example:
// Input: row = [0,2,1,3]
// Output: 1
// Explanation: We only need to swap the second (row[1]) and third (row[2]) person.
//
// Constraints:
// 2n == row.length
// 	2 <= n <= 30
// 	n is even.
// 	0 <= row[i] < 2n
// 	All the elements of row are unique.
//

/**
 * @param {number[]} row
 * @return {number}
 */
var minSwapsCouples = function(row) {
    


    let swaps = 0;
    for (let i = 0; i < row.length; i += 2) {
        const first = row[i];
        const second = row[i + 1];
        const partner = first ^ 1; // The partner of 'first' is 'first ^ 1' (0 <-> 1, 2 <-> 3, etc.)
        if (second !== partner) {
            swaps++;
            // Find the partner and swap
            for (let j = i + 2; j < row.length; j++) {
                if (row[j] === partner) {
                    [row[i + 1], row[j]] = [row[j], row[i + 1]]; // Swap the partner to the correct position
                    break;
                }
            }
        }
    }
    return swaps;
    
};
