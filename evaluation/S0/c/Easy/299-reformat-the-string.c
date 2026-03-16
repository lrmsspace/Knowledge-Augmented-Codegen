// Source: https://leetcode.com/problems/reformat-the-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given an alphanumeric string s. (Alphanumeric string is a string consisting of lowercase English letters and digits).
//
// You have to find a permutation of the string where no letter is followed by another letter and no digit is followed by another digit. That is, no two adjacent characters have the same type.
//
// Return the reformatted string or return an empty string if it is impossible to reformat the string.
//
// Example:
// Input: s = "a0b1c2"
// Output: "0a1b2c"
// Explanation: No two adjacent characters have the same type in "0a1b2c". "a0b1c2", "0a1b2c", "0c2a1b" are also valid permutations.
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of only lowercase English letters and/or digits.
//

char* reformat(char* s) {
    int len = 0, digitCount = 0, letterCount = 0;
    while (s[len]) {
        if (s[len] >= '0' && s[len] <= '9') {
            digitCount++;
        } else {
            letterCount++;
        }
        len++;
    }

    if (abs(digitCount - letterCount) > 1) {
        return "";
    }

    char* result = (char*)malloc((len + 1) * sizeof(char));
    result[len] = '\0';

    int digitIndex = 0, letterIndex = 0;
    if (digitCount >= letterCount) {
        for (int i = 0; i < len; i += 2) {
            while (!(s[digitIndex] >= '0' && s[digitIndex] <= '9')) {
                digitIndex++;
            }
            result[i] = s[digitIndex++];
        }
        for (int i = 1; i < len; i += 2) {
            while (!(s[letterIndex] >= 'a' && s[letterIndex] <= 'z')) {
                letterIndex++;
            }
            result[i] = s[letterIndex++];
        }
    } else {
        for (int i = 0; i < len; i += 2) {
            while (!(s[letterIndex] >= 'a' && s[letterIndex] <= 'z')) {
                letterIndex++;
            }
            result[i] = s[letterIndex++];
        }
        for (int i = 1; i < len; i += 2) {
            while (!(s[digitIndex] >= '0' && s[digitIndex] <= '9')) {
                digitIndex++;
            }
            result[i] = s[digitIndex++];
        }
    }

    return result;      
}
