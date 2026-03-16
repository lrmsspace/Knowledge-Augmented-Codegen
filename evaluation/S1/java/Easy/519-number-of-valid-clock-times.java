// Source: https://leetcode.com/problems/number-of-valid-clock-times/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string of length 5 called time, representing the current time on a digital clock in the format "hh:mm". The earliest possible time is "00:00" and the latest possible time is "23:59".
//
// In the string time, the digits represented by the ? symbol are unknown, and must be replaced with a digit from 0 to 9.
//
// Return an integer answer, the number of valid clock times that can be created by replacing every ? with a digit from 0 to 9.
//
// Example:
// Input: time = "?5:00"
// Output: 2
// Explanation: We can replace the ? with either a 0 or 1, producing "05:00" or "15:00". Note that we cannot replace it with a 2, since the time "25:00" is invalid. In total, we have two choices.
//
// Constraints:
// time is a valid string of length 5 in the format "hh:mm".
// 	"00" <= hh <= "23"
// 	"00" <= mm <= "59"
// 	Some of the digits might be replaced with '?' and need to be replaced with digits from 0 to 9.
//
// Helpful references (internal KB):
// - Linear Diophantine Equation (number, interval, enumeration)
//   • When to use: Use when you need to find or count all integer solutions (x, y) for a linear Diophantine equation ax + by = c, especially when solutions are constrained within specific intervals for x and y.
//   • Idea: This method finds all integer solutions to a linear Diophantine equation ax + by = c within given x and y intervals. It first finds a particular solution, then uses properties of the general solution to determine the valid range for x, and enumerates solutions in O(N) time where N is the number of solutions.
//   • Invariants: The current (x, y) pair always satisfies the linear Diophantine equation ax + by = c.; The current x value is an integer and satisfies the effective bounds l_x <= x <= r_x.
//   • Tips: Pre-divide coefficients a, b, c by gcd(a, b) to simplify the equation.; Use the Extended Euclidean Algorithm to find an initial particular solution (x0, y0).
//   • Pitfalls: Failing to check if c is divisible by gcd(a, b) before proceeding, leading to incorrect results.; Incorrectly applying the shifting logic for x and y bounds, resulting in an invalid solution range.
// - Factorial modulo 
// p (number, counting, recursion)
//   • When to use: Use when the problem asks for the total count of possibilities or arrangements that can be naturally broken down into smaller, self-similar subproblems. It's effective for exploring decision trees or state spaces.
//   • Idea: Counting determines the number of elements or event occurrences. It uses combinatorial or iterative/recursive methods, often with O(N) or O(log N) complexity.
//   • Invariants: Each recursive call processes a smaller, well-defined subproblem.; The base cases correctly return the count for the simplest scenarios.
//   • Tips: Identify the smallest subproblem and its base cases to stop recursion.; Define the recursive relation clearly, showing how larger problems depend on smaller ones.
//   • Pitfalls: Incorrectly defining base cases can lead to infinite recursion or incorrect results.; Overlapping subproblems without memoization can lead to exponential time complexity.
// - Suffix Automaton (string, enumeration)
//   • When to use: When you need to efficiently represent all substrings of a given string and perform various string operations like counting distinct substrings or pattern matching in linear time.
//   • Idea: A Suffix Automaton is a minimal finite automaton that accepts all suffixes of a given string. It implicitly represents all substrings and can be constructed in linear time, O(N) where N is the string length.
//   • Invariants: Every path from the initial state spells a substring of the original string.; Each state represents a set of substrings that share the same end positions in the original string.
//   • Tips: Understand the concept of `endpos` sets and how they define states.; The number of states and transitions in a suffix automaton is linear with respect to string length.
//   • Pitfalls: The construction algorithm can be complex and prone to off-by-one errors or incorrect link updates.; Debugging state transitions and suffix links requires careful attention.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int countTime(String time) {
        int count = 1;

        // Count possibilities for hours
        if (time.charAt(0) == '?' && time.charAt(1) == '?') {
            count *= 24; // 00 to 23
        } else if (time.charAt(0) == '?') {
            int secondDigit = time.charAt(1) - '0';
            if (secondDigit <= 3) {
                count *= 3; // 0, 1, 2
            } else {
                count *= 2; // 0, 1
            }
        } else if (time.charAt(1) == '?') {
            int firstDigit = time.charAt(0) - '0';
            if (firstDigit == 2) {
                count *= 4; // 0 to 3
            } else {
                count *= 10; // 0 to 9
            }
        }

        // Count possibilities for minutes
        if (time.charAt(3) == '?' && time.charAt(4) == '?') {
            count *= 60; // 00 to 59
        } else if (time.charAt(3) == '?') {
            count *= 6; // 0 to 5
        } else if (time.charAt(4) == '?') {
            count *= 10; // 0 to 9
        }

        return count;           
    }
}
