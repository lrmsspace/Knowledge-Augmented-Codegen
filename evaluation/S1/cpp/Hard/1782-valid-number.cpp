// Source: https://leetcode.com/problems/valid-number/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s, return whether s is a valid number.
//
// For example, all the following are valid numbers: "2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789", while the following are not valid numbers: "abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53".
//
// Formally, a valid number is defined using one of the following definitions:
//
//
// 	An integer number followed by an optional exponent.
// 	A decimal number followed by an optional exponent.
//
//
// An integer number is defined with an optional sign '-' or '+' followed by digits.
//
// A decimal number is defined with an optional sign '-' or '+' followed by one of the following definitions:
//
//
// 	Digits followed by a dot '.'.
// 	Digits followed by a dot '.' followed by digits.
// 	A dot '.' followed by digits.
//
//
// An exponent is defined with an exponent notation 'e' or 'E' followed by an integer number.
//
// The digits are defined as one or more digits.
//
// Example:
// Input: s = "0"
//
// Output: true
//
// Constraints:
// 1 <= s.length <= 20
// 	s consists of only English letters (both uppercase and lowercase), digits (0-9), plus '+', minus '-', or dot '.'.
//
// Helpful references (internal KB):
// - Suffix Automaton (string, simulation)
//   • When to use: Use when needing to efficiently process all substrings or suffixes of a given string, especially for counting distinct substrings, finding occurrences, or other complex string pattern problems. It provides linear time solutions for many tasks.
//   • Idea: A suffix automaton is a directed acyclic graph that compactly represents all distinct substrings of a given string. It enables solving a wide range of string-related problems in linear time, typically O(N) or O(N log A) where N is string length and A is alphabet size.
//   • Invariants: Every path from the initial state corresponds to a distinct substring of the original string.; Each state in the automaton represents a set of substrings that share the same end positions.
//   • Tips: Understand the two types of links: suffix links (parent) and transition links (children).; Construction is typically incremental, adding characters one by one.
//   • Pitfalls: Implementation complexity is high; careful handling of state creation and link updates is crucial.; Off-by-one errors in length calculations or suffix link assignments are common.
// - Primality tests (number, enumeration, simulation)
//   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
//   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
//   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
//   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
//   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool isNumber(string s) {
        enum State {
            START,
            SIGN,
            INTEGER,
            POINT_WITHOUT_INT,
            POINT_WITH_INT,
            FRACTION,
            EXPONENT,
            EXP_SIGN,
            EXP_NUMBER,
            END
        };

        State state = START;
        bool seen_digit = false;
        bool seen_exp_digit = false;

        for (char c : s) {
            switch (state) {
                case START:
                    if (c == ' ') {
                        continue;
                    } else if (c == '+' || c == '-') {
                        state = SIGN;
                    } else if (isdigit(c)) {
                        state = INTEGER;
                        seen_digit = true;
                    } else if (c == '.') {
                        state = POINT_WITHOUT_INT;
                    } else {
                        return false;
                    }
                    break;

                case SIGN:
                    if (isdigit(c)) {
                        state = INTEGER;
                        seen_digit = true;
                    } else if (c == '.') {
                        state = POINT_WITHOUT_INT;
                    } else {
                        return false;
                    }
                    break;

                case INTEGER:
                    if (isdigit(c)) {
                        seen_digit = true;
                    } else if (c == '.') {
                        state = POINT_WITH_INT;
                    } else if (c == 'e' || c == 'E') {
                        if (!seen_digit) return false;
                        state = EXPONENT;
                    } else if (c == ' ') {
                        state = END;
                    } else {
                        return false;
                    }
                    break;

                case POINT_WITHOUT_INT:
                    if (isdigit(c)) {
                        state = FRACTION;
                        seen_digit = true;
                    } else {
                        return false;
                    }
                    break;

                case POINT_WITH_INT:
                    if (isdigit(c)) {
                        state = FRACTION;
                        seen_digit = true;
                    } else if (c == 'e' || c == 'E') {
                        if (!seen_digit) return false;
                        state = EXPONENT;
                    } else if (c == ' ') {
                        state = END;
                    } else {
                        return false;
                    }
                    break;

                case FRACTION:
                    if (isdigit(c)) {
                        seen_digit = true;
                    } else if (c == 'e' || c == 'E') {
                        if (!seen_digit) return false;
                        state = EXPONENT;
                    } else if (c == ' ') {
                        state = END;
                    } else {
                        return false;
                    }
                    break;
                case EXPONENT:
                    if (c == '+' || c == '-') {
                        state = EXP_SIGN;
                    } else if (isdigit(c)) {
                        state = EXP_NUMBER;
                        seen_exp_digit = true;
                    } else {
                        return false;
                    }
                    break;
                case EXP_SIGN:
                    if (isdigit(c)) {
                        state = EXP_NUMBER;
                        seen_exp_digit = true;
                    } else {
                        return false;
                    }
                    break;
                case EXP_NUMBER:
                    if (isdigit(c)) {
                        seen_exp_digit = true;
                    } else if (c == ' ') {
                        state = END;
                    } else {
                        return false;
                    }
                    break;
                case END:
                    if (c != ' ') {
                        return false;
                    }
                    break;
                }
            }
        return (state == INTEGER || state == POINT_WITH_INT || state == FRACTION || state == EXP_NUMBER || state == END) && seen_digit && (state != EXPONENT && state != EXP_SIGN || seen_exp_digit);
    }
};
