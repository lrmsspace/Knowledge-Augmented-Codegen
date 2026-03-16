// Source: https://leetcode.com/problems/substrings-of-size-three-with-distinct-characters/   |   Difficulty: Easy
//
// Problem Description:
// A string is good if there are no repeated characters.
//
// Given a string s​​​​​, return the number of good substrings of length three in s​​​​​​.
//
// Note that if there are multiple occurrences of the same substring, every occurrence should be counted.
//
// A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: s = "xyzzaz"
// Output: 1
// Explanation: There are 4 substrings of size 3: "xyz", "yzz", "zza", and "zaz". 
// The only good substring of length 3 is "xyz".
//
// Constraints:
// 1 <= s.length <= 100
// 	s​​​​​​ consists of lowercase English letters.
//

class Solution {
    public int countGoodSubstrings(String s) {
        int count = 0;
        for (int i = 0; i < s.length() - 2; i++) {
            String substring = s.substring(i, i + 3);
            if (isGoodSubstring(substring)) {
                count++;
            }
        }
        return count;           
    }
}
