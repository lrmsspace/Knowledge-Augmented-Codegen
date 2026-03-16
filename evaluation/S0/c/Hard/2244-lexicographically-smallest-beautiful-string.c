// Source: https://leetcode.com/problems/lexicographically-smallest-beautiful-string/   |   Difficulty: Hard
//
// Problem Description:
// A string is beautiful if:
//
//
// 	It consists of the first k letters of the English lowercase alphabet.
// 	It does not contain any substring of length 2 or more which is a palindrome.
//
//
// You are given a beautiful string s of length n and a positive integer k.
//
// Return the lexicographically smallest string of length n, which is larger than s and is beautiful. If there is no such string, return an empty string.
//
// A string a is lexicographically larger than a string b (of the same length) if in the first position where a and b differ, a has a character strictly larger than the corresponding character in b.
//
//
// 	For example, "abcd" is lexicographically larger than "abcc" because the first position they differ is at the fourth character, and d is greater than c.
//
// Example:
// Input: s = "abcz", k = 26
// Output: "abda"
// Explanation: The string "abda" is beautiful and lexicographically larger than the string "abcz".
// It can be proven that there is no string that is lexicographically larger than the string "abcz", beautiful, and lexicographically smaller than the string "abda".
//
// Constraints:
// 1 <= n == s.length <= 105
// 	4 <= k <= 26
// 	s is a beautiful string.
//

char* smallestBeautifulString(char* s, int k) {
    int n = strlen(s);
    char *res = (char*)malloc((n + 1) * sizeof(char));
    if (!res) return NULL;
    strcpy(res, s);

    for (int i = n - 1; i >= 0; --i) {
        for (char c = res[i] + 1; c < 'a' + k; ++c) {
            if ((i >= 1 && res[i - 1] == c) || (i >= 2 && res[i - 2] == c)) {
                continue;
            }
            res[i] = c;
            // Fill the rest with the smallest valid characters
            for (int j = i + 1; j < n; ++j) {
                for (char nc = 'a'; nc < 'a' + k; ++nc) {
                    if ((j >= 1 && res[j - 1] == nc) || (j >= 2 && res[j - 2] == nc)) {
                        continue;
                    }
                    res[j] = nc;
                    break;
                }
            }
            return res;
        }
    }
    free(res);
    return strdup("");      
}
