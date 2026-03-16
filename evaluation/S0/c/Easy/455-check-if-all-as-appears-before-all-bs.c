// Source: https://leetcode.com/problems/check-if-all-as-appears-before-all-bs/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s consisting of only the characters 'a' and 'b', return true if every 'a' appears before every 'b' in the string. Otherwise, return false.
//
// Example:
// Input: s = "aaabbb"
// Output: true
// Explanation:
// The 'a's are at indices 0, 1, and 2, while the 'b's are at indices 3, 4, and 5.
// Hence, every 'a' appears before every 'b' and we return true.
//
// Constraints:
// 1 <= s.length <= 100
// 	s[i] is either 'a' or 'b'.
//

bool checkString(char* s) {
    int seen_b = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == 'b') {
            seen_b = 1;
        } else if (seen_b && s[i] == 'a') {
            return false;
        }
    }
    return true;        
}
