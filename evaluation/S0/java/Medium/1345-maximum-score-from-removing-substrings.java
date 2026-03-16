// Source: https://leetcode.com/problems/maximum-score-from-removing-substrings/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and two integers x and y. You can perform two types of operations any number of times.
//
//
// 	Remove substring "ab" and gain x points.
//
// 	
// 		For example, when removing "ab" from "cabxbae" it becomes "cxbae".
// 	
// 	
// 	Remove substring "ba" and gain y points.
// 	
// 		For example, when removing "ba" from "cabxbae" it becomes "cabxe".
// 	
// 	
//
//
// Return the maximum points you can gain after applying the above operations on s.
//
// Example:
// Input: s = "cdbcbbaaabab", x = 4, y = 5
// Output: 19
// Explanation:
// - Remove the "ba" underlined in "cdbcbbaaabab". Now, s = "cdbcbbaaab" and 5 points are added to the score.
// - Remove the "ab" underlined in "cdbcbbaaab". Now, s = "cdbcbbaa" and 4 points are added to the score.
// - Remove the "ba" underlined in "cdbcbbaa". Now, s = "cdbcba" and 5 points are added to the score.
// - Remove the "ba" underlined in "cdbcba". Now, s = "cdbc" and 5 points are added to the score.
// Total score = 5 + 4 + 5 + 5 = 19.
//
// Constraints:
// 1 <= s.length <= 105
// 	1 <= x, y <= 104
// 	s consists of lowercase English letters.
//

class Solution {
    public int maximumGain(String s, int x, int y) {
        int totalScore = 0;
        String firstPair = x >= y ? "ab" : "ba";
        String secondPair = x >= y ? "ba" : "ab";
        int firstScore = Math.max(x, y);
        int secondScore = Math.min(x, y);

        // First pass: remove all instances of the higher scoring pair
        Stack<Character> stack = new Stack<>();
        for (char c : s.toCharArray()) {
            if (!stack.isEmpty() && stack.peek() == firstPair.charAt(0) && c == firstPair.charAt(1)) {
                stack.pop();
                totalScore += firstScore;
            } else {
                stack.push(c);
            }
        }

        // Second pass: remove all instances of the lower scoring pair
        Stack<Character> secondStack = new Stack<>();
        while (!stack.isEmpty()) {
            char c = stack.remove(0); // simulate queue behavior
            if (!secondStack.isEmpty() && secondStack.peek() == secondPair.charAt(0) && c == secondPair.charAt(1)) {
                secondStack.pop();
                totalScore += secondScore;
            } else {
                secondStack.push(c);
            }
        }

        return totalScore;          
    }
}
