// Source: https://leetcode.com/problems/jewels-and-stones/   |   Difficulty: Easy
//
// Problem Description:
// You're given strings jewels representing the types of stones that are jewels, and stones representing the stones you have. Each character in stones is a type of stone you have. You want to know how many of the stones you have are also jewels.
//
// Letters are case sensitive, so "a" is considered a different type of stone from "A".
//
// Example:
// Input: jewels = "aA", stones = "aAAbbbb"
// Output: 3
//
// Constraints:
// 1 <= jewels.length, stones.length <= 50
// 	jewels and stones consist of only English letters.
// 	All the characters of jewels are unique.
//

/**
 * @param {string} jewels
 * @param {string} stones
 * @return {number}
 */
var numJewelsInStones = function(jewels, stones) {
    const jewelSet = new Set(jewels);                                           
    let count = 0;
    for (const stone of stones) {
        if (jewelSet.has(stone)) {
            count++;
        }
    }
    return count;
};