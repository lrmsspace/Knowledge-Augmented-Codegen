// Source: https://leetcode.com/problems/24-game/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array cards of length 4. You have four cards, each containing a number in the range [1, 9]. You should arrange the numbers on these cards in a mathematical expression using the operators ['+', '-', '*', '/'] and the parentheses '(' and ')' to get the value 24.
//
// You are restricted with the following rules:
//
//
// 	The division operator '/' represents real division, not integer division.
//
// 	
// 		For example, 4 / (1 - 2 / 3) = 4 / (1 / 3) = 12.
// 	
// 	
// 	Every operation done is between two numbers. In particular, we cannot use '-' as a unary operator.
// 	
// 		For example, if cards = [1, 1, 1, 1], the expression "-1 - 1 - 1 - 1" is not allowed.
// 	
// 	
// 	You cannot concatenate numbers together
// 	
// 		For example, if cards = [1, 2, 1, 2], the expression "12 + 12" is not valid.
// 	
// 	
//
//
// Return true if you can get such expression that evaluates to 24, and false otherwise.
//
// Example:
// Input: cards = [4,1,8,7]
// Output: true
// Explanation: (8-4) * (7-1) = 24
//
// Constraints:
// cards.length == 4
// 	1 <= cards[i] <= 9
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Expression parsing (stack, simulation)
//   • When to use: Use this algorithm to evaluate an arithmetic expression given in infix notation, respecting operator precedence and parentheses. It is suitable for expressions with binary, left-associative operators.
//   • Idea: This algorithm evaluates an infix arithmetic expression using two stacks: one for operands and one for operators. It processes the expression from left to right, applying operator precedence and associativity rules to achieve an O(N) time complexity.
//   • Invariants: The operand stack always contains valid numerical values or intermediate results.; The operator stack maintains operators such that operators with higher or equal precedence are processed before lower precedence ones.
//   • Tips: Clearly define operator precedence and associativity rules for all operators.; Use a separate stack for operands (numbers) and operators (including parentheses).
//   • Pitfalls: Misinterpreting operator precedence or associativity rules can lead to incorrect results.; Failure to handle mismatched or unbalanced parentheses can cause runtime errors.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool judgePoint24(int* cards, int cardsSize) {
    const double TARGET = 24.0;
    const double EPSILON = 1e-6;
    const int N = 4;

    bool backtrack(double* nums, int n) {
        if (n == 1) {
            return fabs(nums[0] - TARGET) < EPSILON;
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    double newNums[4];
                    int idx = 0;
                    for (int k = 0; k < n; ++k) {
                        if (k != i && k != j) {
                            newNums[idx++] = nums[k];
                        }
                    }

                    // Try all operations
                    double a = nums[i], b = nums[j];

                    // Addition
                    newNums[idx] = a + b;
                    if (backtrack(newNums, n - 1)) return true;

                    // Subtraction
                    newNums[idx] = a - b;
                    if (backtrack(newNums, n - 1)) return true;

                    newNums[idx] = b - a;
                    if (backtrack(newNums, n - 1)) return true;

                    // Multiplication
                    newNums[idx] = a * b;
                    if (backtrack(newNums, n - 1)) return true;

                    // Division
                    if (fabs(b) > EPSILON) {
                        newNums[idx] = a / b;
                        if (backtrack(newNums, n - 1)) return true;
                    }
                    if (fabs(a) > EPSILON) {
                        newNums[idx] = b / a;
                        if (backtrack(newNums, n - 1)) return true;
                    }
                }
            }
        }
        return false;
    }

    double nums[4];
    for (int i = 0; i < N; ++i) {
        nums[i] = (double)cards[i];
    }
    return backtrack(nums, N);      
}
