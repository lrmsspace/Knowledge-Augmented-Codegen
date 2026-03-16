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
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
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
        visited.insert("0,true");
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
                    string forwardState = to_string(forwardPos) + ",true";
                    if (!visited.count(forwardState)) {
                        visited.insert(forwardState);
                        q.push({forwardPos, true});
                    }
                }

                // Jump backward
                if (canJumpBackward) {
                    int backwardPos = pos - b;
                    if (backwardPos >= 0 && !forbiddenSet.count(backwardPos)) {
                        string backwardState = to_string(backwardPos) + ",false";
                        if (!visited.count(backwardState)) {
                            visited.insert(backwardState);
                            q.push({backwardPos, false});
                        }
                    }
                }
            }
            ++jumps;
        }

        return -1;          
    }
};
