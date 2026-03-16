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

class Solution {
public:
    bool strongPasswordCheckerII(string password) {
        if (password.length() < 8) return false;

        bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;
        string specialChars = "!@#$%^&*()-+";

        for (int i = 0; i < password.length(); ++i) {
            char c = password[i];

            if (i > 0 && c == password[i - 1]) return false;

            if (islower(c)) hasLower = true;
            else if (isupper(c)) hasUpper = true;
            else if (isdigit(c)) hasDigit = true;
            else if (specialChars.find(c) != string::npos) hasSpecial = true;
        }

        return hasLower && hasUpper && hasDigit && hasSpecial;          
    }
};
