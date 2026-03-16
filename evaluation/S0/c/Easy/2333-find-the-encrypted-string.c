// Source: https://leetcode.com/problems/find-the-encrypted-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s and an integer k. Encrypt the string using the following algorithm:
//
//
// 	For each character c in s, replace c with the kth character after c in the string (in a cyclic manner).
//
//
// Return the encrypted string.
//
// Example:
// Input: s = "dart", k = 3
//
// Output: "tdar"
//
// Explanation:
//
//
// 	For i = 0, the 3rd character after 'd' is 't'.
// 	For i = 1, the 3rd character after 'a' is 'd'.
// 	For i = 2, the 3rd character after 'r' is 'a'.
// 	For i = 3, the 3rd character after 't' is 'r'.
//
// Constraints:
// 1 <= s.length <= 100
// 	1 <= k <= 104
// 	s consists only of lowercase English letters.
//

char* getEncryptedString(char* s, int k) {
    int n = 0;
    while (s[n]) n++;

    char* encrypted = (char*)malloc((n + 1) * sizeof(char));
    for (int i = 0; i < n; i++) {
        encrypted[i] = 'a' + (s[i] - 'a' + k) % 26;
    }
    encrypted[n] = '\0';

    return encrypted;       
}
