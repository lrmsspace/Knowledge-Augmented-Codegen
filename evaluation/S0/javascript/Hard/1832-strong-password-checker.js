// Source: https://leetcode.com/problems/strong-password-checker/   |   Difficulty: Hard
//
// Problem Description:
// A password is considered strong if the below conditions are all met:
//
//
// 	It has at least 6 characters and at most 20 characters.
// 	It contains at least one lowercase letter, at least one uppercase letter, and at least one digit.
// 	It does not contain three repeating characters in a row (i.e., "Baaabb0" is weak, but "Baaba0" is strong).
//
//
// Given a string password, return the minimum number of steps required to make password strong. if password is already strong, return 0.
//
// In one step, you can:
//
//
// 	Insert one character to password,
// 	Delete one character from password, or
// 	Replace one character of password with another character.
//
// Example:
// Input: password = "a"
// Output: 5
//
// Constraints:
// 1 <= password.length <= 50
// 	password consists of letters, digits, dot '.' or exclamation mark '!'.
//

/**
 * @param {string} password
 * @return {number}
 */
var strongPasswordChecker = function(password) {
        const n = password.length;
    let hasLower = false, hasUpper = false, hasDigit = false;
    for (let char of password) {
        if (char >= 'a' && char <= 'z') {
            hasLower = true;
        } else if (char >= 'A' && char <= 'Z') {
            hasUpper = true;
        } else if (char >= '0' && char <= '9') {
            hasDigit = true;
        }
    }
    const missingTypes = (hasLower ? 0 : 1) + (hasUpper ? 0 : 1) + (hasDigit ? 0 : 1);
    if (n < 6) {
        return Math.max(missingTypes, 6 - n);
    } else {
        let replace = 0, one = 0, two = 0;
        for (let i = 2; i < n; i++) {
            if (password[i] === password[i - 1] && password[i - 1] === password[i - 2]) {
                replace++;
                if (password[i - 2] === password[i - 3]) {
                    two++;
                } else if (password[i - 2] === password[i - 4]) {
                    one++;
                }
            }
        }
        if (n <= 20) {
            return Math.max(missingTypes, replace);
        }
        let deleteCount = n - 20;
        replace -= Math.min(deleteCount, one * 1) / 1;
        replace -= Math.min(Math.max(deleteCount - one, 0), two * 2) / 2;
        replace -= Math.max(deleteCount - one - 2 * two, 0) / 3;
        return deleteCount + Math.max(missingTypes, replace);
        
    
};
