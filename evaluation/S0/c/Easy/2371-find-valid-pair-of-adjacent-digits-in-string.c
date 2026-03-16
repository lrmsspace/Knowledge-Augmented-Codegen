// Source: https://leetcode.com/problems/find-valid-pair-of-adjacent-digits-in-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s consisting only of digits. A valid pair is defined as two adjacent digits in s such that:
//
//
// 	The first digit is not equal to the second.
// 	Each digit in the pair appears in s exactly as many times as its numeric value.
//
//
// Return the first valid pair found in the string s when traversing from left to right. If no valid pair exists, return an empty string.
//
// Example:
// Input: s = "2523533"
//
// Output: "23"
//
// Explanation:
//
// Digit '2' appears 2 times and digit '3' appears 3 times. Each digit in the pair "23" appears in s exactly as many times as its numeric value. Hence, the output is "23".
//
// Constraints:
// 2 <= s.length <= 100
// 	s only consists of digits from '1' to '9'.
//

char* findValidPair(char* s) {
    int count[10] = {0};
    int len = 0;
    while (s[len] != '\0') {
        count[s[len] - '0']++;
        len++;
    }

    for (int i = 0; i < len - 1; i++) {
        if (s[i] != s[i + 1]) {
            int firstDigit = s[i] - '0';
            int secondDigit = s[i + 1] - '0';
            if (count[firstDigit] == firstDigit && count[secondDigit] == secondDigit) {
                char* result = (char*)malloc(3 * sizeof(char));
                result[0] = s[i];
                result[1] = s[i + 1];
                result[2] = '\0';
                return result;
            }
        }
    }

    char* emptyResult = (char*)malloc(1 * sizeof(char));
    emptyResult[0] = '\0';
    return emptyResult;     
}
