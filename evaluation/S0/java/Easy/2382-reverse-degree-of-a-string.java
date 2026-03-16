// Source: https://leetcode.com/problems/reverse-degree-of-a-string/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, calculate its reverse degree.
//
// The reverse degree is calculated as follows:
//
//
// 	For each character, multiply its position in the reversed alphabet ('a' = 26, 'b' = 25, ..., 'z' = 1) with its position in the string (1-indexed).
// 	Sum these products for all characters in the string.
//
//
// Return the reverse degree of s.
//
// Example:
// Input: s = "abc"
//
// Output: 148
//
// Explanation:
//
//
// 	
// 		
// 			Letter
// 			Index in Reversed Alphabet
// 			Index in String
// 			Product
// 		
// 		
// 			'a'
// 			26
// 			1
// 			26
// 		
// 		
// 			'b'
// 			25
// 			2
// 			50
// 		
// 		
// 			'c'
// 			24
// 			3
// 			72
// 		
// 	
//
//
// The reversed degree is 26 + 50 + 72 = 148.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s contains only lowercase English letters.
//

class Solution {
    public int reverseDegree(String s) {
        int reverseDegree = 0;
        int length = s.length();

        for (int i = 0; i < length; i++) {
            char ch = s.charAt(i);
            int indexInReversedAlphabet = 'z' - ch + 1; // 'a' = 26, 'b' = 25, ..., 'z' = 1
            int indexInString = i + 1; // 1-indexed
            reverseDegree += indexInReversedAlphabet * indexInString;
        }

        return reverseDegree;           
    }
}
