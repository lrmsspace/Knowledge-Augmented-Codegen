// Source: https://leetcode.com/problems/optimal-division/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. The adjacent integers in nums will perform the float division.
//
//
// 	For example, for nums = [2,3,4], we will evaluate the expression "2/3/4".
//
//
// However, you can add any number of parenthesis at any position to change the priority of operations. You want to add these parentheses such the value of the expression after the evaluation is maximum.
//
// Return the corresponding expression that has the maximum value in string format.
//
// Note: your expression should not contain redundant parenthesis.
//
// Example:
// Input: nums = [1000,100,10,2]
// Output: "1000/(100/10/2)"
// Explanation: 1000/(100/10/2) = 1000/((100/10)/2) = 200
// However, the bold parenthesis in "1000/((100/10)/2)" are redundant since they do not influence the operation priority.
// So you should return "1000/(100/10/2)".
// Other cases:
// 1000/(100/10)/2 = 50
// 1000/(100/(10/2)) = 50
// 1000/100/10/2 = 0.5
// 1000/100/(10/2) = 2
//
// Constraints:
// 1 <= nums.length <= 10
// 	2 <= nums[i] <= 1000
// 	There is only one optimal division for the given input.
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

char* optimalDivision(int* nums, int numsSize) {
    // If there is only one number, return it as a string.
    if (numsSize == 1) {
        char* result = (char*)malloc(12 * sizeof(char)); // Enough for numbers up to 1000
        sprintf(result, "%d", nums[0]);
        return result;
    }
    
    // If there are two numbers, return them in the format "a/b".
    if (numsSize == 2) {
        char* result = (char*)malloc(25 * sizeof(char)); // Enough for "a/b"
        sprintf(result, "%d/%d", nums[0], nums[1]);
        return result;
    }
    
    // For more than two numbers, we want to maximize the division by grouping all but the first number together.
    // This can be achieved by returning "a/(b/c/d/...)".
    char* result = (char*)malloc(100 * sizeof(char)); // Enough for the entire expression
    sprintf(result, "%d/(", nums[0]);
    
    for (int i = 1; i < numsSize; i++) {
        sprintf(result + strlen(result), "%d", nums[i]);
        if (i < numsSize - 1) {
            sprintf(result + strlen(result), "/");
        }
    }
    
    sprintf(result + strlen(result), ")");
    
    return result;      
}
