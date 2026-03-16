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

int numberOfWeakCharacters(int** properties, int propertiesSize, int* propertiesColSize) {
    // Sort properties by attack ascending, and by defense descending for equal attacks
    qsort(properties, propertiesSize, sizeof(int*), [](const void* a, const void* b) {
        int* propA = *(int**)a;
        int* propB = *(int**)b;
        if (propA[0] != propB[0]) {
            return propA[0] - propB[0];
        } else {
            return propB[1] - propA[1];
        }
    });

    int maxDefense = 0;
    int weakCount = 0;

    // Traverse from the end to the beginning
    for (int i = propertiesSize - 1; i >= 0; i--) {
        int defense = properties[i][1];
        if (defense < maxDefense) {
            weakCount++;
        } else {
            maxDefense = defense;
        }
    }

    return weakCount;       
}
