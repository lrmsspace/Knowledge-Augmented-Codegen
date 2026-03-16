// Source: https://leetcode.com/problems/minimum-jumps-to-reach-home/   |   Difficulty: Medium
//
// Problem Description:
// A certain bug's home is on the x-axis at position x. Help them get there from position 0.
//
// The bug jumps according to the following rules:
//
//
// 	It can jump exactly a positions forward (to the right).
// 	It can jump exactly b positions backward (to the left).
// 	It cannot jump backward twice in a row.
// 	It cannot jump to any forbidden positions.
//
//
// The bug may jump forward beyond its home, but it cannot jump to positions numbered with negative integers.
//
// Given an array of integers forbidden, where forbidden[i] means that the bug cannot jump to the position forbidden[i], and integers a, b, and x, return the minimum number of jumps needed for the bug to reach its home. If there is no possible sequence of jumps that lands the bug on position x, return -1.
//
// Example:
// Input: forbidden = [14,4,18,1,15], a = 3, b = 15, x = 9
// Output: 3
// Explanation: 3 jumps forward (0 -> 3 -> 6 -> 9) will get the bug home.
//
// Constraints:
// 1 <= forbidden.length <= 1000
// 	1 <= a, b, forbidden[i] <= 2000
// 	0 <= x <= 2000
// 	All the elements in forbidden are distinct.
// 	Position x is not forbidden.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Extended Euclidean Algorithm (number, gcd, simulation)
//   • When to use: Use this algorithm to find integer coefficients x and y that satisfy Bézout's identity (ax + by = gcd(a,b)). It is also essential for computing modular multiplicative inverses and solving linear Diophantine equations.
//   • Idea: The Extended Euclidean Algorithm computes the greatest common divisor (GCD) of two integers 'a' and 'b', and simultaneously finds integer coefficients 'x' and 'y' such that 'ax + by = gcd(a,b)'. It operates in O(log(min(a,b))) time complexity.
//   • Invariants: x * (initial a) + y * (initial b) = current_a_value; x_1 * (initial a) + y_1 * (initial b) = current_b_value
//   • Tips: Can be implemented using either a recursive or an iterative approach.; The algorithm correctly handles negative integer inputs.
//   • Pitfalls: Incorrectly defining base cases in recursive implementations can lead to errors.; Potential for integer overflow if coefficients x or y become extremely large, though uncommon.
// - Ternary Search (interval, number, binary-search, enumeration)
//   • When to use: Use Ternary Search to find the minimum or maximum of a unimodal or bitonic function over a continuous or discrete interval. It is effective when the function's derivative is hard to compute or unavailable.
//   • Idea: Ternary search is a divide and conquer algorithm that repeatedly narrows down the search space for the extremum of a unimodal function by evaluating two points within the current interval. It reduces the search interval by one-third in each step, achieving O(log N) time complexity.
//   • Invariants: The extremum of the unimodal function lies within the current interval [l, r].; The function value at m1 is compared with m2 to narrow the search.
//   • Tips: Ensure the function is strictly unimodal or bitonic within the search range.; Handle floating-point precision carefully for continuous functions.
//   • Pitfalls: Applying to non-unimodal functions yields incorrect results.; Floating-point errors can lead to incorrect bounds or infinite loops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        unordered_set<int> forbiddenSet(forbidden.begin(), forbidden.end());
        queue<pair<int, bool>> q; // pair of (position, canJumpBackward)
        q.push({0, true});
        unordered_set<string> visited; // to track visited states

        int jumps = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                auto [pos, canJumpBackward] = q.front();
                q.pop();

                if (pos == x) return jumps;

                // Jump forward
                int forwardPos = pos + a;
                if (forwardPos <= 6000 && !forbiddenSet.count(forwardPos)) {
                    string state = to_string(forwardPos) + "_true";
                    if (!visited.count(state)) {
                        visited.insert(state);
                        q.push({forwardPos, true});
                    }
                }

                // Jump backward
                if (canJumpBackward) {
                    int backwardPos = pos - b;
                    if (backwardPos >= 0 && !forbiddenSet.count(backwardPos)) {
                        string state = to_string(backwardPos) + "_false";
                        if (!visited.count(state)) {
                            visited.insert(state);
                            q.push({backwardPos, false});
                        }
                    }
                }
            }
            ++jumps;
        }

        return -1; // If we exhaust the queue without finding x         
    }
};
