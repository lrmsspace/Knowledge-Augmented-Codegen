// Source: https://leetcode.com/problems/expression-add-operators/   |   Difficulty: Hard
//
// Problem Description:
// Given a string num that contains only digits and an integer target, return all possibilities to insert the binary operators '+', '-', and/or '*' between the digits of num so that the resultant expression evaluates to the target value.
//
// Note that operands in the returned expressions should not contain leading zeros.
//
// Note that a number can contain multiple digits.
//
// Example:
// Input: num = "123", target = 6
// Output: ["1*2*3","1+2+3"]
// Explanation: Both "1*2*3" and "1+2+3" evaluate to 6.
//
// Constraints:
// 1 <= num.length <= 10
// 	num consists of only digits.
// 	-231 <= target <= 231 - 1
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Expression parsing (stack, simulation)
//   • When to use: When evaluating or converting arithmetic or logical expressions involving various operators, including unary and binary, and handling different associativities. It's useful for implementing calculators or compilers.
//   • Idea: This technique involves using stacks to parse and evaluate expressions, correctly handling operator precedence and associativity, including unary and right-associative operators. It typically processes expressions in O(N) time, where N is the expression length.
//   • Invariants: The operator stack always maintains operators in increasing order of precedence from bottom to top (excluding parentheses).; When processing an operand, it is immediately pushed onto the operand stack.
//   • Tips: Distinguish unary from binary operators based on context (e.g., preceding token).; Assign higher precedence to unary operators than most binary ones.
//   • Pitfalls: Incorrectly identifying unary vs. binary operators based on context.; Failing to correctly implement operator precedence rules.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> result;

        function<void(int, long, long, string)> backtrack = [&](int index, long current_value, long last_operand, string expression) {
            if (index == num.size()) {
                if (current_value == target) {
                    result.push_back(expression);
                }
                return;
            }

            for (int i = index; i < num.size(); ++i) {
                if (i != index && num[index] == '0') break; // Skip leading zeros

                string current_str = num.substr(index, i - index + 1);
                long current_num = stol(current_str);

                if (index == 0) {
                    backtrack(i + 1, current_num, current_num, current_str);
                } else {
                    backtrack(i + 1, current_value + current_num, current_num, expression + "+" + current_str);
                    backtrack(i + 1, current_value - current_num, -current_num, expression + "-" + current_str);
                    backtrack(i + 1, current_value - last_operand + last_operand * current_num, last_operand * current_num, expression + "*" + current_str);
                }
            }
        };

        backtrack(0, 0, 0, "");
        return result;
    }
};
