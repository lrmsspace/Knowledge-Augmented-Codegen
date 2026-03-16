// Source: https://leetcode.com/problems/letter-combinations-of-a-phone-number/   |   Difficulty: Medium
//
// Problem Description:
// Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.
//
// A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.
//
// Example:
// Input: digits = "23"
// Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
//
// Constraints:
// 0 <= digits.length <= 4
// 	digits[i] is a digit in the range ['2', '9'].
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** letterCombinations(char* digits, int* returnSize) {
    if (!digits || !*digits) {
        *returnSize = 0;
        return NULL;
    }

    const char* mapping[] = {
        "",     "",     "abc",  "def",
        "ghi",  "jkl",  "mno",  "pqrs",
        "tuv",  "wxyz"
    };

    int len = strlen(digits);
    int totalCombinations = 1;
    for (int i = 0; i < len; i++) {
        totalCombinations *= strlen(mapping[digits[i] - '0']);
    }

    char** result = (char**)malloc(totalCombinations * sizeof(char*));
    for (int i = 0; i < totalCombinations; i++) {
        result[i] = (char*)malloc((len + 1) * sizeof(char));
        result[i][len] = '\0';
    }

    for (int i = 0; i < totalCombinations; i++) {
        int index = i;
        for (int j = 0; j < len; j++) {
            const char* letters = mapping[digits[j] - '0'];
            int lettersCount = strlen(letters);
            result[i][j] = letters[index % lettersCount];
            index /= lettersCount;
        }
    }

    *returnSize = totalCombinations;
    return result;      
}
