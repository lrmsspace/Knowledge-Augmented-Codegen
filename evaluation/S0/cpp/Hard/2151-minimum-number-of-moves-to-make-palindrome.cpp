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
public:
    int minMovesToMakePalindrome(string s) {
        int n = s.size();
        int left = 0, right = n - 1;
        int moves = 0;
        
        while (left < right) {
            int l = left, r = right;
            // Find matching character for s[left] from the right side
            while (r > l && s[r] != s[l]) {
                r--;
            }
            
            if (r == l) {
                // No matching character found, swap s[l] with s[l+1]
                swap(s[l], s[l + 1]);
                moves++;
            } else {
                // Matching character found at position r
                // Move it to position right by swapping adjacent characters
                for (int i = r; i < right; i++) {
                    swap(s[i], s[i + 1]);
                    moves++;
                }
                left++;
                right--;
            }
        }
        
        return moves;           
    }
};
