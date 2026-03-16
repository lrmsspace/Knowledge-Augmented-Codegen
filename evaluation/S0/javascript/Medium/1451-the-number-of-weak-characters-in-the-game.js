// Source: https://leetcode.com/problems/the-number-of-weak-characters-in-the-game/   |   Difficulty: Medium
//
// Problem Description:
// You are playing a game that contains multiple characters, and each of the characters has two main properties: attack and defense. You are given a 2D integer array properties where properties[i] = [attacki, defensei] represents the properties of the ith character in the game.
//
// A character is said to be weak if any other character has both attack and defense levels strictly greater than this character's attack and defense levels. More formally, a character i is said to be weak if there exists another character j where attackj > attacki and defensej > defensei.
//
// Return the number of weak characters.
//
// Example:
// Input: properties = [[5,5],[6,3],[3,6]]
// Output: 0
// Explanation: No character has strictly greater attack and defense than the other.
//
// Constraints:
// 2 <= properties.length <= 105
// 	properties[i].length == 2
// 	1 <= attacki, defensei <= 105
//

/**
 * @param {number[][]} properties
 * @return {number}
 */
var numberOfWeakCharacters = function(properties) {
    // Sort by attack ascending, and by defense descending for same attack
    properties.sort((a, b) => a[0] === b[0] ? b[1] - a[1] : a[0] - b[0]);

    let maxDefense = 0;
    let weakCount = 0;
    // Traverse from the end to the beginning
    for (let i = properties.length - 1; i >= 0; i--) {
        const [attack, defense] = properties[i];
        if (defense < maxDefense) {
            weakCount++;
        }
            
        maxDefense = Math.max(maxDefense, defense);
    }
    return weakCount;   
    
};
