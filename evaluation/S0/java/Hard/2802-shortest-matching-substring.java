// Source: https://leetcode.com/problems/shortest-matching-substring/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and a pattern string p, where p contains exactly two '*' characters.
//
// The '*' in p matches any sequence of zero or more characters.
//
// Return the length of the shortest substring in s that matches p. If there is no such substring, return -1.
// Note: The empty substring is considered valid.
//
// Example:
// Input: s = "abaacbaecebce", p = "ba*c*ce"
//
// Output: 8
//
// Explanation:
//
// The shortest matching substring of p in s is "baecebce".
//
// Constraints:
// 1 <= s.length <= 105
// 	2 <= p.length <= 105
// 	s contains only lowercase English letters.
// 	p contains only lowercase English letters and exactly two '*'.
//

class Solution {
    public int shortestMatchingSubstring(String s, String p) {
        String[] parts = p.split("\\*");
        String firstPart = parts[0];
        String secondPart = parts[1];
        String thirdPart = parts[2];

        int n = s.length();
        int m1 = firstPart.length();
        int m2 = secondPart.length();
        int m3 = thirdPart.length();

        int[] left = new int[n];
        int[] right = new int[n];

        // Fill left array
        for (int i = 0, j = 0; i < n && j < m1; i++) {
            if (s.charAt(i) == firstPart.charAt(j)) {
                j++;
            }
            left[i] = j;
        }

        // Fill right array
        for (int i = n - 1, j = m3 - 1; i >= 0 && j >= 0; i--) {
            if (s.charAt(i) == thirdPart.charAt(j)) {
                j--;
            }
            right[i] = m3 - 1 - j;
        }

        int minLength = Integer.MAX_VALUE;

        // Find the shortest matching substring
        for (int i = 0; i < n; i++) {
            if (left[i] == m1) {
                for (int j = i + 1; j < n; j++) {
                    if (right[j] == m3) {
                        // Check if the middle part can match
                        if (j - i - 1 >= m2) {
                            minLength = Math.min(minLength, j - i + 1);
                        }
                    }
                }
            }
        }

        return minLength == Integer.MAX_VALUE ? -1 : minLength;         
    }
}
