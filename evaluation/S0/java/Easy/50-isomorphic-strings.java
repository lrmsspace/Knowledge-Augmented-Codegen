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
    public boolean isIsomorphic(String s, String t) {
        int[] mapS = new int[256];
        int[] mapT = new int[256];

        for (int i = 0; i < s.length(); i++) {
            char charS = s.charAt(i);
            char charT = t.charAt(i);

            if (mapS[charS] != mapT[charT]) {
                return false;
            }

            mapS[charS] = i + 1;
            mapT[charT] = i + 1;
        }

        return true;            
    }
}
