// Source: https://leetcode.com/problems/the-number-of-full-rounds-you-have-played/   |   Difficulty: Medium
//
// Problem Description:
// You are participating in an online chess tournament. There is a chess round that starts every 15 minutes. The first round of the day starts at 00:00, and after every 15 minutes, a new round starts.
//
//
// 	For example, the second round starts at 00:15, the fourth round starts at 00:45, and the seventh round starts at 01:30.
//
//
// You are given two strings loginTime and logoutTime where:
//
//
// 	loginTime is the time you will login to the game, and
// 	logoutTime is the time you will logout from the game.
//
//
// If logoutTime is earlier than loginTime, this means you have played from loginTime to midnight and from midnight to logoutTime.
//
// Return the number of full chess rounds you have played in the tournament.
//
// Note: All the given times follow the 24-hour clock. That means the first round of the day starts at 00:00 and the last round of the day starts at 23:45.
//
// Example:
// Input: loginTime = "09:31", logoutTime = "10:14"
// Output: 1
// Explanation: You played one full round from 09:45 to 10:00.
// You did not play the full round from 09:30 to 09:45 because you logged in at 09:31 after it began.
// You did not play the full round from 10:00 to 10:15 because you logged out at 10:14 before it ended.
//
// Constraints:
// loginTime and logoutTime are in the format hh:mm.
// 	00 <= hh <= 23
// 	00 <= mm <= 59
// 	loginTime and logoutTime are not equal.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Suffix Automaton (string, enumeration)
//   • When to use: When you need to efficiently represent all substrings of a given string and perform various string operations like counting distinct substrings or pattern matching in linear time.
//   • Idea: A Suffix Automaton is a minimal finite automaton that accepts all suffixes of a given string. It implicitly represents all substrings and can be constructed in linear time, O(N) where N is the string length.
//   • Invariants: Every path from the initial state spells a substring of the original string.; Each state represents a set of substrings that share the same end positions in the original string.
//   • Tips: Understand the concept of `endpos` sets and how they define states.; The number of states and transitions in a suffix automaton is linear with respect to string length.
//   • Pitfalls: The construction algorithm can be complex and prone to off-by-one errors or incorrect link updates.; Debugging state transitions and suffix links requires careful attention.
// - Finding intersection of two segments (geometry, interval, simulation, interval-scheduling)
//   • When to use: When determining if two line segments in 2D space cross, touch, or overlap, and to find the nature of their intersection (point, segment, or empty).
//   • Idea: This algorithm determines if two line segments intersect and calculates their intersection point or segment. It typically involves checking for orientation changes and handling special cases like collinearity, with an O(1) time complexity.
//   • Invariants: The bounding boxes of the two segments must overlap for an intersection to be possible.; If segments are collinear, their intersection is either empty, a point, or a sub-segment.
//   • Tips: Use a bounding box check first for early exit optimization.; Handle collinear segments as a distinct special case.
//   • Pitfalls: Incorrectly handling parallel or perfectly collinear segments.; Floating point inaccuracies leading to false positives or negatives.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} loginTime
 * @param {string} logoutTime
 * @return {number}
 */
var numberOfRounds = function(loginTime, logoutTime) {
    const toMinutes = (time) => {
        const [hh, mm] = time.split(':').map(Number);
        return hh * 60 + mm;
    };

    let loginMinutes = toMinutes(loginTime);
    let logoutMinutes = toMinutes(logoutTime);

    if (logoutMinutes < loginMinutes) {
        logoutMinutes += 24 * 60; // Adjust for next day
    }

    // Round up login time to next quarter hour
    if (loginMinutes % 15 !== 0) {
        loginMinutes += 15 - (loginMinutes % 15);
    }

    // Round down logout time to previous quarter hour
    logoutMinutes -= logoutMinutes % 15;

    const fullRounds = Math.max(0, (logoutMinutes - loginMinutes) / 15);
    return fullRounds;
};
