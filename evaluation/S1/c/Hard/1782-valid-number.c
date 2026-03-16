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
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool isNumber(char* s) {
    enum State {
        START,
        SIGN,
        INTEGER,
        POINT_WITHOUT_INT,
        POINT_WITH_INT,
        FRACTION,
        EXPONENT,
        EXP_SIGN,
        EXP_INTEGER,
        END
    };

    enum CharType {
        CHAR_NUMBER,
        CHAR_SIGN,
        CHAR_POINT,
        CHAR_EXPONENT,
        CHAR_SPACE,
        CHAR_INVALID
    };

    enum State transitionTable[10][6] = {
        // CHAR_NUMBER, CHAR_SIGN, CHAR_POINT, CHAR_EXPONENT, CHAR_SPACE, CHAR_INVALID
        {INTEGER, SIGN, POINT_WITHOUT_INT, END, START, END},          // START
        {INTEGER, END, END, END, END, END},                           // SIGN
        {INTEGER, END, POINT_WITH_INT, EXPONENT, END, END},          // INTEGER
        {FRACTION, END, END, END, END, END},                          // POINT_WITHOUT_INT
        {FRACTION, END, END, EXPONENT, END, END},                    // POINT_WITH_INT
        {FRACTION, END, END, EXPONENT, END, END},                    // FRACTION
        {EXP_INTEGER, EXP_SIGN, END, END, END, END},                 // EXPONENT
        {EXP_INTEGER, END, END, END, END, END},                      // EXP_SIGN
        {EXP_INTEGER, END, END, END, END, END},                      // EXP_INTEGER
        {END, END, END, END, END, END}                               // END
    };

    enum State state = START;
    char* p = s;

    while (*p != '\0') {
        enum CharType charType;
        if (*p >= '0' && *p <= '9') {
            charType = CHAR_NUMBER;
        } else if (*p == '+' || *p == '-') {
            charType = CHAR_SIGN;
        } else if (*p == '.') {
            charType = CHAR_POINT;
        } else if (*p == 'e' || *p == 'E') {
            charType = CHAR_EXPONENT;
        } else if (*p == ' ') {
            charType = CHAR_SPACE;
        } else {
            charType = CHAR_INVALID;
        }

        state = transitionTable[state][charType];
        if (state == END) {
            return false;
        }
        p++;
    }

    return state == INTEGER || state == POINT_WITH_INT || state == FRACTION || state == EXP_INTEGER || state == END;
}
