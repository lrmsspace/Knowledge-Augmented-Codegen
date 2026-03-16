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
    public boolean halvesAreAlike(String s) {
        int mid = s.length() / 2;
        String a = s.substring(0, mid);
        String b = s.substring(mid);

        return countVowels(a) == countVowels(b);            
    }
}
