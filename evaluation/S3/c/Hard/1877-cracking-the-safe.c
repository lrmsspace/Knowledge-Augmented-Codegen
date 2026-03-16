// Source: https://leetcode.com/problems/cracking-the-safe/   |   Difficulty: Hard
//
// Problem Description:
// There is a safe protected by a password. The password is a sequence of n digits where each digit can be in the range [0, k - 1].
//
// The safe has a peculiar way of checking the password. When you enter in a sequence, it checks the most recent n digits that were entered each time you type a digit.
//
//
// 	For example, the correct password is "345" and you enter in "012345":
//
// 	
// 		After typing 0, the most recent 3 digits is "0", which is incorrect.
// 		After typing 1, the most recent 3 digits is "01", which is incorrect.
// 		After typing 2, the most recent 3 digits is "012", which is incorrect.
// 		After typing 3, the most recent 3 digits is "123", which is incorrect.
// 		After typing 4, the most recent 3 digits is "234", which is incorrect.
// 		After typing 5, the most recent 3 digits is "345", which is correct and the safe unlocks.
// 	
// 	
//
//
// Return any string of minimum length that will unlock the safe at some point of entering it.
//
// Example:
// Input: n = 1, k = 2
// Output: "10"
// Explanation: The password is a single digit, so enter each digit. "01" would also unlock the safe.
//
// Constraints:
// 1 <= n <= 4
// 	1 <= k <= 10
// 	1 <= kn <= 4096
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Digit DP (array, number, digit-dp)
//   • When to use: When counting numbers within a given range [A, B] that satisfy certain digit-based properties, or calculating a sum of such properties.
//   • Idea: Digit DP is a dynamic programming technique used to count numbers or calculate sums of properties for numbers within a given range, based on their digits. It typically involves a recursive function with memoization, processing digits from most significant to least significant, achieving a time complexity of O(log(N) * S * T) where S is sum/state range and T is tight constraint.
//   • Invariants: The `idx` parameter always represents the current digit position being processed, from most significant to least significant.; The `tight` boolean parameter accurately indicates if the current digit choice is restricted by the original number's corresponding digit.
//   • Tips: Handle leading zeros carefully, often with a dedicated boolean state in the DP function.; Use a 'tight' or 'limit' boolean parameter to manage the upper bound constraint imposed by the original number.
//   • Pitfalls: Incorrectly handling the 'tight' constraint can lead to overcounting or undercounting.; Forgetting to reset the memoization table for each new query or test case, especially in competitive programming.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* crackSafe(int n, int k) {
    int total = 1;
    for (int i = 0; i < n; i++) {
        total *= k;
    }
    
    char* result = (char*)malloc((total + n) * sizeof(char));
    result[0] = '\0'; // Initialize the result string
    
    // Generate the de Bruijn sequence
    char* visited = (char*)calloc(total, sizeof(char));
    
    void dfs(int node) {
        for (int i = 0; i < k; i++) {
            int nextNode = node * k + i;
            if (!visited[nextNode % total]) {
                visited[nextNode % total] = 1;
                dfs(nextNode % total);
                char digit[2] = {i + '0', '\0'};
                strcat(result, digit);
            }
        }
    }
    
    dfs(0);
    
    // Append the first n-1 digits to complete the cycle
    for (int i = 0; i < n - 1; i++) {
        char digit[2] = {'0', '\0'};
        strcat(result, digit);
    }
    
    free(visited);
    
    return result;      
}
