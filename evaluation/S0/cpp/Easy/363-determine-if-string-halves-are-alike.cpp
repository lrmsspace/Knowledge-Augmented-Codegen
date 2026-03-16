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

class Solution {
public:
    bool halvesAreAlike(string s) {
        auto is_vowel = [](char c) {
            c = tolower(c);
            return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
        };

        int n = s.size();
        int count_first_half = 0;
        int count_second_half = 0;

        for (int i = 0; i < n / 2; ++i) {
            if (is_vowel(s[i])) {
                ++count_first_half;
            }
            if (is_vowel(s[i + n / 2])) {
                ++count_second_half;
            }
        }

        return count_first_half == count_second_half;           
    }
};
