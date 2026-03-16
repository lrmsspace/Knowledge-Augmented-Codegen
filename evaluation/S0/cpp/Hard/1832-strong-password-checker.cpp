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
public:
    int strongPasswordChecker(string password) {
        int n = password.size();
        bool hasLower = false, hasUpper = false, hasDigit = false;
        for (char c : password) {
            if (islower(c)) hasLower = true;
            else if (isupper(c)) hasUpper = true;
            else if (isdigit(c)) hasDigit = true;
        }
        
        int missingTypes = (!hasLower) + (!hasUpper) + (!hasDigit);
        
        vector<int> repeats;
        for (int i = 0; i < n;) {
            int j = i;
            while (j < n && password[j] == password[i]) j++;
            int len = j - i;
            if (len >= 3) repeats.push_back(len);
            i = j;
        }
        
        int toAdd = max(0, 6 - n);
        int toDelete = max(0, n - 20);
        
        int replace = 0;
        vector<int> modCount(3, 0);
        
        for (int len : repeats) {
            replace += len / 3;
            modCount[len % 3]++;
        }
        
        if (n <= 20) {
            return max(toAdd, max(missingTypes, replace));
        } else {
            int deleteRemaining = toDelete;
            
            for (int k = 0; k < 3; k++) {
                if (k == 2) {
                    int need = replace * 3;
                    int canDelete = min(deleteRemaining, need);
                    replace -= canDelete / 3;
                    deleteRemaining -= canDelete;
                } else {
                    int need = modCount[k] * (k + 1);
                    int canDelete = min(deleteRemaining, need);
                    replace -= canDelete / (k + 1);
                    deleteRemaining -= canDelete;
                }
            }
            
            return toDelete + max(missingTypes, replace);
        }           
    }
};
