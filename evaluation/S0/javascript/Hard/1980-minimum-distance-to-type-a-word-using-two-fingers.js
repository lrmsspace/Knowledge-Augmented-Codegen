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

/**
 * @param {string} word
 * @return {number}
 */
var minimumDistance = function(word) {
    const n = word.length;
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
    const dp = new Map();
    const dfs = (i, finger1, finger2) => {
        if (i === n) return 0;
        const key = `${i},${finger1},${finger2}`;
        if (dp.has(key)) return dp.get(key);
        const char = word[i];
        const cost1 = distance(finger1, char) + dfs(i + 1, char, finger2);
        const cost2 = distance(finger2, char) + dfs(i + 1, finger1, char);
        const result = Math.min(cost1, cost2);
        dp.set(key, result);
        return result;
    };
    return dfs(0, null, null);
};
