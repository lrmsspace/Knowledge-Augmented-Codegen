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
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numberOfRounds(char* loginTime, char* logoutTime) {
    int loginHour = (loginTime[0] - '0') * 10 + (loginTime[1] - '0');
    int loginMinute = (loginTime[3] - '0') * 10 + (loginTime[4] - '0');
    int logoutHour = (logoutTime[0] - '0') * 10 + (logoutTime[1] - '0');
    int logoutMinute = (logoutTime[3] - '0') * 10 + (logoutTime[4] - '0');

    int loginTotalMinutes = loginHour * 60 + loginMinute;
    int logoutTotalMinutes = logoutHour * 60 + logoutMinute;

    if (logoutTotalMinutes < loginTotalMinutes) {
        logoutTotalMinutes += 24 * 60; // Adjust for next day
    }

    // Round up login time to the next quarter hour
    if (loginMinute % 15 != 0) {
        loginTotalMinutes += (15 - (loginMinute % 15));
    }

    // Round down logout time to the previous quarter hour
    if (logoutMinute % 15 != 0) {
        logoutTotalMinutes -= (logoutMinute % 15);
    }

    if (logoutTotalMinutes < loginTotalMinutes) {
        return 0; // No full rounds played
    }

    return (logoutTotalMinutes - loginTotalMinutes) / 15;       
}
