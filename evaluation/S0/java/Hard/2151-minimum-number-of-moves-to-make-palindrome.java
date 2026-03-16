// Source: https://leetcode.com/problems/minimum-number-of-moves-to-make-palindrome/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s consisting only of lowercase English letters.
//
// In one move, you can select any two adjacent characters of s and swap them.
//
// Return the minimum number of moves needed to make s a palindrome.
//
// Note that the input will be generated such that s can always be converted to a palindrome.
//
// Example:
// Input: s = "aabb"
// Output: 2
// Explanation:
// We can obtain two palindromes from s, "abba" and "baab". 
// - We can obtain "abba" from s in 2 moves: "aabb" -> "abab" -> "abba".
// - We can obtain "baab" from s in 2 moves: "aabb" -> "abab" -> "baab".
// Thus, the minimum number of moves needed to make s a palindrome is 2.
//
// Constraints:
// 1 <= s.length <= 2000
// 	s consists only of lowercase English letters.
// 	s can be converted to a palindrome using a finite number of moves.
//

class Solution {
    public int minMovesToMakePalindrome(String s) {
        char[] arr = s.toCharArray();
        int left = 0, right = arr.length - 1;
        int moves = 0;

        while (left < right) {
            int l = left, r = right;

            // Find the matching character for arr[left] from the right side
            while (l < r && arr[l] != arr[r]) {
                r--;
            }

            if (l == r) {
                // No matching character found, swap with the next character
                swap(arr, r, r + 1);
                moves++;
            } else {
                // Move the matching character to the right position
                while (r < right) {
                    swap(arr, r, r + 1);
                    moves++;
                    r++;
                }
                left++;
                right--;
            }
        }

        return moves;           
    }
}
