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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* diffWaysToCompute(char* expression, int* returnSize) {
    int len = strlen(expression);
    int *results = (int *)malloc(0);
    *returnSize = 0;

    for (int i = 0; i < len; i++) {
        char c = expression[i];
        if (c == '+' || c == '-' || c == '*') {
            int leftSize = 0, rightSize = 0;
            char leftExpr[i + 1];
            strncpy(leftExpr, expression, i);
            leftExpr[i] = '\0';
            char rightExpr[len - i];
            strncpy(rightExpr, expression + i + 1, len - i - 1);
            rightExpr[len - i - 1] = '\0';

            int *leftResults = diffWaysToCompute(leftExpr, &leftSize);
            int *rightResults = diffWaysToCompute(rightExpr, &rightSize);

            for (int l = 0; l < leftSize; l++) {
                for (int r = 0; r < rightSize; r++) {
                    int res;
                    if (c == '+') {
                        res = leftResults[l] + rightResults[r];
                    } else if (c == '-') {
                        res = leftResults[l] - rightResults[r];
                    } else if (c == '*') {
                        res = leftResults[l] * rightResults[r];
                    }
                    results = (int *)realloc(results, sizeof(int) * (*returnSize + 1));
                    results[*returnSize] = res;
                    (*returnSize)++;
                }
            }
            free(leftResults);
            free(rightResults);
        }
    }

    if (*returnSize == 0) {
        int num = atoi(expression);
        results = (int *)malloc(sizeof(int));
        results[0] = num;
        *returnSize = 1;
    }

    return results;     
}
