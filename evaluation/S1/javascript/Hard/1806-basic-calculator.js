// Source: https://leetcode.com/problems/basic-calculator/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s representing a valid expression, implement a basic calculator to evaluate it, and return the result of the evaluation.
//
// Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().
//
// Example:
// Input: s = "1 + 1"
// Output: 2
//
// Constraints:
// 1 <= s.length <= 3 * 105
// 	s consists of digits, '+', '-', '(', ')', and ' '.
// 	s represents a valid expression.
// 	'+' is not used as a unary operation (i.e., "+1" and "+(2 + 3)" is invalid).
// 	'-' could be used as a unary operation (i.e., "-1" and "-(2 + 3)" is valid).
// 	There will be no two consecutive operators in the input.
// 	Every number and running calculation will fit in a signed 32-bit integer.
//
// Helpful references (internal KB):
// - Expression parsing (stack, simulation)
//   • When to use: Use this algorithm to evaluate an arithmetic expression given in infix notation, respecting operator precedence and parentheses. It is suitable for expressions with binary, left-associative operators.
//   • Idea: This algorithm evaluates an infix arithmetic expression using two stacks: one for operands and one for operators. It processes the expression from left to right, applying operator precedence and associativity rules to achieve an O(N) time complexity.
//   • Invariants: The operand stack always contains valid numerical values or intermediate results.; The operator stack maintains operators such that operators with higher or equal precedence are processed before lower precedence ones.
//   • Tips: Clearly define operator precedence and associativity rules for all operators.; Use a separate stack for operands (numbers) and operators (including parentheses).
//   • Pitfalls: Misinterpreting operator precedence or associativity rules can lead to incorrect results.; Failure to handle mismatched or unbalanced parentheses can cause runtime errors.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Minimum stack / Minimum queue (stack, simulation)
//   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
//   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
//   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
//   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
//   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @return {number}
 */
var calculate = function(s) {
    const stack = [];
    let currentNumber = 0;
    let currentResult = 0;
    let currentSign = 1;

    for (let i = 0; i < s.length; i++) {
        const char = s[i];

        if (char >= '0' && char <= '9') {
            currentNumber = currentNumber * 10 + (char - '0');
        } else if (char === '+' || char === '-') {
            currentResult += currentSign * currentNumber;
            currentSign = char === '+' ? 1 : -1;
            currentNumber = 0;
        } else if (char === '(') {
            stack.push(currentResult);
            stack.push(currentSign);
            currentResult = 0;
            currentSign = 1;
        } else if (char === ')') {
            currentResult += currentSign * currentNumber;
            const prevSign = stack.pop();
            const prevResult = stack.pop();
            currentResult = prevResult + prevSign * currentResult;
            currentNumber = 0;
        }
    }

    return currentResult + (currentSign * currentNumber);
};
