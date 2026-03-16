// Source: https://leetcode.com/problems/jump-game-v/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of integers arr and an integer d. In one step you can jump from index i to index:
//
//
// 	i + x where: i + x < arr.length and  0 < x <= d.
// 	i - x where: i - x >= 0 and  0 < x <= d.
//
//
// In addition, you can only jump from index i to index j if arr[i] > arr[j] and arr[i] > arr[k] for all indices k between i and j (More formally min(i, j) < k < max(i, j)).
//
// You can choose any index of the array and start jumping. Return the maximum number of indices you can visit.
//
// Notice that you can not jump outside of the array at any time.
//
// Example:
// Input: arr = [6,4,14,6,8,13,9,7,10,6,12], d = 2
// Output: 4
// Explanation: You can start at index 10. You can jump 10 --> 8 --> 6 --> 7 as shown.
// Note that if you start at index 6 you can only jump to index 7. You cannot jump to index 5 because 13 > 9. You cannot jump to index 4 because index 5 is between index 4 and 6 and 13 > 9.
// Similarly You cannot jump from index 3 to index 2 or index 1.
//
// Constraints:
// 1 <= arr.length <= 1000
// 	1 <= arr[i] <= 105
// 	1 <= d <= arr.length
//

/**
 * @param {number[]} arr
 * @param {number} d
 * @return {number}
 */
var maxJumps = function(arr, d) {
    const n = arr.length;
    const dp = new Array(n).fill(0);
    const indices = Array.from({ length: n }, (_, i) => i);
    indices.sort((a, b) => arr[a] - arr[b]);
    for (const i of indices) {
        dp[i] = 1;
        for (let j = i - 1; j >= Math.max(0, i - d); j--) {
            if (arr[j] >= arr[i]) {
                break;
            }
            dp[i] = Math.max(dp[i], dp[j] + 1);
        }
        for (let j = i + 1; j <= Math.min(n - 1, i + d); j++) {
            if (arr[j] >= arr[i]) {
                break;
            }
            dp[i] = Math.max(dp[i], dp[j] + 1);
        }
    }
    return Math.max(...dp); 
};
