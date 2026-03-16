// Source: https://leetcode.com/problems/sentence-similarity-iii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings sentence1 and sentence2, each representing a sentence composed of words. A sentence is a list of words that are separated by a single space with no leading or trailing spaces. Each word consists of only uppercase and lowercase English characters.
//
// Two sentences s1 and s2 are considered similar if it is possible to insert an arbitrary sentence (possibly empty) inside one of these sentences such that the two sentences become equal. Note that the inserted sentence must be separated from existing words by spaces.
//
// For example,
//
//
// 	s1 = "Hello Jane" and s2 = "Hello my name is Jane" can be made equal by inserting "my name is" between "Hello" and "Jane" in s1.
// 	s1 = "Frog cool" and s2 = "Frogs are cool" are not similar, since although there is a sentence "s are" inserted into s1, it is not separated from "Frog" by a space.
//
//
// Given two sentences sentence1 and sentence2, return true if sentence1 and sentence2 are similar. Otherwise, return false.
//
// Example:
// Input: sentence1 = "My name is Haley", sentence2 = "My Haley"
//
// Output: true
//
// Explanation:
//
// sentence2 can be turned to sentence1 by inserting "name is" between "My" and "Haley".
//
// Constraints:
// 1 <= sentence1.length, sentence2.length <= 100
// 	sentence1 and sentence2 consist of lowercase and uppercase English letters and spaces.
// 	The words in sentence1 and sentence2 are separated by a single space.
//
// Helpful references (internal KB):
// - Expression parsing (stack, simulation)
//   • When to use: This algorithm is used to evaluate expressions given in Reverse Polish Notation (postfix notation) to compute their final numerical value.
//   • Idea: This algorithm evaluates an expression in Reverse Polish Notation by processing elements sequentially. Numbers are pushed onto a stack, and operators pop two operands, compute, and push the result.
//   • Invariants: The stack always contains only numbers (operands or intermediate results).; For a valid RPN expression, the stack will have at least two elements when an operator is processed.
//   • Tips: Process the RPN expression from left to right, token by token.; Push numerical operands directly onto the stack.
//   • Pitfalls: Attempting to pop from an empty stack when an operator is encountered, indicating an invalid RPN expression.; Incorrect order of operands for non-commutative operations like subtraction or division.
// - Expression parsing (stack, simulation)
//   • When to use: Use this algorithm to evaluate an arithmetic expression given in infix notation, respecting operator precedence and parentheses. It is suitable for expressions with binary, left-associative operators.
//   • Idea: This algorithm evaluates an infix arithmetic expression using two stacks: one for operands and one for operators. It processes the expression from left to right, applying operator precedence and associativity rules to achieve an O(N) time complexity.
//   • Invariants: The operand stack always contains valid numerical values or intermediate results.; The operator stack maintains operators such that operators with higher or equal precedence are processed before lower precedence ones.
//   • Tips: Clearly define operator precedence and associativity rules for all operators.; Use a separate stack for operands (numbers) and operators (including parentheses).
//   • Pitfalls: Misinterpreting operator precedence or associativity rules can lead to incorrect results.; Failure to handle mismatched or unbalanced parentheses can cause runtime errors.
// - Expression parsing (stack, simulation)
//   • When to use: When evaluating or converting arithmetic or logical expressions involving various operators, including unary and binary, and handling different associativities. It's useful for implementing calculators or compilers.
//   • Idea: This technique involves using stacks to parse and evaluate expressions, correctly handling operator precedence and associativity, including unary and right-associative operators. It typically processes expressions in O(N) time, where N is the expression length.
//   • Invariants: The operator stack always maintains operators in increasing order of precedence from bottom to top (excluding parentheses).; When processing an operand, it is immediately pushed onto the operand stack.
//   • Tips: Distinguish unary from binary operators based on context (e.g., preceding token).; Assign higher precedence to unary operators than most binary ones.
//   • Pitfalls: Incorrectly identifying unary vs. binary operators based on context.; Failing to correctly implement operator precedence rules.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool areSentencesSimilar(string sentence1, string sentence2) {
        vector<string> s1, s2;
        stringstream ss1(sentence1), ss2(sentence2);
        string word;

        while (ss1 >> word) {
            s1.push_back(word);
        }
        while (ss2 >> word) {
            s2.push_back(word);
        }

        int i = 0, j = 0;
        while (i < s1.size() && j < s2.size() && s1[i] == s2[j]) {
            i++;
            j++;
        }

        int k = 0, l = 0;
        while (k < s1.size() && l < s2.size() && s1[s1.size() - 1 - k] == s2[s2.size() - 1 - l]) {
            k++;
            l++;
        }

        return i + k >= min(s1.size(), s2.size());          
    }
};
