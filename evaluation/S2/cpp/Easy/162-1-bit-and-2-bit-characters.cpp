// Source: https://leetcode.com/problems/1-bit-and-2-bit-characters/   |   Difficulty: Easy
//
// Problem Description:
// We have two special characters:
//
//
// 	The first character can be represented by one bit 0.
// 	The second character can be represented by two bits (10 or 11).
//
//
// Given a binary array bits that ends with 0, return true if the last character must be a one-bit character.
//
// Example:
// Input: bits = [1,0,0]
// Output: true
// Explanation: The only way to decode it is two-bit character and one-bit character.
// So the last character is one-bit character.
//
// Constraints:
// 1 <= bits.length <= 1000
// 	bits[i] is either 0 or 1.
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
    bool isOneBitCharacter(vector<int>& bits) {
        int n = bits.size();
        int i = 0;
        while (i < n - 1) {
            if (bits[i] == 0) {
                i += 1; // One-bit character
            } else {
                i += 2; // Two-bit character
            }
        }
        return i == n - 1; // Check if we ended on the last character           
    }
};
