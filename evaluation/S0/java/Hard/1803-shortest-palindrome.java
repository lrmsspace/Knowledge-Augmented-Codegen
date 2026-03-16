// Source: https://leetcode.com/problems/shortest-palindrome/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s. You can convert s to a palindrome by adding characters in front of it.
//
// Return the shortest palindrome you can find by performing this transformation.
//
// Example:
// Input: s = "aacecaaa"
// Output: "aaacecaaa"
//
// Constraints:
// 0 <= s.length <= 5 * 104
// 	s consists of lowercase English letters only.
//

class Solution {
    public String shortestPalindrome(String s) {
        String rev = new StringBuilder(s).reverse().toString();
        String l = s + "#" + rev;
        int[] p = new int[l.length()];

        for (int i = 1; i < l.length(); i++) {
            int j = p[i - 1];
            while (j > 0 && l.charAt(i) != l.charAt(j)) {
                j = p[j - 1];
            }
            if (l.charAt(i) == l.charAt(j)) {
                j++;
            }
            p[i] = j;
        }

        return rev.substring(0, s.length() - p[l.length() - 1]) + s;            
    }
}
