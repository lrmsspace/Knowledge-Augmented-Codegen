// Source: https://leetcode.com/problems/remove-duplicate-letters/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.
//
// Example:
// Input: s = "bcabc"
// Output: "abc"
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of lowercase English letters.
//
//
//  
// Note: This question is the same as 1081: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/
//

class Solution {
    public String removeDuplicateLetters(String s) {
        int[] lastIndex = new int[26];
        boolean[] visited = new boolean[26];
        char[] charArray = s.toCharArray();
        int n = charArray.length;

        for (int i = 0; i < n; i++) {
            lastIndex[charArray[i] - 'a'] = i;
        }

        StringBuilder sb = new StringBuilder();
        Deque<Character> stack = new ArrayDeque<>();

        for (int i = 0; i < n; i++) {
            char currentChar = charArray[i];
            if (visited[currentChar - 'a']) {
                continue;
            }

            while (!stack.isEmpty() && stack.peek() > currentChar && lastIndex[stack.peek() - 'a'] > i) {
                visited[stack.pop() - 'a'] = false;
            }

            stack.push(currentChar);
            visited[currentChar - 'a'] = true;
        }

        while (!stack.isEmpty()) {
            sb.append(stack.pop());
        }

        return sb.reverse().toString();         
    }
}
