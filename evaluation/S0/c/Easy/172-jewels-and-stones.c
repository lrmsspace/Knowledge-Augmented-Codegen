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

int numJewelsInStones(char* jewels, char* stones) {
    int count = 0;
    for (int i = 0; stones[i] != '\0'; i++) {
        for (int j = 0; jewels[j] != '\0'; j++) {
            if (stones[i] == jewels[j]) {
                count++;
                break;
            }
        }
    }
    return count;       
}
