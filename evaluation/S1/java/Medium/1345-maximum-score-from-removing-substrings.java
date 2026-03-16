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
// Helpful references (internal KB):
// - Minimum stack / Minimum queue (stack, simulation)
//   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
//   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
//   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
//   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
//   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
//   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
//   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
//   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
//   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private int removeSubstrings(String s, String target, int score) {
        Deque<Character> stack = new ArrayDeque<>();
        int totalScore = 0;
        for (char c : s.toCharArray()) {
            stack.push(c);
            if (stack.size() >= 2) {
                char second = stack.pop();
                char first = stack.pop();
                if (first == target.charAt(0) && second == target.charAt(1)) {
                    totalScore += score;
                } else {
                    stack.push(first);
                    stack.push(second);
                }
            }
        }
        return totalScore;
    }
    private String removeSubstringsAndReturnString(String s, String target) {
        Deque<Character> stack = new ArrayDeque<>();
        for (char c : s.toCharArray()) {
            stack.push(c);
            if (stack.size() >= 2) {
                char second = stack.pop();
                char first = stack.pop();
                if (first == target.charAt(0) && second == target.charAt(1)) {
                    // Do nothing, effectively removing the substring
                } else {
                    stack.push(first);
                    stack.push(second);
                }
            }
        }
        StringBuilder sb = new StringBuilder();
        while (!stack.isEmpty()) {
            sb.append(stack.removeLast());
        }
        return sb.toString();
    }
    public int maximumGain(String s, int x, int y) {
        String first = x >= y ? "ab" : "ba";
        String second = x >= y ? "ba" : "ab";
        int firstScore = Math.max(x, y);
        int secondScore = Math.min(x, y);

        int totalScore = 0;
        totalScore += removeSubstrings(s, first, firstScore);
        s = removeSubstringsAndReturnString(s, first);
        totalScore += removeSubstrings(s, second, secondScore);

        return totalScore;          
    }
}
