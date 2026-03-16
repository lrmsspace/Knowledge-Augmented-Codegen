// Source: https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/   |   Difficulty: Hard
//
// Problem Description:
// You have a keyboard layout as shown above in the X-Y plane, where each English uppercase letter is located at some coordinate.
//
//
// 	For example, the letter 'A' is located at coordinate (0, 0), the letter 'B' is located at coordinate (0, 1), the letter 'P' is located at coordinate (2, 3) and the letter 'Z' is located at coordinate (4, 1).
//
//
// Given the string word, return the minimum total distance to type such string using only two fingers.
//
// The distance between coordinates (x1, y1) and (x2, y2) is |x1 - x2| + |y1 - y2|.
//
// Note that the initial positions of your two fingers are considered free so do not count towards your total distance, also your two fingers do not have to start at the first letter or the first two letters.
//
// Example:
// Input: word = "CAKE"
// Output: 3
// Explanation: Using two fingers, one optimal way to type "CAKE" is: 
// Finger 1 on letter 'C' -> cost = 0 
// Finger 1 on letter 'A' -> cost = Distance from letter 'C' to letter 'A' = 2 
// Finger 2 on letter 'K' -> cost = 0 
// Finger 2 on letter 'E' -> cost = Distance from letter 'K' to letter 'E' = 1 
// Total distance = 3
//
// Constraints:
// 2 <= word.length <= 300
// 	word consists of uppercase English letters.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} word
 * @return {number}
 */
var minimumDistance = function(word) {
    const charToCoord = (char) => {
        const index = char.charCodeAt(0) - 'A'.charCodeAt(0);
        return [Math.floor(index / 6), index % 6];
    };
    
    const distance = (char1, char2) => {
        if (char1 === null || char2 === null) return 0;
        const [x1, y1] = charToCoord(char1);
        const [x2, y2] = charToCoord(char2);
        return Math.abs(x1 - x2) + Math.abs(y1 - y2);
    };
    
    const n = word.length;
    const dp = new Array(n + 1).fill(0).map(() => new Array(n + 1).fill(Infinity));
    dp[0][0] = 0;
    
    for (let i = 1; i <= n; i++) {
        const char = word[i - 1];
        for (let j = 0; j < i; j++) {
            const prevChar = word[j];
            dp[i][j] = Math.min(dp[i][j], dp[i - 1][j] + distance(prevChar, char));
            if (i > 1) {
                dp[i][i - 1] = Math.min(dp[i][i - 1], dp[i - 1][j] + distance(prevChar, char));
            }
        }
    }
    
    let minDistance = Infinity;
    for (let j = 0; j < n; j++) {
        minDistance = Math.min(minDistance, dp[n][j]);
    }
    
    return minDistance;
};
