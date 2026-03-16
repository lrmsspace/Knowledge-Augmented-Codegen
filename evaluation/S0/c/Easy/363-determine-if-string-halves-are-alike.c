// Source: https://leetcode.com/problems/determine-if-string-halves-are-alike/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s of even length. Split this string into two halves of equal lengths, and let a be the first half and b be the second half.
//
// Two strings are alike if they have the same number of vowels ('a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'). Notice that s contains uppercase and lowercase letters.
//
// Return true if a and b are alike. Otherwise, return false.
//
// Example:
// Input: s = "book"
// Output: true
// Explanation: a = "bo" and b = "ok". a has 1 vowel and b has 1 vowel. Therefore, they are alike.
//
// Constraints:
// 2 <= s.length <= 1000
// 	s.length is even.
// 	s consists of uppercase and lowercase letters.
//

bool halvesAreAlike(char* s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }

    int mid = len / 2;
    int countA = 0;
    int countB = 0;

    for (int i = 0; i < mid; i++) {
        char chA = s[i];
        char chB = s[i + mid];

        if (chA == 'a' || chA == 'e' || chA == 'i' || chA == 'o' || chA == 'u' ||
            chA == 'A' || chA == 'E' || chA == 'I' || chA == 'O' || chA == 'U') {
            countA++;
        }

        if (chB == 'a' || chB == 'e' || chB == 'i' || chB == 'o' || chB == 'u' ||
            chB == 'A' || chB == 'E' || chB == 'I' || chB == 'O' || chB == 'U') {
            countB++;
        }
    }

    return countA == countB;        
}
