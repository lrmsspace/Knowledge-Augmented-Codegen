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

bool isIsomorphic(char* s, char* t) {
    int mapS[256] = {0};
    int mapT[256] = {0};
    
    for (int i = 0; s[i] != '\0'; i++) {
        char charS = s[i];
        char charT = t[i];
        
        if (mapS[(unsigned char)charS] != mapT[(unsigned char)charT]) {
            return false;
        }
        
        // Use i + 1 to avoid confusion with the default value of 0
        mapS[(unsigned char)charS] = i + 1;
        mapT[(unsigned char)charT] = i + 1;
    }
    
    return true;        
}
