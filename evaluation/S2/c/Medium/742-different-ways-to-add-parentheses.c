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
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* diffWaysToCompute(char* expression, int* returnSize) {
    // Base case: if the expression is a number, return it as the only result
    int num = 0;
    int isNumber = 1;
    for (char* p = expression; *p; p++) {
        if (*p >= '0' && *p <= '9') {
            num = num * 10 + (*p - '0');
        } else {
            isNumber = 0;
            break;
        }
    }
    if (isNumber) {
        int* result = (int*)malloc(sizeof(int));
        result[0] = num;
        *returnSize = 1;
        return result;
    }

    // Recursive case: split the expression by operators
    int* results = NULL;
    int count = 0;

    for (char* p = expression; *p; p++) {
        if (*p == '+' || *p == '-' || *p == '*') {
            // Split the expression into left and right parts
            char left[21], right[21];
            strncpy(left, expression, p - expression);
            left[p - expression] = '\0';
            strcpy(right, p + 1);

            // Recursively compute results for left and right parts
            int leftSize, rightSize;
            int* leftResults = diffWaysToCompute(left, &leftSize);
            int* rightResults = diffWaysToCompute(right, &rightSize);

            // Combine results from left and right parts based on the operator
            for (int i = 0; i < leftSize; i++) {
                for (int j = 0; j < rightSize; j++) {
                    int combinedResult;
                    if (*p == '+') {
                        combinedResult = leftResults[i] + rightResults[j];
                    } else if (*p == '-') {
                        combinedResult = leftResults[i] - rightResults[j];
                    } else { // '*'
                        combinedResult = leftResults[i] * rightResults[j];
                    }
                    results = (int*)realloc(results, sizeof(int) * (count + 1));
                    results[count++] = combinedResult;
                }
            }

            free(leftResults);
            free(rightResults);
        }
    }

    *returnSize = count;
    return results;     
}
