// Source: https://leetcode.com/problems/find-the-string-with-lcp/   |   Difficulty: Hard
//
// Problem Description:
// We define the lcp matrix of any 0-indexed string word of n lowercase English letters as an n x n grid such that:
//
//
// 	lcp[i][j] is equal to the length of the longest common prefix between the substrings word[i,n-1] and word[j,n-1].
//
//
// Given an n x n matrix lcp, return the alphabetically smallest string word that corresponds to lcp. If there is no such string, return an empty string.
//
// A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b. For example, "aabd" is lexicographically smaller than "aaca" because the first position they differ is at the third letter, and 'b' comes before 'c'.
//
// Example:
// Input: lcp = [[4,0,2,0],[0,3,0,1],[2,0,2,0],[0,1,0,1]]
// Output: "abab"
// Explanation: lcp corresponds to any 4 letter string with two alternating letters. The lexicographically smallest of them is "abab".
//
// Constraints:
// 1 <= n == lcp.length == lcp[i].length <= 1000
// 	0 <= lcp[i][j] <= n
//

class Solution {
    public String findTheString(int[][] lcp) {
        int n = lcp.length;
        char[] res = new char[n];
        int currChar = 0;

        for (int i = 0; i < n; i++) {
            if (res[i] == 0) {
                if (currChar == 26) {
                    return "";
                }
                res[i] = (char) ('a' + currChar);
                currChar++;
            }
            for (int j = i + 1; j < n; j++) {
                if (lcp[i][j] > 0) {
                    res[j] = res[i];
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int expectedLcp = lcp[i][j];
                int actualLcp = 0;
                while (i + actualLcp < n && j + actualLcp < n
                        && res[i + actualLcp] == res[j + actualLcp]) {
                    actualLcp++;
                }
                if (expectedLcp != actualLcp) {
                    return "";
                }
            }
        }

        return new String(res);         
    }
}
