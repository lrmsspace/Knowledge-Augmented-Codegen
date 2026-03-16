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
    public String originalDigits(String s) {
        int[] count = new int[10];
        int[] charCount = new int[26];

        for (char c : s.toCharArray()) {
            charCount[c - 'a']++;
        }

        count[0] = charCount['z' - 'a'];
        count[2] = charCount['w' - 'a'];
        count[4] = charCount['u' - 'a'];
        count[6] = charCount['x' - 'a'];
        count[8] = charCount['g' - 'a'];

        count[3] = charCount['h' - 'a'] - count[8];
        count[5] = charCount['f' - 'a'] - count[4];
        count[7] = charCount['s' - 'a'] - count[6];

        count[1] = charCount['o' - 'a'] - count[0] - count[2] - count[4];
        count[9] = charCount['i' - 'a'] - count[5] - count[6] - count[8];

        StringBuilder result = new StringBuilder();
        for (int i = 0; i <= 9; i++) {
            for (int j = 0; j < count[i]; j++) {
                result.append(i);
            }
        }

        return result.toString();           
    }
}
