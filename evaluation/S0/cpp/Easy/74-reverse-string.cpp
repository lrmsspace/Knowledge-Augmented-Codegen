// Source: https://leetcode.com/problems/reverse-string/   |   Difficulty: Easy
//
// Problem Description:
// Write a function that reverses a string. The input string is given as an array of characters s.
//
// You must do this by modifying the input array in-place with O(1) extra memory.
//
// Example:
// Input: s = ["h","e","l","l","o"]
// Output: ["o","l","l","e","h"]
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is a printable ascii character.
//

class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0;
        int right = s.size() - 1;

        while (left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }           
    }
};
