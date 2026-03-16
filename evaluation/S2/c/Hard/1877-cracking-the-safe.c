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
// - N/A
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
    if (!result) {
        return NULL; // Handle memory allocation failure
    }

    // Initialize the result with the first n digits
    for (int i = 0; i < n; i++) {
        result[i] = '0';
    }
    result[n] = '\0';

    // Generate the de Bruijn sequence
    for (int i = 0; i < total; i++) {
        int current = 0;
        for (int j = 0; j < n - 1; j++) {
            current = current * k + (result[i + j] - '0');
        }
        current = current * k + (result[i + n - 1] - '0');
        result[total + i] = '0' + (current % k);
    }
    result[total + n - 1] = '\0';

    return result;      
}
