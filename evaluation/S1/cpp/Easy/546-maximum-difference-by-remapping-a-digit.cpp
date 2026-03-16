// Source: https://leetcode.com/problems/maximum-difference-by-remapping-a-digit/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer num. You know that Bob will sneakily remap one of the 10 possible digits (0 to 9) to another digit.
//
// Return the difference between the maximum and minimum values Bob can make by remapping exactly one digit in num.
//
// Notes:
//
//
// 	When Bob remaps a digit d1 to another digit d2, Bob replaces all occurrences of d1 in num with d2.
// 	Bob can remap a digit to itself, in which case num does not change.
// 	Bob can remap different digits for obtaining minimum and maximum values respectively.
// 	The resulting number after remapping can contain leading zeroes.
//
// Example:
// Input: num = 11891
// Output: 99009
// Explanation: 
// To achieve the maximum value, Bob can remap the digit 1 to the digit 9 to yield 99899.
// To achieve the minimum value, Bob can remap the digit 1 to the digit 0, yielding 890.
// The difference between these two numbers is 99009.
//
// Constraints:
// 1 <= num <= 108
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minMaxDifference(int num) {
        string numStr = to_string(num);
        string maxStr = numStr;
        string minStr = numStr;

        // For maximum, replace first non-9 digit with 9
        char toMax = '\0';
        for (char c : numStr) {
            if (c != '9') {
                toMax = c;
                break;
            }
        }
        if (toMax != '\0') {
            for (char &c : maxStr) {
                if (c == toMax) {
                    c = '9';
                }
            }
        }

        // For minimum, replace first non-0 digit with 0 (if it's not the leading digit)
        char toMin = '\0';
        for (char c : numStr) {
            if (c != '0' && c != numStr[0]) {
                toMin = c;
                break;
            }
        }
        if (toMin != '\0') {
            for (char &c : minStr) {
                if (c == toMin) {
                    c = '0';
                }
            }
        }

        int maxVal = stoi(maxStr);
        int minVal = stoi(minStr);
        return maxVal - minVal;         
    }
};
