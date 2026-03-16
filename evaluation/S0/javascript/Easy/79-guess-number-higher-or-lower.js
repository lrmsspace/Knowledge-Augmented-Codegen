// Source: https://leetcode.com/problems/guess-number-higher-or-lower/   |   Difficulty: Easy
//
// Problem Description:
// We are playing the Guess Game. The game is as follows:
//
// I pick a number from 1 to n. You have to guess which number I picked (the number I picked stays the same throughout the game).
//
// Every time you guess wrong, I will tell you whether the number I picked is higher or lower than your guess.
//
// You call a pre-defined API int guess(int num), which returns three possible results:
//
//
// 	-1: Your guess is higher than the number I picked (i.e. num > pick).
// 	1: Your guess is lower than the number I picked (i.e. num < pick).
// 	0: your guess is equal to the number I picked (i.e. num == pick).
//
//
// Return the number that I picked.
//
// Example:
// Input: n = 10, pick = 6
// Output: 6
//
// Constraints:
// 1 <= n <= 231 - 1
// 	1 <= pick <= n
//

/** 
 * Forward declaration of guess API.
 * @param {number} num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * var guess = function(num) {}
 */

/**
 * @param {number} n
 * @return {number}
 */
var guessNumber = function(n) {
    let left = 1;
    let right = n;
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        const res = guess(mid);
        if (res === 0) {
            return mid;
        } else if (res < 0) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
};