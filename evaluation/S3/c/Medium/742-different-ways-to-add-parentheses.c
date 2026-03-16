// Source: https://leetcode.com/problems/different-ways-to-add-parentheses/   |   Difficulty: Medium
//
// Problem Description:
// Given a string expression of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. You may return the answer in any order.
//
// The test cases are generated such that the output values fit in a 32-bit integer and the number of different results does not exceed 104.
//
// Example:
// Input: expression = "2-1-1"
// Output: [0,2]
// Explanation:
// ((2-1)-1) = 0 
// (2-(1-1)) = 2
//
// Constraints:
// 1 <= expression.length <= 20
// 	expression consists of digits and the operator '+', '-', and '*'.
// 	All the integer values in the input expression are in the range [0, 99].
// 	The integer values in the input expression do not have a leading '-' or '+' denoting the sign.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Digit DP (array, number, digit-dp)
//   • When to use: When counting numbers within a given range [A, B] that satisfy certain digit-based properties, or calculating a sum of such properties.
//   • Idea: Digit DP is a dynamic programming technique used to count numbers or calculate sums of properties for numbers within a given range, based on their digits. It typically involves a recursive function with memoization, processing digits from most significant to least significant, achieving a time complexity of O(log(N) * S * T) where S is sum/state range and T is tight constraint.
//   • Invariants: The `idx` parameter always represents the current digit position being processed, from most significant to least significant.; The `tight` boolean parameter accurately indicates if the current digit choice is restricted by the original number's corresponding digit.
//   • Tips: Handle leading zeros carefully, often with a dedicated boolean state in the DP function.; Use a 'tight' or 'limit' boolean parameter to manage the upper bound constraint imposed by the original number.
//   • Pitfalls: Incorrectly handling the 'tight' constraint can lead to overcounting or undercounting.; Forgetting to reset the memoization table for each new query or test case, especially in competitive programming.
// - Divide and Conquer DP (array, number, divide-and-conquer, dp-2d)
//   • When to use: Use when a problem can be broken into smaller, independent subproblems, and their solutions combine to solve the original. Also applicable when overlapping subproblems benefit from memoization or tabulation.
//   • Idea: This approach solves problems by recursively breaking them into smaller subproblems, solving each once, and storing results in a 2D table to avoid recomputation. It typically achieves a time complexity of O(N*M) or O(N^2) depending on state definition.
//   • Invariants: The DP table entry `dp[i][j]` correctly stores the optimal solution for the subproblem defined by `i` and `j`.; All subproblems `dp[x][y]` where `x < i` or `y < j` (or based on dependency order) are already computed and correct.
//   • Tips: Clearly define the state variables for your 2D DP table.; Establish the base cases before defining recursive relations.
//   • Pitfalls: Incorrectly defining state transitions or recurrence relations.; Missing or incorrect base cases leading to infinite recursion or wrong results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

#include <stdlib.h>
#include <string.h>

typedef struct {
	int* values;
	int size;
	int computed;
} MemoCell;

static char* g_expr;
static int g_len;
static MemoCell* g_memo;

static int is_op(char c) {
	return c == '+' || c == '-' || c == '*';
}

static MemoCell* cell_at(int left, int right) {
	return &g_memo[left * g_len + right];
}

static void push_value(int** arr, int* size, int* cap, int value) {
	int* next;
	if (*size >= *cap) {
		*cap = (*cap == 0) ? 8 : (*cap * 2);
		next = (int*)realloc(*arr, (size_t)(*cap) * sizeof(int));
		if (next == NULL) {
			free(*arr);
			*arr = NULL;
			*size = 0;
			*cap = 0;
			return;
		}
		*arr = next;
	}
	(*arr)[(*size)++] = value;
}

static MemoCell solve_range(int left, int right) {
	int i;
	int has_op;
	int cap;
	int number;
	int li;
	int ri;
	MemoCell* cell;
	MemoCell left_res;
	MemoCell right_res;
	MemoCell out;

	cell = cell_at(left, right);
	if (cell->computed) {
		return *cell;
	}

	out.values = NULL;
	out.size = 0;
	out.computed = 1;
	cap = 0;
	has_op = 0;

	for (i = left; i <= right; ++i) {
		if (is_op(g_expr[i])) {
			has_op = 1;
			left_res = solve_range(left, i - 1);
			right_res = solve_range(i + 1, right);

			for (li = 0; li < left_res.size; ++li) {
				for (ri = 0; ri < right_res.size; ++ri) {
					int v;
					if (g_expr[i] == '+') {
						v = left_res.values[li] + right_res.values[ri];
					} else if (g_expr[i] == '-') {
						v = left_res.values[li] - right_res.values[ri];
					} else {
						v = left_res.values[li] * right_res.values[ri];
					}
					push_value(&out.values, &out.size, &cap, v);
					if (out.values == NULL && out.size == 0) {
						*cell = out;
						return out;
					}
				}
			}
		}
	}

	if (!has_op) {
		number = 0;
		for (i = left; i <= right; ++i) {
			number = number * 10 + (g_expr[i] - '0');
		}
		push_value(&out.values, &out.size, &cap, number);
	}

	*cell = out;
	return out;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* diffWaysToCompute(char* expression, int* returnSize) {
	int i;
	int j;
	int* ans;
	MemoCell root;

	g_expr = expression;
	g_len = (int)strlen(expression);
	*returnSize = 0;

	if (g_len == 0) {
		return NULL;
	}

	g_memo = (MemoCell*)calloc((size_t)g_len * (size_t)g_len, sizeof(MemoCell));
	if (g_memo == NULL) {
		return NULL;
	}

	root = solve_range(0, g_len - 1);
	*returnSize = root.size;

	if (root.size == 0 || root.values == NULL) {
		for (i = 0; i < g_len; ++i) {
			for (j = 0; j < g_len; ++j) {
				free(cell_at(i, j)->values);
			}
		}
		free(g_memo);
		g_memo = NULL;
		return NULL;
	}

	ans = (int*)malloc((size_t)root.size * sizeof(int));
	if (ans != NULL) {
		memcpy(ans, root.values, (size_t)root.size * sizeof(int));
	} else {
		*returnSize = 0;
	}

	for (i = 0; i < g_len; ++i) {
		for (j = 0; j < g_len; ++j) {
			free(cell_at(i, j)->values);
		}
	}
	free(g_memo);
	g_memo = NULL;

	return ans;
}