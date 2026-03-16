// Source: https://leetcode.com/problems/minimum-cost-to-change-the-final-value-of-expression/   |   Difficulty: Hard
//
// Problem Description:
// You are given a valid boolean expression as a string expression consisting of the characters '1','0','&' (bitwise AND operator),'|' (bitwise OR operator),'(', and ')'.
//
//
// 	For example, "()1|1" and "(1)&()" are not valid while "1", "(((1))|(0))", and "1|(0&(1))" are valid expressions.
//
//
// Return the minimum cost to change the final value of the expression.
//
//
// 	For example, if expression = "1|1|(0&0)&1", its value is 1|1|(0&0)&1 = 1|1|0&1 = 1|0&1 = 1&1 = 1. We want to apply operations so that the new expression evaluates to 0.
//
//
// The cost of changing the final value of an expression is the number of operations performed on the expression. The types of operations are described as follows:
//
//
// 	Turn a '1' into a '0'.
// 	Turn a '0' into a '1'.
// 	Turn a '&' into a '|'.
// 	Turn a '|' into a '&'.
//
//
// Note: '&' does not take precedence over '|' in the order of calculation. Evaluate parentheses first, then in left-to-right order.
//
// Example:
// Input: expression = "1&(0|1)"
// Output: 1
// Explanation: We can turn "1&(0|1)" into "1&(0&1)" by changing the '|' to a '&' using 1 operation.
// The new expression evaluates to 0.
//
// Constraints:
// 1 <= expression.length <= 105
// 	expression only contains '1','0','&','|','(', and ')'
// 	All parentheses are properly matched.
// 	There will be no empty parentheses (i.e: "()" is not a substring of expression).
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Expression parsing (stack, simulation)
//   • When to use: Use this algorithm to evaluate an arithmetic expression given in infix notation, respecting operator precedence and parentheses. It is suitable for expressions with binary, left-associative operators.
//   • Idea: This algorithm evaluates an infix arithmetic expression using two stacks: one for operands and one for operators. It processes the expression from left to right, applying operator precedence and associativity rules to achieve an O(N) time complexity.
//   • Invariants: The operand stack always contains valid numerical values or intermediate results.; The operator stack maintains operators such that operators with higher or equal precedence are processed before lower precedence ones.
//   • Tips: Clearly define operator precedence and associativity rules for all operators.; Use a separate stack for operands (numbers) and operators (including parentheses).
//   • Pitfalls: Misinterpreting operator precedence or associativity rules can lead to incorrect results.; Failure to handle mismatched or unbalanced parentheses can cause runtime errors.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

// dp[i][j][v] = minimum cost to make expression[i..j] evaluate to value v (0 or 1)
int dp[105][105][2];

// Parse and compute the minimum cost
// Returns current value in *val
int parse_expr(const char* expr, int* pos);

int parse_value(const char* expr, int* pos) {
    if (expr[*pos] == '(') {
        (*pos)++;  // skip '('
        int result = parse_expr(expr, pos);
        (*pos)++;  // skip ')'
        return result;
    } else {
        return expr[(*pos)++] - '0';
    }
}

int parse_expr(const char* expr, int* pos) {
    int result = parse_value(expr, pos);
    
    while (expr[*pos] != '\0' && expr[*pos] != ')') {
        char op = expr[(*pos)++];
        int right = parse_value(expr, pos);
        
        if (op == '&') {
            result = result & right;
        } else {
            result = result | right;
        }
    }
    
    return result;
}

void compute_dp(const char* expr, int start, int end) {
    if (start > end) return;
    
    // Base case: single element
    if (start == end) {
        if (expr[start] == '0') {
            dp[start][end][0] = 0;
            dp[start][end][1] = 1;
        } else if (expr[start] == '1') {
            dp[start][end][0] = 1;
            dp[start][end][1] = 0;
        }
        return;
    }
    
    // Remove outer parentheses if they match
    if (expr[start] == '(' && expr[end] == ')') {
        int cnt = 0, valid = 1;
        for (int k = start; k <= end; k++) {
            if (expr[k] == '(') cnt++;
            else if (expr[k] == ')') cnt--;
            if (cnt == 0 && k < end) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            compute_dp(expr, start + 1, end - 1);
            dp[start][end][0] = dp[start+1][end-1][0];
            dp[start][end][1] = dp[start+1][end-1][1];
            return;
        }
    }
    
    // Find the main operator (at depth 0, first from left)
    int cnt = 0, op_pos = -1;
    char main_op = '\0';
    for (int i = start; i <= end; i++) {
        if (expr[i] == '(') cnt++;
        else if (expr[i] == ')') cnt--;
        else if (cnt == 0 && (expr[i] == '&' || expr[i] == '|')) {
            op_pos = i;
            main_op = expr[i];
            break;
        }
    }
    
    if (op_pos == -1) return;  // No operator found
    
    // Recursively compute for left and right
    compute_dp(expr, start, op_pos - 1);
    compute_dp(expr, op_pos + 1, end);
    
    int l0 = dp[start][op_pos-1][0];
    int l1 = dp[start][op_pos-1][1];
    int r0 = dp[op_pos+1][end][0];
    int r1 = dp[op_pos+1][end][1];
    
    if (main_op == '&') {
        // AND operation: to get 0, flip one if needed; to get 1, both must be 1
        // Cost to make 0: min cost among (0,0), (0,1), (1,0)
        int c0_0 = l0 + r0;
        int c0_1 = l0 + r1;
        int c1_0 = l1 + r0;
        dp[start][end][0] = (c0_0 < c0_1) ? c0_0 : c0_1;
        dp[start][end][0] = (dp[start][end][0] < c1_0) ? dp[start][end][0] : c1_0;
        
        // Cost to make 1: both must be 1
        dp[start][end][1] = l1 + r1;
    } else {  // OR operation
        // Cost to make 0: both must be 0
        dp[start][end][0] = l0 + r0;
        
        // Cost to make 1: at least one must be 1
        // Options: (0,1), (1,0), (1,1)
        int c0_1 = l0 + r1;
        int c1_0 = l1 + r0;
        int c1_1 = l1 + r1;
        dp[start][end][1] = (c0_1 < c1_0) ? c0_1 : c1_0;
        dp[start][end][1] = (dp[start][end][1] < c1_1) ? dp[start][end][1] : c1_1;
    }
}

int minOperationsToFlip(char* expression) {
    memset(dp, 0, sizeof(dp));
    
    int len = strlen(expression);
    
    // Compute DP values for all subexpressions
    compute_dp(expression, 0, len - 1);
    
    // Get the current value of the entire expression
    int pos = 0;
    int current_value = parse_expr(expression, &pos);
    
    // Return the cost to flip to the opposite value
    if (current_value == 0) {
        return dp[0][len-1][1];
    } else {
        return dp[0][len-1][0];
    }
}
