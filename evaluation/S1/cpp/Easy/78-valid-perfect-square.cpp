// Source: https://leetcode.com/problems/valid-perfect-square/   |   Difficulty: Easy
//
// Problem Description:
// Given a positive integer num, return true if num is a perfect square or false otherwise.
//
// A perfect square is an integer that is the square of an integer. In other words, it is the product of some integer with itself.
//
// You must not use any built-in library function, such as sqrt.
//
// Example:
// Input: num = 16
// Output: true
// Explanation: We return true because 4 * 4 = 16 and 4 is an integer.
//
// Constraints:
// 1 <= num <= 231 - 1
//
// Helpful references (internal KB):
// - Binary search (interval, number, binary-search-answer, recursion)
//   • When to use: Use when optimizing a unimodal function (finding its maximum or minimum) over a continuous interval, where direct differentiation is hard or impossible.
//   • Idea: This algorithm finds the extremum (maximum or minimum) of a unimodal function over a given interval by repeatedly narrowing the search space. It evaluates the function at two internal points to achieve logarithmic convergence.
//   • Invariants: The extremum of the unimodal function f(x) is always within the current interval [l, r].; The function f(x) remains unimodal within the current interval [l, r].
//   • Tips: Use a fixed number of iterations as a stopping criterion instead of an epsilon value for robustness against floating point errors.; For golden section search, reuse one function evaluation from the previous step to minimize expensive computations.
//   • Pitfalls: Applying this algorithm to a non-unimodal function will yield an incorrect result.; Floating point precision issues can lead to incorrect comparisons or infinite loops if `eps` is too small.
// - Integer factorization (number, gcd, mod-exp)
//   • When to use: Use when the goal is to decompose a composite number into its prime factors. It is particularly useful for numbers where factors might be close or exhibit specific number-theoretic properties.
//   • Idea: Integer factorization is the process of finding the prime factors of a composite integer. Various methods like trial division, Fermat's method, and Pollard's p-1 method offer different performance characteristics, with complexities depending on the factor distribution.
//   • Invariants: The product of all found factors and the remaining unfactored part always equals the original number.; For Fermat's method, if a factor is found, then a^2 - n is a perfect square.
//   • Tips: Combine trial division with more advanced methods for initial small prime factors.; Fermat's method is efficient when the prime factors of N are numerically close.
//   • Pitfalls: Fermat's method becomes extremely slow if the factors are numerically far apart.; Pollard's p-1 method may fail if p-1 is not B-powersmooth for the chosen bound B.
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
    bool isPerfectSquare(int num) {
        if (num < 1) return false;
        int left = 1, right = num;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            long long square = (long long)mid * mid;
            if (square == num) {
                return true;
            } else if (square < num) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return false;           
    }
};
