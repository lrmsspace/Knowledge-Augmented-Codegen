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

class Solution {
    public int strongPasswordChecker(String password) {
        int n = password.length();
        boolean hasLower = false, hasUpper = false, hasDigit = false;

        for (char c : password.toCharArray()) {
            if (Character.isLowerCase(c)) hasLower = true;
            else if (Character.isUpperCase(c)) hasUpper = true;
            else if (Character.isDigit(c)) hasDigit = true;
        }

        int missingTypes = 0;
        if (!hasLower) missingTypes++;
        if (!hasUpper) missingTypes++;
        if (!hasDigit) missingTypes++;

        int replace = 0;
        int[] count = new int[3];
        for (int i = 2; i < n; ) {
            if (password.charAt(i) == password.charAt(i - 1) && password.charAt(i - 1) == password.charAt(i - 2)) {
                int length = 2;
                while (i < n && password.charAt(i) == password.charAt(i - 1)) {
                    length++;
                    i++;
                }
                replace += length / 3;
                count[length % 3]++;
            } else {
                i++;
            }
        }

        if (n < 6) {
            return Math.max(missingTypes, 6 - n);
        } else if (n <= 20) {
            return Math.max(missingTypes, replace);
        } else {
            int delete = n - 20;
            int remainDelete = delete;

            for (int i = 0; i < 3; i++) {
                if (remainDelete <= 0) break;
                int num = count[i];
                if (i == 0) {
                    int needDelete = Math.min(num, remainDelete);
                    replace -= needDelete;
                    remainDelete -= needDelete;
                } else if (i == 1) {
                    int needDelete = Math.min(num * 2, remainDelete);
                    replace -= needDelete / 2;
                    remainDelete -= needDelete;
                } else {
                    int needDelete = Math.min(num * 3, remainDelete);
                    replace -= needDelete / 3;
                    remainDelete -= needDelete;
                }
            }

            return delete + Math.max(missingTypes, replace);
        }           
    }
}
