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

void reverseString(char* s, int sSize) {
    int left = 0;
    int right = sSize - 1;
    while (left < right) {
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        left++;
        right--;
    }       
}
