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

int strongPasswordChecker(char* password) {
    int n = strlen(password);
    int hasLower = 0, hasUpper = 0, hasDigit = 0;
    for (int i = 0; i < n; ++i) {
        if ('a' <= password[i] && password[i] <= 'z') hasLower = 1;
        else if ('A' <= password[i] && password[i] <= 'Z') hasUpper = 1;
        else if ('0' <= password[i] && password[i] <= '9') hasDigit = 1;
    }
    int missingTypes = 3 - (hasLower + hasUpper + hasDigit);

    int replace = 0;
    int oneMod = 0, twoMod = 0; // counts of sequences with (len % 3) == 1 and 2
    for (int i = 0; i < n;) {
        int j = i;
        while (j < n && password[j] == password[i]) ++j;
        int len = j - i;
        if (len >= 3) {
            replace += len / 3;
            if (len % 3 == 0) oneMod += 1;
            else if (len % 3 == 1) twoMod += 1;
        }
        i = j;
    }

    if (n < 6) {
        return fmax(missingTypes, 6 - n);
    } else if (n <= 20) {
        return fmax(missingTypes, replace);
    } else {
        int deleteCount = n - 20;
        int toDelete = deleteCount;

        // Reduce replacements by deleting characters from sequences
        if (toDelete > 0 && oneMod > 0) {
            int used = fmin(toDelete, oneMod * 1);
            replace -= used / 1;
            toDelete -= used;
        }
        if (toDelete > 0 && twoMod > 0) {
            int used = fmin(toDelete, twoMod * 2);
            replace -= used / 2;
            toDelete -= used;
        }
        if (toDelete > 0) {
            int used = toDelete;
            replace -= used / 3;
            toDelete -= used;
        }

        return deleteCount + fmax(missingTypes, replace);
    }       
}
