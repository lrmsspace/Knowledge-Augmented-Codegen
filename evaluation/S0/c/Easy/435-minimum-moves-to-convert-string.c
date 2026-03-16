// Source: https://leetcode.com/problems/minimum-moves-to-convert-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s consisting of n characters which are either 'X' or 'O'.
//
// A move is defined as selecting three consecutive characters of s and converting them to 'O'. Note that if a move is applied to the character 'O', it will stay the same.
//
// Return the minimum number of moves required so that all the characters of s are converted to 'O'.
//
// Example:
// Input: s = "XXX"
// Output: 1
// Explanation: XXX -> OOO
// We select all the 3 characters and convert them in one move.
//
// Constraints:
// 3 <= s.length <= 1000
// 	s[i] is either 'X' or 'O'.
//

int minimumMoves(char* s) {
    int moves = 0;
    int i = 0;
    int n = strlen(s);
    
    while (i < n) {
        if (s[i] == 'X') {
            moves++;
            i += 3; // Skip the next two characters as they are converted to 'O'
        } else {
            i++;
        }
    }
    
    return moves;       
}
