// Source: https://leetcode.com/problems/isomorphic-strings/   |   Difficulty: Easy
//
// Problem Description:
// Given two strings s and t, determine if they are isomorphic.
//
// Two strings s and t are isomorphic if the characters in s can be replaced to get t.
//
// All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.
//
// Example:
// Input: s = "egg", t = "add"
//
// Output: true
//
// Explanation:
//
// The strings s and t can be made identical by:
//
//
// 	Mapping 'e' to 'a'.
// 	Mapping 'g' to 'd'.
//
// Constraints:
// 1 <= s.length <= 5 * 104
// 	t.length == s.length
// 	s and t consist of any valid ascii character.
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
    bool isIsomorphic(string s, string t) {
        if (s.size() != t.size()) {
            return false;
        }

        unordered_map<char, char> s_to_t;
        unordered_map<char, char> t_to_s;

        for (size_t i = 0; i < s.size(); ++i) {
            char sc = s[i];
            char tc = t[i];

            if (s_to_t.count(sc) && s_to_t[sc] != tc) {
                return false;
            }
            if (t_to_s.count(tc) && t_to_s[tc] != sc) {
                return false;
            }

            s_to_t[sc] = tc;
            t_to_s[tc] = sc;
        }

        return true;            
    }
};
