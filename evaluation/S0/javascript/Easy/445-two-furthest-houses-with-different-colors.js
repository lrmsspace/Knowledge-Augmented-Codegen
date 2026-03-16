// Source: https://leetcode.com/problems/two-furthest-houses-with-different-colors/   |   Difficulty: Easy
//
// Problem Description:
// There are n houses evenly lined up on the street, and each house is beautifully painted. You are given a 0-indexed integer array colors of length n, where colors[i] represents the color of the ith house.
//
// Return the maximum distance between two houses with different colors.
//
// The distance between the ith and jth houses is abs(i - j), where abs(x) is the absolute value of x.
//
// Example:
// Input: colors = [1,1,1,6,1,1,1]
// Output: 3
// Explanation: In the above image, color 1 is blue, and color 6 is red.
// The furthest two houses with different colors are house 0 and house 3.
// House 0 has color 1, and house 3 has color 6. The distance between them is abs(0 - 3) = 3.
// Note that houses 3 and 6 can also produce the optimal answer.
//
// Constraints:
// n == colors.length
// 	2 <= n <= 100
// 	0 <= colors[i] <= 100
// 	Test data are generated such that at least two houses have different colors.
//

/**
 * @param {number[]} colors
 * @return {number}
 */
var maxDistance = function(colors) {
    let left = 0;
    let right = colors.length - 1;
    let maxDist = 0;
    while (left < right) {
        if (colors[left] !== colors[right]) {
            maxDist = Math.max(maxDist, right - left);
            break;
        }
        if (colors[left] === colors[right]) {
            if (colors[left] === colors[left + 1]) {
                left++;
            } else {
                right--;
            }
        }
    }
    return maxDist;
};