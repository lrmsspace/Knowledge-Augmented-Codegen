// Source: https://leetcode.com/problems/vowels-game-in-a-string/   |   Difficulty: Medium
//
// Problem Description:
// Alice and Bob are playing a game on a string.
//
// You are given a string s, Alice and Bob will take turns playing the following game where Alice starts first:
//
//
// 	On Alice's turn, she has to remove any non-empty substring from s that contains an odd number of vowels.
// 	On Bob's turn, he has to remove any non-empty substring from s that contains an even number of vowels.
//
//
// The first player who cannot make a move on their turn loses the game. We assume that both Alice and Bob play optimally.
//
// Return true if Alice wins the game, and false otherwise.
//
// The English vowels are: a, e, i, o, and u.
//
// Example:
// Input: s = "leetcoder"
//
// Output: true
//
// Explanation:
// Alice can win the game as follows:
//
//
// 	Alice plays first, she can delete the underlined substring in s = "leetcoder" which contains 3 vowels. The resulting string is s = "der".
// 	Bob plays second, he can delete the underlined substring in s = "der" which contains 0 vowels. The resulting string is s = "er".
// 	Alice plays third, she can delete the whole string s = "er" which contains 1 vowel.
// 	Bob plays fourth, since the string is empty, there is no valid play for Bob. So Alice wins the game.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Suffix Automaton (string, enumeration)
//   • When to use: When you need to efficiently represent all substrings of a given string and perform various string operations like counting distinct substrings or pattern matching in linear time.
//   • Idea: A Suffix Automaton is a minimal finite automaton that accepts all suffixes of a given string. It implicitly represents all substrings and can be constructed in linear time, O(N) where N is the string length.
//   • Invariants: Every path from the initial state spells a substring of the original string.; Each state represents a set of substrings that share the same end positions in the original string.
//   • Tips: Understand the concept of `endpos` sets and how they define states.; The number of states and transitions in a suffix automaton is linear with respect to string length.
//   • Pitfalls: The construction algorithm can be complex and prone to off-by-one errors or incorrect link updates.; Debugging state transitions and suffix links requires careful attention.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool doesAliceWin(string s) {
        int vowels = 0;
        for (char c : s) {
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                vowels++;
            }
        }
        return vowels % 2 == 1;         
    }
};
