// Source: https://leetcode.com/problems/parsing-a-boolean-expression/   |   Difficulty: Hard
//
// Problem Description:
// A boolean expression is an expression that evaluates to either true or false. It can be in one of the following shapes:
//
//
// 	't' that evaluates to true.
// 	'f' that evaluates to false.
// 	'!(subExpr)' that evaluates to the logical NOT of the inner expression subExpr.
// 	'&(subExpr1, subExpr2, ..., subExprn)' that evaluates to the logical AND of the inner expressions subExpr1, subExpr2, ..., subExprn where n >= 1.
// 	'|(subExpr1, subExpr2, ..., subExprn)' that evaluates to the logical OR of the inner expressions subExpr1, subExpr2, ..., subExprn where n >= 1.
//
//
// Given a string expression that represents a boolean expression, return the evaluation of that expression.
//
// It is guaranteed that the given expression is valid and follows the given rules.
//
// Example:
// Input: expression = "&(|(f))"
// Output: false
// Explanation: 
// First, evaluate |(f) --> f. The expression is now "&(f)".
// Then, evaluate &(f) --> f. The expression is now "f".
// Finally, return false.
//
// Constraints:
// 1 <= expression.length <= 2 * 104
// 	expression[i] is one following characters: '(', ')', '&', '|', '!', 't', 'f', and ','.
//
// Helpful references (internal KB):
// - Expression parsing (stack, simulation)
//   • When to use: Use this algorithm to evaluate an arithmetic expression given in infix notation, respecting operator precedence and parentheses. It is suitable for expressions with binary, left-associative operators.
//   • Idea: This algorithm evaluates an infix arithmetic expression using two stacks: one for operands and one for operators. It processes the expression from left to right, applying operator precedence and associativity rules to achieve an O(N) time complexity.
//   • Invariants: The operand stack always contains valid numerical values or intermediate results.; The operator stack maintains operators such that operators with higher or equal precedence are processed before lower precedence ones.
//   • Tips: Clearly define operator precedence and associativity rules for all operators.; Use a separate stack for operands (numbers) and operators (including parentheses).
//   • Pitfalls: Misinterpreting operator precedence or associativity rules can lead to incorrect results.; Failure to handle mismatched or unbalanced parentheses can cause runtime errors.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
//   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
//   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
//   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
//   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool parseBoolExpr(char* expression) {
    int stack[20000];
    int sp = 0; /* stack pointer */

    for (char *p = expression; *p; ++p) {
        char c = *p;
        if (c == 't') {
            stack[sp++] = 1;
        } else if (c == 'f') {
            stack[sp++] = 0;
        } else if (c == '!') {
            /* do nothing, wait for '(' */
        } else if (c == '&' || c == '|') {
            stack[sp++] = (c == '&') ? 2 : 3; /* use 2 for AND, 3 for OR */
        } else if (c == '(') {
            stack[sp++] = -1; /* marker for '(' */
        } else if (c == ',') {
            /* do nothing, just a separator */
        } else if (c == ')') {
            /* evaluate the expression inside the parentheses */
            int vals[1000];
            int valCount = 0;
            while (sp > 0 && stack[sp - 1] != -1) {
                vals[valCount++] = stack[--sp];
            }
            sp--; /* pop the -1 marker */

            int op = stack[--sp]; /* operator before '(' */
            int result;
            if (op == 1) { /* NOT */
                result = !vals[0];
            } else if (op == 2) { /* AND */
                result = 1;
                for (int i = 0; i < valCount; ++i) {
                    result &= vals[i];
                }
            } else { /* OR */
                result = 0;
                for (int i = 0; i < valCount; ++i) {
                    result |= vals[i];
                }
            }
            stack[sp++] = result;
        }
    }
    return stack[0];        
}
