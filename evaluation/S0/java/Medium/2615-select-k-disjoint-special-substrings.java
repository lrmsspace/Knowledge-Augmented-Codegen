// Source: https://leetcode.com/problems/select-k-disjoint-special-substrings/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s of length n and an integer k, determine whether it is possible to select k disjoint special substrings.
//
// A special substring is a substring where:
//
//
// 	Any character present inside the substring should not appear outside it in the string.
// 	The substring is not the entire string s.
//
//
// Note that all k substrings must be disjoint, meaning they cannot overlap.
//
// Return true if it is possible to select k such disjoint special substrings; otherwise, return false.
//
// Example:
// Input: s = "abcdbaefab", k = 2
//
// Output: true
//
// Explanation:
//
//
// 	We can select two disjoint special substrings: "cd" and "ef".
// 	"cd" contains the characters 'c' and 'd', which do not appear elsewhere in s.
// 	"ef" contains the characters 'e' and 'f', which do not appear elsewhere in s.
//
// Constraints:
// 2 <= n == s.length <= 5 * 104
// 	0 <= k <= 26
// 	s consists only of lowercase English letters.
//

class Solution {
    public boolean maxSubstringLength(String s, int k) {
        int n = s.length();
        int[] firstOccurrence = new int[26];
        int[] lastOccurrence = new int[26];

        // Initialize first and last occurrence arrays
        for (int i = 0; i < 26; i++) {
            firstOccurrence[i] = -1;
            lastOccurrence[i] = -1;
        }

        // Record the first and last occurrence of each character
        for (int i = 0; i < n; i++) {
            char ch = s.charAt(i);
            int index = ch - 'a';
            if (firstOccurrence[index] == -1) {
                firstOccurrence[index] = i;
            }
            lastOccurrence[index] = i;
        }

        int count = 0;
        boolean[] visited = new boolean[26];

        // Iterate through the string to find special substrings
        for (int i = 0; i < n; ) {
            char ch = s.charAt(i);
            int index = ch - 'a';

            // If this character has already been visited, skip it
            if (visited[index]) {
                i++;
                continue;
            }

            // Determine the end of the current special substring
            int end = lastOccurrence[index];
            boolean isSpecial = true;

            for (int j = i; j <= end; j++) {
                char currentChar = s.charAt(j);
                int currentIndex = currentChar - 'a';
                if (firstOccurrence[currentIndex] < i || lastOccurrence[currentIndex] > end) {
                    isSpecial = false;
                    break;
                }
                end = Math.max(end, lastOccurrence[currentIndex]);
                visited[currentIndex] = true;
            }

            if (isSpecial) {
                count++;
                if (count >= k) {
                    return true;
                }
            }

            i = end + 1;
        }

        return false;           
    }
}
