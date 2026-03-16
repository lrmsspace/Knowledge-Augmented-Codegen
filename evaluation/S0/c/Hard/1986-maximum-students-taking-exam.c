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

int maxStudents(char** seats, int seatsSize, int* seatsColSize) {
    int m = seatsSize;
    int n = seatsColSize[0];
    int maxState = 1 << n;
    int dp[8][256]; /* dp[row][state] = max students up to row with state */
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;

    for (int row = 0; row < m; ++row) {
        for (int state = 0; state < maxState; ++state) {
            /* check if state is valid */
            int valid = 1, count = 0;
            for (int col = 0; col < n; ++col) {
                if ((state & (1 << col)) != 0) {
                    if (seats[row][col] == '#') {
                        valid = 0; break;
                    }
                    if (col > 0 && (state & (1 << (col - 1))) != 0) {
                        valid = 0; break;
                    }
                    if (col < n - 1 && (state & (1 << (col + 1))) != 0) {
                        valid = 0; break;
                    }
                    count++;
                }
            }
            if (!valid) continue;

            /* transition from previous row */
            for (int prevState = 0; prevState < maxState; ++prevState) {
                if (dp[row][prevState] < 0) continue;
                /* check cheating condition with previous row */
                int cheat = 0;
                for (int col = 0; col < n; ++col) {
                    if ((state & (1 << col)) != 0) {
                        if (col > 0 && (prevState & (1 << (col - 1))) != 0) {
                            cheat = 1; break;
                        }
                        if (col < n - 1 && (prevState & (1 << (col + 1))) != 0) {
                            cheat = 1; break;
                        }
                    }
                }
                if (cheat) continue;

                if (dp[row + 1][state] < dp[row][prevState] + count) {
                    dp[row + 1][state] = dp[row][prevState] + count;
                }
            }
        }
    }

    int result = 0;     
    for (int state = 0; state < maxState; ++state) {
        if (dp[m][state] > result) {
            result = dp[m][state];
        }
    }
    return result;
}
