// Source: https://leetcode.com/problems/reconstruct-original-digits-from-english/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s containing an out-of-order English representation of digits 0-9, return the digits in ascending order.
//
// Example:
// Input: s = "owoztneoer"
// Output: "012"
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is one of the characters ["e","g","f","i","h","o","n","s","r","u","t","w","v","x","z"].
// 	s is guaranteed to be valid.
//

class Solution {
public:
    string originalDigits(string s) {
        vector<int> count(10, 0);
        vector<int> charCount(26, 0);

        for (char c : s) {
            charCount[c - 'a']++;
        }

        // Unique letters for certain digits
        count[0] = charCount['z' - 'a']; // zero
        count[2] = charCount['w' - 'a']; // two
        count[4] = charCount['u' - 'a']; // four
        count[6] = charCount['x' - 'a']; // six
        count[8] = charCount['g' - 'a']; // eight

        // Letters that appear in multiple digits
        count[3] = charCount['h' - 'a'] - count[8]; // three
        count[5] = charCount['f' - 'a'] - count[4]; // five
        count[7] = charCount['s' - 'a'] - count[6]; // seven
        count[1] = charCount['o' - 'a'] - count[0] - count[2] - count[4]; // one
        count[9] = charCount['i' - 'a'] - count[5] - count[6] - count[8]; // nine

        string result;
        for (int i = 0; i <= 9; ++i) {
            result += string(count[i], '0' + i);
        }

        return result;          
    }
};
