// Source: https://leetcode.com/problems/count-unique-characters-of-all-substrings-of-a-given-string/   |   Difficulty: Hard
//
// Problem Description:
// Let's define a function countUniqueChars(s) that returns the number of unique characters in s.
//
//
// 	For example, calling countUniqueChars(s) if s = "LEETCODE" then "L", "T", "C", "O", "D" are the unique characters since they appear only once in s, therefore countUniqueChars(s) = 5.
//
//
// Given a string s, return the sum of countUniqueChars(t) where t is a substring of s. The test cases are generated such that the answer fits in a 32-bit integer.
//
// Notice that some substrings can be repeated so in this case you have to count the repeated ones too.
//
// Example:
// Input: s = "ABC"
// Output: 10
// Explanation: All possible substrings are: "A","B","C","AB","BC" and "ABC".
// Every substring is composed with only unique letters.
// Sum of lengths of all substring is 1 + 1 + 1 + 2 + 2 + 3 = 10
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of uppercase English letters only.
//

int uniqueLetterString(char* s) {
    int index[26][2];
    int res = 0;
    int n = strlen(s);
    for (int i = 0; i < 26; ++i) {
        index[i][0] = -1;
        index[i][1] = -1;
    }
    for (int i = 0; i < n; ++i) {
        int c = s[i] - 'A';
        res += (i - index[c][1]) * (index[c][1] - index[c][0]);
        index[c][0] = index[c][1];
        index[c][1] = i;
    }
    for (int c = 0; c < 26; ++c) {
        res += (n - index[c][1]) * (index[c][1] - index[c][0]);
    }
    return res;     
}
