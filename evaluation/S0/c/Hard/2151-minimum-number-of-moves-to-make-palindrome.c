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

int minMovesToMakePalindrome(char* s) {
    int len = strlen(s);
    int left = 0, right = len - 1;
    int moves = 0;

    while (left < right) {
        int l = left, r = right;

        // Find the matching character for s[left] from the right side
        while (r > l && s[r] != s[l]) {
            r--;
        }

        if (r == l) {
            // No matching character found, swap with the next character
            char temp = s[l];
            s[l] = s[l + 1];
            s[l + 1] = temp;
            moves++;
        } else {
            // Move the matching character to the right position
            for (int i = r; i < right; i++) {
                char temp = s[i];
                s[i] = s[i + 1];
                s[i + 1] = temp;
                moves++;
            }
            left++;
            right--;
        }
    }

    return moves;       
}
