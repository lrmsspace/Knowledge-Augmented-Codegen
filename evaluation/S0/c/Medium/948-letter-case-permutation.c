// Source: https://leetcode.com/problems/letter-case-permutation/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, you can transform every letter individually to be lowercase or uppercase to create another string.
//
// Return a list of all possible strings we could create. Return the output in any order.
//
// Example:
// Input: s = "a1b2"
// Output: ["a1b2","a1B2","A1b2","A1B2"]
//
// Constraints:
// 1 <= s.length <= 12
// 	s consists of lowercase English letters, uppercase English letters, and digits.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** letterCasePermutation(char* s, int* returnSize) {
    int n = strlen(s);
    int total = 1 << n; // 2^n possible combinations
    char** result = (char**)malloc(total * sizeof(char*));
    *returnSize = 0;

    for (int mask = 0; mask < total; ++mask) {
        char* permutation = (char*)malloc((n + 1) * sizeof(char));
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            if (isalpha(c)) {
                // Check if the i-th bit in mask is set
                if (mask & (1 << i)) {
                    permutation[i] = toupper(c);
                } else {
                    permutation[i] = tolower(c);
                }
            } else {
                permutation[i] = c; // Keep digits unchanged
            }
        }
        permutation[n] = '\0'; // Null-terminate the string
        result[(*returnSize)++] = permutation;
    }

    return result;      
}
