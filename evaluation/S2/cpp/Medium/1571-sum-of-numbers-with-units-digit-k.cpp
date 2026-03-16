// Source: https://leetcode.com/problems/sum-of-numbers-with-units-digit-k/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers num and k, consider a set of positive integers with the following properties:
//
//
// 	The units digit of each integer is k.
// 	The sum of the integers is num.
//
//
// Return the minimum possible size of such a set, or -1 if no such set exists.
//
// Note:
//
//
// 	The set can contain multiple instances of the same integer, and the sum of an empty set is considered 0.
// 	The units digit of a number is the rightmost digit of the number.
//
// Example:
// Input: num = 58, k = 9
// Output: 2
// Explanation:
// One valid set is [9,49], as the sum is 58 and each integer has a units digit of 9.
// Another valid set is [19,39].
// It can be shown that 2 is the minimum possible size of a valid set.
//
// Constraints:
// 0 <= num <= 3000
// 	0 <= k <= 9
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Linear Diophantine Equation (number, enumeration)
//   • When to use: Use when you need to find all integer solutions (x, y) for a linear equation of the form ax + by = c, or to determine if such solutions exist. It is also applicable for enumerating solutions within specified bounds.
//   • Idea: This method finds all integer solutions (x, y) to the linear equation ax + by = c. It utilizes the Extended Euclidean Algorithm to find a particular solution, then generates the general solution set using properties of the greatest common divisor in O(log(min(a,b))) time.
//   • Invariants: The equation a * x + b * y = c holds true for any generated integer solution (x, y).; For integer solutions to exist, c must be perfectly divisible by gcd(a, b).
//   • Tips: Always check if c is divisible by gcd(a, b); if not, no integer solutions exist.; Use the Extended Euclidean Algorithm to find a particular solution (x0, y0) for ax + by = gcd(a, b).
//   • Pitfalls: Forgetting to verify that c is a multiple of gcd(a, b) before proceeding.; Incorrectly scaling the particular solution obtained from the Extended Euclidean Algorithm.
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minimumNumbers(int num, int k) {
        if (num == 0) return 0; // The sum of an empty set is considered 0, so we can return 0 if num is 0.

        for (int i = 1; i <= 10; ++i) {
            if ((i * k) % 10 == num % 10 && i * k <= num) {
                return i; // Return the minimum size of the set that satisfies the conditions.
            }
        }

        return -1; // Return -1 if no such set exists.          
    }
};
