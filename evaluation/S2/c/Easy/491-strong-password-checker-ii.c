// Source: https://leetcode.com/problems/strong-password-checker-ii/   |   Difficulty: Easy
//
// Problem Description:
// A password is said to be strong if it satisfies all the following criteria:
//
//
// 	It has at least 8 characters.
// 	It contains at least one lowercase letter.
// 	It contains at least one uppercase letter.
// 	It contains at least one digit.
// 	It contains at least one special character. The special characters are the characters in the following string: "!@#$%^&*()-+".
// 	It does not contain 2 of the same character in adjacent positions (i.e., "aab" violates this condition, but "aba" does not).
//
//
// Given a string password, return true if it is a strong password. Otherwise, return false.
//
// Example:
// Input: password = "IloveLe3tcode!"
// Output: true
// Explanation: The password meets all the requirements. Therefore, we return true.
//
// Constraints:
// 1 <= password.length <= 100
// 	password consists of letters, digits, and special characters: "!@#$%^&*()-+".
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

bool strongPasswordCheckerII(char* password) {
    int len = strlen(password);
    if (len < 8) {
        return false;
    }

    bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;
    char specialChars[] = "!@#$%^&*()-+";

    for (int i = 0; i < len; i++) {
        char c = password[i];
        if (islower(c)) {
            hasLower = true;
        } else if (isupper(c)) {
            hasUpper = true;
        } else if (isdigit(c)) {
            hasDigit = true;
        } else if (strchr(specialChars, c)) {
            hasSpecial = true;
        }

        // Check for adjacent characters
        if (i > 0 && password[i] == password[i - 1]) {
            return false;
        }
    }

    return hasLower && hasUpper && hasDigit && hasSpecial;      
}
