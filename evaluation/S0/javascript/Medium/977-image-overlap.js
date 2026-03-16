// Source: https://leetcode.com/problems/image-overlap/   |   Difficulty: Medium
//
// Problem Description:
// You are given two images, img1 and img2, represented as binary, square matrices of size n x n. A binary matrix has only 0s and 1s as values.
//
// We translate one image however we choose by sliding all the 1 bits left, right, up, and/or down any number of units. We then place it on top of the other image. We can then calculate the overlap by counting the number of positions that have a 1 in both images.
//
// Note also that a translation does not include any kind of rotation. Any 1 bits that are translated outside of the matrix borders are erased.
//
// Return the largest possible overlap.
//
// Example:
// Input: img1 = [[1,1,0],[0,1,0],[0,1,0]], img2 = [[0,0,0],[0,1,1],[0,0,1]]
// Output: 3
// Explanation: We translate img1 to right by 1 unit and down by 1 unit.
//
// The number of positions that have a 1 in both images is 3 (shown in red).
//
// Constraints:
// n == img1.length == img1[i].length
// 	n == img2.length == img2[i].length
// 	1 <= n <= 30
// 	img1[i][j] is either 0 or 1.
// 	img2[i][j] is either 0 or 1.
//

/**
 * @param {number[][]} img1
 * @param {number[][]} img2
 * @return {number}
 */
var largestOverlap = function(img1, img2) {
    const n = img1.length;
    let maxOverlap = 0;
    const getOverlap = (dx, dy) => {
        let overlap = 0;    
        for (let i = 0; i < n; i++) {
            for (let j = 0; j < n; j++) {
                const x = i + dx;
                const y = j + dy;
                if (x >= 0 && x < n && y >= 0 && y < n) {
                    overlap += img1[i][j] & img2[x][y];
                }
            }
        return overlap;
        }
    };
    for (let dx = -n + 1; dx < n; dx++) {
        for (let dy = -n + 1; dy < n; dy++) {
            maxOverlap = Math.max(maxOverlap, getOverlap(dx, dy));
        }
    }
    return maxOverlap;  
};
