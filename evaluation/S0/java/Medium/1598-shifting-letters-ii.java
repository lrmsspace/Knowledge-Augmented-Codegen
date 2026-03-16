// Source: https://leetcode.com/problems/shifting-letters-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s of lowercase English letters and a 2D integer array shifts where shifts[i] = [starti, endi, directioni]. For every i, shift the characters in s from the index starti to the index endi (inclusive) forward if directioni = 1, or shift the characters backward if directioni = 0.
//
// Shifting a character forward means replacing it with the next letter in the alphabet (wrapping around so that 'z' becomes 'a'). Similarly, shifting a character backward means replacing it with the previous letter in the alphabet (wrapping around so that 'a' becomes 'z').
//
// Return the final string after all such shifts to s are applied.
//
// Example:
// Input: s = "abc", shifts = [[0,1,0],[1,2,1],[0,2,1]]
// Output: "ace"
// Explanation: Firstly, shift the characters from index 0 to index 1 backward. Now s = "zac".
// Secondly, shift the characters from index 1 to index 2 forward. Now s = "zbd".
// Finally, shift the characters from index 0 to index 2 forward. Now s = "ace".
//
// Constraints:
// 1 <= s.length, shifts.length <= 5 * 104
// 	shifts[i].length == 3
// 	0 <= starti <= endi < s.length
// 	0 <= directioni <= 1
// 	s consists of lowercase English letters.
//

class Solution {
    public String shiftingLetters(String s, int[][] shifts) {
        int n = s.length();
        int[] diff = new int[n + 1];

        // Build the difference array based on the shifts
        for (int[] shift : shifts) {
            int start = shift[0];
            int end = shift[1];
            int direction = shift[2] == 1 ? 1 : -1;

            diff[start] += direction;
            diff[end + 1] -= direction;
        }

        // Apply the difference array to get the final shifts for each character
        StringBuilder result = new StringBuilder();
        int currentShift = 0;

        for (int i = 0; i < n; i++) {
            currentShift += diff[i];
            int originalCharPos = s.charAt(i) - 'a';
            int newCharPos = (originalCharPos + currentShift) % 26;

            // Handle negative shifts
            if (newCharPos < 0) {
                newCharPos += 26;
            }

            result.append((char) ('a' + newCharPos));
        }

        return result.toString();           
    }
}
