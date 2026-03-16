// Source: https://leetcode.com/problems/maximum-students-taking-exam/   |   Difficulty: Hard
//
// Problem Description:
// Given a m * n matrix seats  that represent seats distributions in a classroom. If a seat is broken, it is denoted by '#' character otherwise it is denoted by a '.' character.
//
// Students can see the answers of those sitting next to the left, right, upper left and upper right, but he cannot see the answers of the student sitting directly in front or behind him. Return the maximum number of students that can take the exam together without any cheating being possible.
//
// Students must be placed in seats in good condition.
//
// Example:
// Input: seats = [["#",".","#","#",".","#"],
//                 [".","#","#","#","#","."],
//                 ["#",".","#","#",".","#"]]
// Output: 4
// Explanation: Teacher can place 4 students in available seats so they don't cheat on the exam.
//
// Constraints:
// seats contains only characters '.' and'#'.
// 	m == seats.length
// 	n == seats[i].length
// 	1 <= m <= 8
// 	1 <= n <= 8
//

class Solution {
    public int maxStudents(char[][] seats) {
        int m = seats.length, n = seats[0].length;
        int[] dp = new int[1 << n];
        for (int i = 0; i < m; i++) {
            int[] ndp = new int[1 << n];
            for (int mask = 0; mask < (1 << n); mask++) {
                if (!isValid(seats[i], mask, n)) continue;
                for (int pmask = 0; pmask < (1 << n); pmask++) {
                    if ((mask & (pmask << 1)) != 0 || (mask & (pmask >> 1)) != 0) continue;
                    ndp[mask] = Math.max(ndp[mask], dp[pmask] + Integer.bitCount(mask));
                }
            }
            dp = ndp;
        }
        int result = 0;
        for (int val : dp) {
            result = Math.max(result, val);
        }
        return result;                  
    }
}
