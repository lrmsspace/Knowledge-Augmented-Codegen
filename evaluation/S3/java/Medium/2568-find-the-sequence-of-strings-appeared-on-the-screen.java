// Source: https://leetcode.com/problems/find-the-sequence-of-strings-appeared-on-the-screen/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string target.
//
// Alice is going to type target on her computer using a special keyboard that has only two keys:
//
//
// 	Key 1 appends the character "a" to the string on the screen.
// 	Key 2 changes the last character of the string on the screen to its next character in the English alphabet. For example, "c" changes to "d" and "z" changes to "a".
//
//
// Note that initially there is an empty string "" on the screen, so she can only press key 1.
//
// Return a list of all strings that appear on the screen as Alice types target, in the order they appear, using the minimum key presses.
//
// Example:
// Input: target = "abc"
//
// Output: ["a","aa","ab","aba","abb","abc"]
//
// Explanation:
//
// The sequence of key presses done by Alice are:
//
//
// 	Press key 1, and the string on the screen becomes "a".
// 	Press key 1, and the string on the screen becomes "aa".
// 	Press key 2, and the string on the screen becomes "ab".
// 	Press key 1, and the string on the screen becomes "aba".
// 	Press key 2, and the string on the screen becomes "abb".
// 	Press key 2, and the string on the screen becomes "abc".
//
// Constraints:
// 1 <= target.length <= 400
// 	target consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
//   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
//   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
//   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
//   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
// - Suffix Automaton (string, simulation)
//   • When to use: Use when needing to efficiently process all substrings or suffixes of a given string, especially for counting distinct substrings, finding occurrences, or other complex string pattern problems. It provides linear time solutions for many tasks.
//   • Idea: A suffix automaton is a directed acyclic graph that compactly represents all distinct substrings of a given string. It enables solving a wide range of string-related problems in linear time, typically O(N) or O(N log A) where N is string length and A is alphabet size.
//   • Invariants: Every path from the initial state corresponds to a distinct substring of the original string.; Each state in the automaton represents a set of substrings that share the same end positions.
//   • Tips: Understand the two types of links: suffix links (parent) and transition links (children).; Construction is typically incremental, adding characters one by one.
//   • Pitfalls: Implementation complexity is high; careful handling of state creation and link updates is crucial.; Off-by-one errors in length calculations or suffix link assignments are common.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use to efficiently represent all suffixes of a string in a compressed form, ideal for various string problems like pattern matching or counting distinct substrings.
//   • Idea: A suffix automaton is a minimal Deterministic Finite Automaton (DFA) that accepts all suffixes of a given string, offering O(N) time construction and O(N) memory complexity.
//   • Invariants: Every state in the automaton represents a set of substrings of the original string.; Each state's longest path from the initial state corresponds to its longest string.
//   • Tips: Understand the definition of states and transitions, and their relationship to substrings.; Leverage its linear time and space complexity for efficient string processing on large inputs.
//   • Pitfalls: The construction algorithm can be complex and challenging to implement correctly.; Debugging state transitions, suffix links, and their properties requires careful attention.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<String> stringSequence(String target) {
        List<String> result = new ArrayList<>();
        StringBuilder current = new StringBuilder();

        for (char c : target.toCharArray()) {
            while (current.length() < target.length() && (current.length() == 0 || current.charAt(current.length() - 1) != c)) {
                current.append('a');
                result.add(current.toString());
            }
            if (current.charAt(current.length() - 1) == c) {
                continue; // Already correct, no need to change
            }
            // Change the last character to the next character until it matches c
            while (current.charAt(current.length() - 1) != c) {
                char lastChar = current.charAt(current.length() - 1);
                char nextChar = (char) ((lastChar - 'a' + 1) % 26 + 'a');
                current.setCharAt(current.length() - 1, nextChar);
                result.add(current.toString());
            }
        }

        return result;          
    }
}
