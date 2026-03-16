// Source: https://leetcode.com/problems/minimum-number-of-chairs-in-a-waiting-room/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s. Simulate events at each second i:
//
//
// 	If s[i] == 'E', a person enters the waiting room and takes one of the chairs in it.
// 	If s[i] == 'L', a person leaves the waiting room, freeing up a chair.
//
//
// Return the minimum number of chairs needed so that a chair is available for every person who enters the waiting room given that it is initially empty.
//
// Example:
// Input: s = "EEEEEEE"
//
// Output: 7
//
// Explanation:
//
// After each second, a person enters the waiting room and no person leaves it. Therefore, a minimum of 7 chairs is needed.
//
// Constraints:
// 1 <= s.length <= 50
// 	s consists only of the letters 'E' and 'L'.
// 	s represents a valid sequence of entries and exits.
//

class Solution {
    public int minimumChairs(String s) {
        int currentChairs = 0;
        int maxChairs = 0;

        for (char event : s.toCharArray()) {
            if (event == 'E') {
                currentChairs++;
                maxChairs = Math.max(maxChairs, currentChairs);
            } else if (event == 'L') {
                currentChairs--;
            }
        }

        return maxChairs;           
    }
}
