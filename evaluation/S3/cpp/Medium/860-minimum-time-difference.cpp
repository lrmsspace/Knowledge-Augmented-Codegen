// Source: https://leetcode.com/problems/minimum-time-difference/   |   Difficulty: Medium
//
// Problem Description:
// Given a list of 24-hour clock time points in "HH:MM" format, return the minimum minutes difference between any two time-points in the list.
//
// Example:
// Input: timePoints = ["23:59","00:00"]
// Output: 1
//
// Constraints:
// 2 <= timePoints.length <= 2 * 104
// 	timePoints[i] is in the format "HH:MM".
//
// Helpful references (internal KB):
// - Integration by Simpson's formula (number, interval, enumeration, simulation)
//   • When to use: Use when approximating definite integrals of functions that are sufficiently smooth over a given interval. It is effective for achieving good accuracy with a moderate number of subintervals.
//   • Idea: Simpson's formula approximates a definite integral by dividing the integration interval into an even number of subintervals and approximating the function over each pair of subintervals with a parabola. This method offers a higher order of accuracy compared to simpler rules, typically achieving O(N^4) accuracy for N subintervals.
//   • Invariants: The sum accumulates weighted function values for all processed subintervals.; The subinterval width 'h' remains constant across the entire integration range.
//   • Tips: Ensure the total number of subintervals (2n) is always even for the composite rule.; The weights for function evaluations follow a specific 1-4-2-4-...-2-4-1 pattern.
//   • Pitfalls: Incorrectly applying the weighting coefficients, especially at the boundaries or interior points.; Using an odd number of subintervals, which invalidates the parabolic approximation for the composite rule.
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - Burnside's lemma / Pólya enumeration theorem (array, number, enumeration, simulation)
//   • When to use: Use when counting the number of distinct configurations or arrangements of objects under a set of symmetry operations, where configurations are considered identical if one can be transformed into another by a group action.
//   • Idea: Burnside's Lemma and Pólya Enumeration Theorem are combinatorial tools used to count the number of distinct objects under a group of symmetries. Both typically involve iterating through group elements and analyzing permutation cycle structures, often resulting in polynomial time complexity depending on group size and element analysis.
//   • Invariants: The set of group elements considered remains consistent throughout the summation.; Each group element's cycle decomposition is correctly identified.
//   • Tips: Identify the group of symmetry operations acting on the objects.; For each group element, determine its permutation cycle structure.
//   • Pitfalls: Incorrectly identifying the full set of distinct group operations.; Errors in determining the cycle structure of permutations.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        vector<int> minutes;
        for (const auto& time : timePoints) {
            int h = stoi(time.substr(0, 2));
            int m = stoi(time.substr(3, 2));
            minutes.push_back(h * 60 + m);
        }
        sort(minutes.begin(), minutes.end());
        int minDiff = 1440 - (minutes.back() - minutes.front()); // Wrap around case
        for (size_t i = 1; i < minutes.size(); ++i) {
            minDiff = min(minDiff, minutes[i] - minutes[i - 1]);
        }
        return minDiff;         
    }
};
