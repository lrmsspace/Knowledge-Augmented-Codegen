// Source: https://leetcode.com/problems/least-operators-to-express-number/   |   Difficulty: Hard
//
// Problem Description:
// Given a single positive integer x, we will write an expression of the form x (op1) x (op2) x (op3) x ... where each operator op1, op2, etc. is either addition, subtraction, multiplication, or division (+, -, *, or /). For example, with x = 3, we might write 3 * 3 / 3 + 3 - 3 which is a value of 3.
//
// When writing such an expression, we adhere to the following conventions:
//
//
// 	The division operator (/) returns rational numbers.
// 	There are no parentheses placed anywhere.
// 	We use the usual order of operations: multiplication and division happen before addition and subtraction.
// 	It is not allowed to use the unary negation operator (-). For example, "x - x" is a valid expression as it only uses subtraction, but "-x + x" is not because it uses negation.
//
//
// We would like to write an expression with the least number of operators such that the expression equals the given target. Return the least number of operators used.
//
// Example:
// Input: x = 3, target = 19
// Output: 5
// Explanation: 3 * 3 + 3 * 3 + 3 / 3.
// The expression contains 5 operations.
//
// Constraints:
// 2 <= x <= 100
// 	1 <= target <= 2 * 108
//
// Helpful references (internal KB):
// - The Stern-Brocot tree and Farey sequences (number, tree, binary-search, simulation)
//   • When to use: Use this when representing positive rational numbers as unique paths in a binary tree or when efficiently approximating irrational numbers. It's ideal for finding a fraction's path or its position within ordered sequences.
//   • Idea: The Stern-Brocot tree uniquely maps every positive rational number to a binary path, constructed by repeatedly taking mediants. This allows for efficient search and representation of fractions with O(log(p+q)) time complexity.
//   • Invariants: The target fraction p/q always lies strictly between the current left boundary pL/qL and right boundary pR/qR.; The current left and right boundary fractions (pL/qL, pR/qR) are always adjacent terms in some Farey sequence.
//   • Tips: Initialize search boundaries with 0/1 and 1/0 (or 1/1 for positive fractions).; Calculate the mediant (pL+pR)/(qL+qR) to determine the next candidate fraction.
//   • Pitfalls: Naive O(p+q) search without run-length encoding can be too slow for large fractions.; Incorrectly handling initial boundary conditions (e.g., 0/1, 1/0, 1/1).
// - The Stern-Brocot tree and Farey sequences (number, tree, binary-search, simulation)
//   • When to use: Use when you need to represent all positive irreducible fractions in a structured tree or efficiently search for a specific fraction. It's also useful for generating Farey sequences or understanding rational number properties.
//   • Idea: The Stern-Brocot tree is an infinite binary tree containing every positive irreducible fraction exactly once, ordered by value. Searching for a fraction or generating parts of the tree typically involves a logarithmic number of steps relative to the sum of the numerator and denominator, making it efficient for O(log(x+y)) operations.
//   • Invariants: For any node m/n, all fractions in its left subtree are strictly less than m/n.; For any node m/n, all fractions in its right subtree are strictly greater than m/n.
//   • Tips: The mediant of a/b and c/d is (a+c)/(b+d), which is always irreducible if a/b and c/d are.; All fractions in the Stern-Brocot tree are inherently irreducible.
//   • Pitfalls: Integer overflow when calculating mediants if numerators or denominators are very large.; Incorrectly handling the initial 'infinite' fractions (0/1 and 1/0) as boundary conditions.
// - Arbitrary-Precision Arithmetic (number, gcd)
//   • When to use: When standard integer types cannot hold the magnitude of numbers required for calculations, or when exact results for very large numbers are necessary.
//   • Idea: A technique to represent and operate on integers of arbitrary size, exceeding built-in data type limits, often by storing numbers as sequences of digits or in modular form. Operations are implemented manually, typically with complexity proportional to the number of digits.
//   • Invariants: The stored representation accurately reflects the numerical value.; Each digit or modular component is within its valid range for the chosen base/modulus.
//   • Tips: Choose a suitable base for digit representation (e.g., powers of 10 or 2^k) to balance memory and computation.; Implement basic arithmetic operations (add, subtract, multiply, divide) carefully, handling carries/borrows.
//   • Pitfalls: Inefficient implementation of basic operations can lead to Time Limit Exceeded for large inputs.; Off-by-one errors or incorrect carry/borrow handling are common during manual arithmetic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int leastOpsExpressTarget(int x, int target) {
        if (target == 0) return 0;  
        if (target == 1) return 2;  
        int n = 0;
        long long power = 1;
        while (power < target) {
            power *= x;
            n++;
        }
        if (power == target) return n - 1;
        int cost = n;
        long long remainder = power - target;
        if (remainder < target) {
            cost += leastOpsExpressTarget(x, remainder);
        } else {
            cost += leastOpsExpressTarget(x, target);
        }   
        return cost;
    }
};
