// Source: https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given two strings s1 and s2, both of length 4, consisting of lowercase English letters.
//
// You can apply the following operation on any of the two strings any number of times:
//
//
// 	Choose any two indices i and j such that j - i = 2, then swap the two characters at those indices in the string.
//
//
// Return true if you can make the strings s1 and s2 equal, and false otherwise.
//
// Example:
// Input: s1 = "abcd", s2 = "cdab"
// Output: true
// Explanation: We can do the following operations on s1:
// - Choose the indices i = 0, j = 2. The resulting string is s1 = "cbad".
// - Choose the indices i = 1, j = 3. The resulting string is s1 = "cdab" = s2.
//
// Constraints:
// s1.length == s2.length == 4
// 	s1 and s2 consist only of lowercase English letters.
//

class Solution {
    public boolean canBeEqual(String s1, String s2) {
        char[] s1Arr = s1.toCharArray();
        char[] s2Arr = s2.toCharArray();

        char[] s1Even = new char[2];
        char[] s1Odd = new char[2];
        char[] s2Even = new char[2];
        char[] s2Odd = new char[2];

        for (int i = 0; i < 4; i++) {
            if (i % 2 == 0) {
                s1Even[i / 2] = s1Arr[i];
                s2Even[i / 2] = s2Arr[i];
            } else {
                s1Odd[i / 2] = s1Arr[i];
                s2Odd[i / 2] = s2Arr[i];
            }
        }

        Arrays.sort(s1Even);
        Arrays.sort(s1Odd);
        Arrays.sort(s2Even);
        Arrays.sort(s2Odd);

        return Arrays.equals(s1Even, s2Even) && Arrays.equals(s1Odd, s2Odd);            
    }
}
