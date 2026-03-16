// Source: https://leetcode.com/problems/first-unique-character-in-a-string/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, find the first non-repeating character in it and return its index. If it does not exist, return -1.
//
// Example:
// Input: s = "leetcode"
//
// Output: 0
//
// Explanation:
//
// The character 'l' at index 0 is the first character that does not occur at any other index.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of only lowercase English letters.
//

class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> charCount;
        
        // Count the occurrences of each character
        for (char c : s) {
            charCount[c]++;
        }
        
        // Find the first unique character
        for (int i = 0; i < s.length(); i++) {
            if (charCount[s[i]] == 1) {
                return i;
            }
        }
        
        return -1; // No unique character found         
    }
};
