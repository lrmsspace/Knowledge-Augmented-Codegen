// Source: https://leetcode.com/problems/long-pressed-name/   |   Difficulty: Easy
//
// Problem Description:
// Your friend is typing his name into a keyboard. Sometimes, when typing a character c, the key might get long pressed, and the character will be typed 1 or more times.
//
// You examine the typed characters of the keyboard. Return True if it is possible that it was your friends name, with some characters (possibly none) being long pressed.
//
// Example:
// Input: name = "alex", typed = "aaleex"
// Output: true
// Explanation: 'a' and 'e' in 'alex' were long pressed.
//
// Constraints:
// 1 <= name.length, typed.length <= 1000
// 	name and typed consist of only lowercase English letters.
//

class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int i = 0, j = 0;
        while (i < name.size() && j < typed.size()) {
            if (name[i] == typed[j]) {
                i++;
                j++;
            } else if (j > 0 && typed[j] == typed[j - 1]) {
                j++;
            } else {
                return false;
            }
        }
        while (j < typed.size()) {
            if (typed[j] != typed[j - 1]) {
                return false;
            }
            j++;
        }
        return i == name.size();            
    }
};
