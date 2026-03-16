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

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, char> s_to_t;
        unordered_map<char, char> t_to_s;

        for (size_t i = 0; i < s.length(); ++i) {
            char sc = s[i];
            char tc = t[i];

            if (s_to_t.count(sc) == 0 && t_to_s.count(tc) == 0) {
                s_to_t[sc] = tc;
                t_to_s[tc] = sc;
            } else {
                if (s_to_t[sc] != tc || t_to_s[tc] != sc) {
                    return false;
                }
            }
        }

        return true;            
    }
};
