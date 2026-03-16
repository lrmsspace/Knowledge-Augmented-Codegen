// Source: https://leetcode.com/problems/day-of-the-year/   |   Difficulty: Easy
//
// Problem Description:
// Given a string date representing a Gregorian calendar date formatted as YYYY-MM-DD, return the day number of the year.
//
// Example:
// Input: date = "2019-01-09"
// Output: 9
// Explanation: Given date is the 9th day of the year in 2019.
//
// Constraints:
// date.length == 10
// 	date[4] == date[7] == '-', and all other date[i]'s are digits
// 	date represents a calendar date between Jan 1st, 1900 and Dec 31st, 2019.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - String Sorts (array, string, number, radix-sort, recursion, counting-sort)
//   • When to use: Use when sorting a large collection of strings or integers with a limited range of character/digit values. It is particularly efficient for fixed-length keys but can be adapted for variable lengths.
//   • Idea: Radix sort is a non-comparative integer sorting algorithm that sorts data with integer keys by grouping keys by individual digits or characters which share the same significant position and value. It typically achieves O(N*W) time complexity, where N is the number of items and W is the key length.
//   • Invariants: After each pass `d`, the elements are stably sorted according to their digits up to position `d`.; The counting sort subroutine correctly places elements into their sorted positions for the current digit, preserving relative order.
//   • Tips: LSD (Least Significant Digit) is simpler for fixed-length keys.; MSD (Most Significant Digit) is better for variable-length keys or when keys are very long.
//   • Pitfalls: Not efficient for small N or very large W due to constant factors.; Requires extra space for auxiliary array and counting array.
// - Suffix Automaton (string, simulation)
//   • When to use: Use when needing to efficiently process all substrings or suffixes of a given string, especially for counting distinct substrings, finding occurrences, or other complex string pattern problems. It provides linear time solutions for many tasks.
//   • Idea: A suffix automaton is a directed acyclic graph that compactly represents all distinct substrings of a given string. It enables solving a wide range of string-related problems in linear time, typically O(N) or O(N log A) where N is string length and A is alphabet size.
//   • Invariants: Every path from the initial state corresponds to a distinct substring of the original string.; Each state in the automaton represents a set of substrings that share the same end positions.
//   • Tips: Understand the two types of links: suffix links (parent) and transition links (children).; Construction is typically incremental, adding characters one by one.
//   • Pitfalls: Implementation complexity is high; careful handling of state creation and link updates is crucial.; Off-by-one errors in length calculations or suffix link assignments are common.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private boolean isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
    public int dayOfYear(String date) {
        String[] parts = date.split("-");
        int year = Integer.parseInt(parts[0]);
        int month = Integer.parseInt(parts[1]);
        int day = Integer.parseInt(parts[2]);

        int[] daysInMonths = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        // Check for leap year
        if (isLeapYear(year)) {
            daysInMonths[1] = 29;
        }

        int dayOfYear = 0;
        for (int i = 0; i < month - 1; i++) {
            dayOfYear += daysInMonths[i];
        }
        dayOfYear += day;

        return dayOfYear;           
    }
}
