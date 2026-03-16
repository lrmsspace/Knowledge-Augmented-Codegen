// Source: https://leetcode.com/problems/reverse-vowels-of-a-string/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, reverse only all the vowels in the string and return it.
//
// The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both lower and upper cases, more than once.
//
// Example:
// Input: s = "IceCreAm"
//
// Output: "AceCreIm"
//
// Explanation:
//
// The vowels in s are ['I', 'e', 'e', 'A']. On reversing the vowels, s becomes "AceCreIm".
//
// Constraints:
// 1 <= s.length <= 3 * 105
// 	s consist of printable ASCII characters.
//

class Solution {
public:
    string reverseVowels(string s) {
        int left = 0;
        int right = s.length() - 1;
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};

        while (left < right) {
            while (left < right && vowels.find(s[left]) == vowels.end()) {
                left++;
            }
            while (left < right && vowels.find(s[right]) == vowels.end()) {
                right--;
            }
            if (left < right) {
                swap(s[left], s[right]);
                left++;
                right--;
            }
        }

        return s;           
    }
};
