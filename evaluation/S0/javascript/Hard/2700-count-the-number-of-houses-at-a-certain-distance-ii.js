// Source: https://leetcode.com/problems/count-the-number-of-houses-at-a-certain-distance-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given three positive integers n, x, and y.
//
// In a city, there exist houses numbered 1 to n connected by n streets. There is a street connecting the house numbered i with the house numbered i + 1 for all 1 <= i <= n - 1 . An additional street connects the house numbered x with the house numbered y.
//
// For each k, such that 1 <= k <= n, you need to find the number of pairs of houses (house1, house2) such that the minimum number of streets that need to be traveled to reach house2 from house1 is k.
//
// Return a 1-indexed array result of length n where result[k] represents the total number of pairs of houses such that the minimum streets required to reach one house from the other is k.
//
// Note that x and y can be equal.
//
// Example:
// Input: n = 3, x = 1, y = 3
// Output: [6,0,0]
// Explanation: Let's look at each pair of houses:
// - For the pair (1, 2), we can go from house 1 to house 2 directly.
// - For the pair (2, 1), we can go from house 2 to house 1 directly.
// - For the pair (1, 3), we can go from house 1 to house 3 directly.
// - For the pair (3, 1), we can go from house 3 to house 1 directly.
// - For the pair (2, 3), we can go from house 2 to house 3 directly.
// - For the pair (3, 2), we can go from house 3 to house 2 directly.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= x, y <= n
//

/**
 * @param {number} n
 * @param {number} x
 * @param {number} y
 * @return {number[]}
 */
var countOfPairs = function(n, x, y) {
    const result = new Array(n).fill(0);
    for (let i = 1; i <= n; i++) {
        for (let j = i + 1; j <= n; j++) {
            const directDistance = j - i;
            const viaXDistance = Math.abs(i - x) + 1 + Math.abs(j - y);
            const viaYDistance = Math.abs(i - y) + 1 + Math.abs(j - x);
            const minDistance = Math.min(directDistance, viaXDistance, viaYDistance);
            result[minDistance - 1]++;
        }
    }
    return result;
};
