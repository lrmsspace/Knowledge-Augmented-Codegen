// Source: https://leetcode.com/problems/letter-tile-possibilities/   |   Difficulty: Medium
//
// Problem Description:
// You have n  tiles, where each tile has one letter tiles[i] printed on it.
//
// Return the number of possible non-empty sequences of letters you can make using the letters printed on those tiles.
//
// Example:
// Input: tiles = "AAB"
// Output: 8
// Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB", "ABA", "BAA".
//
// Constraints:
// 1 <= tiles.length <= 7
// 	tiles consists of uppercase English letters.
//

int numTilePossibilities(char* tiles) {
    int count[26] = {0};
    for (char* p = tiles; *p; ++p) {
        count[*p - 'A']++;
    }

    int result = 0;

    void backtrack() {
        for (int i = 0; i < 26; ++i) {
            if (count[i] == 0) {
                continue;
            }
            result++;
            count[i]--;
            backtrack();
            count[i]++;
        }
    }

    backtrack();
    return result;      
}
