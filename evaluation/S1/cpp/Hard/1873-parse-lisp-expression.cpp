// Source: https://leetcode.com/problems/parse-lisp-expression/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string expression representing a Lisp-like expression to return the integer value of.
//
// The syntax for these expressions is given as follows.
//
//
// 	An expression is either an integer, let expression, add expression, mult expression, or an assigned variable. Expressions always evaluate to a single integer.
// 	(An integer could be positive or negative.)
// 	A let expression takes the form "(let v1 e1 v2 e2 ... vn en expr)", where let is always the string "let", then there are one or more pairs of alternating variables and expressions, meaning that the first variable v1 is assigned the value of the expression e1, the second variable v2 is assigned the value of the expression e2, and so on sequentially; and then the value of this let expression is the value of the expression expr.
// 	An add expression takes the form "(add e1 e2)" where add is always the string "add", there are always two expressions e1, e2 and the result is the addition of the evaluation of e1 and the evaluation of e2.
// 	A mult expression takes the form "(mult e1 e2)" where mult is always the string "mult", there are always two expressions e1, e2 and the result is the multiplication of the evaluation of e1 and the evaluation of e2.
// 	For this question, we will use a smaller subset of variable names. A variable starts with a lowercase letter, then zero or more lowercase letters or digits. Additionally, for your convenience, the names "add", "let", and "mult" are protected and will never be used as variable names.
// 	Finally, there is the concept of scope. When an expression of a variable name is evaluated, within the context of that evaluation, the innermost scope (in terms of parentheses) is checked first for the value of that variable, and then outer scopes are checked sequentially. It is guaranteed that every expression is legal. Please see the examples for more details on the scope.
//
// Example:
// Input: expression = "(let x 2 (mult x (let x 3 y 4 (add x y))))"
// Output: 14
// Explanation: In the expression (add x y), when checking for the value of the variable x,
// we check from the innermost scope to the outermost in the context of the variable we are trying to evaluate.
// Since x = 3 is found first, the value of x is 3.
//
// Constraints:
// 1 <= expression.length <= 2000
// 	There are no leading or trailing spaces in expression.
// 	All tokens are separated by a single space in expression.
// 	The answer and all intermediate calculations of that answer are guaranteed to fit in a 32-bit integer.
// 	The expression is guaranteed to be legal and evaluate to an integer.
//
// Helpful references (internal KB):
// - Expression parsing (stack, simulation)
//   • When to use: Use this algorithm to evaluate an arithmetic expression given in infix notation, respecting operator precedence and parentheses. It is suitable for expressions with binary, left-associative operators.
//   • Idea: This algorithm evaluates an infix arithmetic expression using two stacks: one for operands and one for operators. It processes the expression from left to right, applying operator precedence and associativity rules to achieve an O(N) time complexity.
//   • Invariants: The operand stack always contains valid numerical values or intermediate results.; The operator stack maintains operators such that operators with higher or equal precedence are processed before lower precedence ones.
//   • Tips: Clearly define operator precedence and associativity rules for all operators.; Use a separate stack for operands (numbers) and operators (including parentheses).
//   • Pitfalls: Misinterpreting operator precedence or associativity rules can lead to incorrect results.; Failure to handle mismatched or unbalanced parentheses can cause runtime errors.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Search for connected components in a graph (stack, graph, dfs, recursion)
//   • When to use: Use when the goal is to identify distinct groups of interconnected nodes within a graph, or to find all nodes reachable from a specific starting point.
//   • Idea: Depth-First Search (DFS) explores a graph by traversing as far as possible along each branch before backtracking. It efficiently finds connected components by visiting all reachable nodes from an unvisited starting point, typically with O(V+E) time complexity.
//   • Invariants: All nodes in the current DFS path from the start node to the current node are on the recursion stack.; Any node marked as visited will not be re-processed by the current DFS call.
//   • Tips: Maintain a 'visited' status for each node to prevent cycles and redundant work.; Iterate through all nodes and start DFS if a node is unvisited to find all components.
//   • Pitfalls: Excessive recursion depth can lead to stack overflow errors for large graphs.; Forgetting to mark nodes as visited results in infinite loops in cyclic graphs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int evaluate(string expression) {
        unordered_map<string, vector<int>> scope;

        function<int(int&, int)> eval = [&](int& pos, int depth) -> int {
            if (expression[pos] == '(') {
                pos++; // skip '('
                string token = parseToken(pos);
                int result;

                if (token == "let") {
                    vector<string> vars;
                    while (true) {
                        if (expression[pos] == '(' || isdigit(expression[pos]) || expression[pos] == '-' ) {
                            result = eval(pos, depth + 1);
                            break;
                        }
                        string var = parseToken(pos);
                        vars.push_back(var);
                        int val = eval(pos, depth + 1);
                        scope[var].push_back(val);
                    }
                    for (const string& var : vars) {
                        scope[var].pop_back();
                    }
                } else if (token == "add") {
                    int val1 = eval(pos, depth + 1);
                    int val2 = eval(pos, depth + 1);
                    result = val1 + val2;
                } else if (token == "mult") {
                    int val1 = eval(pos, depth + 1);
                    int val2 = eval(pos, depth + 1);
                    result = val1 * val2;
                }

                pos++; // skip ')'
                return result;
            } else {
                string token = parseToken(pos);
                if (isdigit(token[0]) || token[0] == '-') {
                    return stoi(token);
                } else {
                    return scope[token].back();
                }
            }
        };

        function<string(int&)> parseToken = [&](int& pos) -> string {
            while (pos < expression.size() && expression[pos] == ' ') pos++;
            int start = pos;
            if (expression[pos] == '(' || expression[pos] == ')') {
                return string(1, expression[pos++]);
            }
            while (pos < expression.size() && expression[pos] != ' ' && expression[pos] != '(' && expression[pos] != ')') {
                pos++;
            }
            return expression.substr(start, pos - start);
        };

        int pos = 0;
        return eval(pos, 0);
    }
};
