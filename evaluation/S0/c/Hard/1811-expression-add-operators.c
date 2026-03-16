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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** addOperators(char* num, int target, int* returnSize) {
    // Implementation of expression add operators using backtracking
    
    #define MAX_RESULTS 1000
    #define MAX_EXPR_LEN 20
    
    char** results = (char**)malloc(sizeof(char*) * MAX_RESULTS);
    *returnSize = 0;
    
    void backtrack(int index, long currentValue, long lastOperand, char* expr, int exprLen) {
        if (index == strlen(num)) {
            if (currentValue == target) {
                expr[exprLen] = '\0';
                results[*returnSize] = strdup(expr);
                (*returnSize)++;
            }
            return;
        }
        
        for (int i = index; i < strlen(num); i++) {
            if (i != index && num[index] == '0') break; // Skip leading zeros
            
            char buffer[12];
            strncpy(buffer, &num[index], i - index + 1);
            buffer[i - index + 1] = '\0';
            long operand = atol(buffer);
            
            if (index == 0) {
                // First operand, no operator
                strcpy(&expr[exprLen], buffer);
                backtrack(i + 1, operand, operand, expr, exprLen + strlen(buffer));
            } else {
                // Addition
                expr[exprLen] = '+';
                strcpy(&expr[exprLen + 1], buffer);
                backtrack(i + 1, currentValue + operand, operand, expr, exprLen + 1 + strlen(buffer));
                
                // Subtraction
                expr[exprLen] = '-';
                strcpy(&expr[exprLen + 1], buffer);
                backtrack(i + 1, currentValue - operand, -operand, expr, exprLen + 1 + strlen(buffer));
                
                // Multiplication
                expr[exprLen] = '*';
                strcpy(&expr[exprLen + 1], buffer);
                backtrack(i + 1, currentValue - lastOperand + lastOperand * operand, lastOperand * operand, expr, exprLen + 1 + strlen(buffer));
            }
        }
    }
    
    char expr[MAX_EXPR_LEN];
    backtrack(0, 0, 0, expr, 0);
    
    return results;
}
