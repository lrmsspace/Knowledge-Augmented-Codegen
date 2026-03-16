// Source: https://leetcode.com/problems/number-of-changing-keys/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed string s typed by a user. Changing a key is defined as using a key different from the last used key. For example, s = "ab" has a change of a key while s = "bBBb" does not have any.
//
// Return the number of times the user had to change the key. 
//
// Note: Modifiers like shift or caps lock won't be counted in changing the key that is if a user typed the letter 'a' and then the letter 'A' then it will not be considered as a changing of key.
//
// Example:
// Input: s = "aAbBcC"
// Output: 2
// Explanation: 
// From s[0] = 'a' to s[1] = 'A', there is no change of key as caps lock or shift is not counted.
// From s[1] = 'A' to s[2] = 'b', there is a change of key.
// From s[2] = 'b' to s[3] = 'B', there is no change of key as caps lock or shift is not counted.
// From s[3] = 'B' to s[4] = 'c', there is a change of key.
// From s[4] = 'c' to s[5] = 'C', there is no change of key as caps lock or shift is not counted.
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists of only upper case and lower case English letters.
//

class Solution {
public:
    int countKeyChanges(string s) {
        int changes = 0;
        for (int i = 1; i < s.length(); i++) {
            if (tolower(s[i]) != tolower(s[i - 1])) {
                changes++;
            }
        }
        return changes;         
    }
};
