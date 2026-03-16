// Source: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, return the lexicographically smallest subsequence of s that contains all the distinct characters of s exactly once.
//
// Example:
// Input: s = "bcabc"
// Output: "abc"
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists of lowercase English letters.
//
//
//  
// Note: This question is the same as 316: https://leetcode.com/problems/remove-duplicate-letters/
//

class Solution {
    public String smallestSubsequence(String s) {
        int[] lastIndex = new int[26];
        boolean[] seen = new boolean[26];
        char[] arr = s.toCharArray();
        int n = arr.length;

        for (int i = 0; i < n; i++) {
            lastIndex[arr[i] - 'a'] = i;
        }

        StringBuilder sb = new StringBuilder();
        Deque<Character> stack = new ArrayDeque<>();

        for (int i = 0; i < n; i++) {
            char c = arr[i];
            if (seen[c - 'a']) {
                continue;
            }

            while (!stack.isEmpty() && stack.peekLast() > c && lastIndex[stack.peekLast() - 'a'] > i) {
                char removed = stack.removeLast();
                seen[removed - 'a'] = false;
            }

            stack.addLast(c);
            seen[c - 'a'] = true;
        }

        for (char c : stack) {
            sb.append(c);
        }

        return sb.toString();           
    }
}
