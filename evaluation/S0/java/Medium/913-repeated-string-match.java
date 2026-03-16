// Source: https://leetcode.com/problems/repeated-string-match/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings a and b, return the minimum number of times you should repeat string a so that string b is a substring of it. If it is impossible for b​​​​​​ to be a substring of a after repeating it, return -1.
//
// Notice: string "abc" repeated 0 times is "", repeated 1 time is "abc" and repeated 2 times is "abcabc".
//
// Example:
// Input: a = "abcd", b = "cdabcdab"
// Output: 3
// Explanation: We return 3 because by repeating a three times "abcdabcdabcd", b is a substring of it.
//
// Constraints:
// 1 <= a.length, b.length <= 104
// 	a and b consist of lowercase English letters.
//

class Solution {
    public int repeatedStringMatch(String a, String b) {
        int count = 0;
        StringBuilder repeatedA = new StringBuilder();

        // Repeat string a until its length is at least that of b
        while (repeatedA.length() < b.length()) {
            repeatedA.append(a);
            count++;
        }

        // Check if b is a substring of the current repeated a
        if (repeatedA.toString().contains(b)) {
            return count;
        }

        // Append one more a to cover the case where b overlaps the boundary
        repeatedA.append(a);
        count++;

        // Final check for b as a substring
        if (repeatedA.toString().contains(b)) {
            return count;
        }

        // If b is still not found, return -1
        return -1;          
    }
}
