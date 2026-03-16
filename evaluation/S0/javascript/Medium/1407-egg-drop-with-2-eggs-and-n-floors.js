// Source: https://leetcode.com/problems/egg-drop-with-2-eggs-and-n-floors/   |   Difficulty: Medium
//
// Problem Description:
// You are given two identical eggs and you have access to a building with n floors labeled from 1 to n.
//
// You know that there exists a floor f where 0 <= f <= n such that any egg dropped at a floor higher than f will break, and any egg dropped at or below floor f will not break.
//
// In each move, you may take an unbroken egg and drop it from any floor x (where 1 <= x <= n). If the egg breaks, you can no longer use it. However, if the egg does not break, you may reuse it in future moves.
//
// Return the minimum number of moves that you need to determine with certainty what the value of f is.
//
// Example:
// Input: n = 2
// Output: 2
// Explanation: We can drop the first egg from floor 1 and the second egg from floor 2.
// If the first egg breaks, we know that f = 0.
// If the second egg breaks but the first egg didn't, we know that f = 1.
// Otherwise, if both eggs survive, we know that f = 2.
//
// Constraints:
// 1 <= n <= 1000
//

/**
 * @param {number} n
 * @return {number}
 */
var twoEggDrop = function(n) {
    let left = 1;
    let right = n;
    let result = n;
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        const moves = Math.ceil((-1 + Math.sqrt(1 + 8 * mid)) / 2);
        if (moves * (moves + 1) / 2 >= mid) {
            result = Math.min(result, moves);
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return result;  
};
