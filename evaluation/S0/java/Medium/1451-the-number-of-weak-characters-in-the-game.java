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

class Solution {
    public int numberOfWeakCharacters(int[][] properties) {
        // Sort by attack in descending order, and by defense in ascending order
        Arrays.sort(properties, (a, b) -> {
            if (a[0] != b[0]) {
                return b[0] - a[0]; // Descending order for attack
            } else {
                return a[1] - b[1]; // Ascending order for defense
            }
        });

        int maxDefense = 0;
        int weakCharactersCount = 0;

        for (int[] property : properties) {
            int attack = property[0];
            int defense = property[1];

            // If current defense is less than the maximum defense seen so far,
            // it means there exists a character with higher attack and defense
            if (defense < maxDefense) {
                weakCharactersCount++;
            } else {
                // Update the maximum defense encountered
                maxDefense = Math.max(maxDefense, defense);
            }
        }

        return weakCharactersCount;         
    }
}
