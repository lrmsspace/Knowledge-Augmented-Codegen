// Source: https://leetcode.com/problems/largest-substring-between-two-equal-characters/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, return the length of the longest substring between two equal characters, excluding the two characters. If there is no such substring return -1.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "aa"
// Output: 0
// Explanation: The optimal substring here is an empty substring between the two 'a's.
//
// Constraints:
// 1 <= s.length <= 300
// 	s contains only lowercase English letters.
//

class Solution {
public:
    int maxLengthBetweenEqualCharacters(string s) {
        int maxLength = -1;
        unordered_map<char, int> charIndexMap;

        for (int i = 0; i < s.length(); ++i) {
            char currentChar = s[i];

            if (charIndexMap.find(currentChar) != charIndexMap.end()) {
                int substringLength = i - charIndexMap[currentChar] - 1;
                maxLength = max(maxLength, substringLength);
            } else {
                charIndexMap[currentChar] = i;
            }
        }

        return maxLength;           
    }
};
