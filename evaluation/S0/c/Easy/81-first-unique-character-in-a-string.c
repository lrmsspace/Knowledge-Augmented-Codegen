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

int firstUniqChar(char* s) {
    int count[26] = {0};
    for (char* p = s; *p != '\0'; p++) {
        count[*p - 'a']++;
    }
    for (int i = 0; s[i] != '\0'; i++) {
        if (count[s[i] - 'a'] == 1) {
            return i;
        }
    }
    return -1;      
}
