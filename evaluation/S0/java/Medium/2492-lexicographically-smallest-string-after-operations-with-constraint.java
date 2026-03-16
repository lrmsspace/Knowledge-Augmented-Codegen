// Source: https://leetcode.com/problems/lexicographically-smallest-string-after-operations-with-constraint/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and an integer k.
//
// Define a function distance(s1, s2) between two strings s1 and s2 of the same length n as:
//
//
// 	The sum of the minimum distance between s1[i] and s2[i] when the characters from 'a' to 'z' are placed in a cyclic order, for all i in the range [0, n - 1].
//
//
// For example, distance("ab", "cd") == 4, and distance("a", "z") == 1.
//
// You can change any letter of s to any other lowercase English letter, any number of times.
//
// Return a string denoting the lexicographically smallest string t you can get after some changes, such that distance(s, t) <= k.
//
// Example:
// Input: s = "zbbz", k = 3
//
// Output: "aaaz"
//
// Explanation:
//
// Change s to "aaaz". The distance between "zbbz" and "aaaz" is equal to k = 3.
//
// Constraints:
// 1 <= s.length <= 100
// 	0 <= k <= 2000
// 	s consists only of lowercase English letters.
//

class Solution {
    public String getSmallestString(String s, int k) {
        StringBuilder result = new StringBuilder();
        int n = s.length();

        for (int i = 0; i < n; i++) {
            char currentChar = s.charAt(i);
            int distanceToA = currentChar - 'a';
            int distanceToZ = 'z' - currentChar;

            if (distanceToA <= distanceToZ) {
                if (k >= distanceToA) {
                    result.append('a');
                    k -= distanceToA;
                } else {
                    char newChar = (char) (currentChar - k);
                    result.append(newChar);
                    k = 0;
                }
            } else {
                if (k >= distanceToZ) {
                    result.append('z');
                    k -= distanceToZ;
                } else {
                    char newChar = (char) (currentChar + k);
                    result.append(newChar);
                    k = 0;
                }
            }
        }

        return result.toString();           
    }
}
