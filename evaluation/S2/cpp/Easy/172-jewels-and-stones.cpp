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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int numJewelsInStones(string jewels, string stones) {
        int count = 0;
        for (char stone : stones) {
            if (jewels.find(stone) != string::npos) {
                count++;
            }
        }
        return count;           
    }
};
