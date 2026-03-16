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

/**
 * @param {character[][]} seats
 * @return {number}
 */
var maxStudents = function(seats) {
    const m = seats.length;
    const n = seats[0].length;
    const dp = new Array(m).fill(0).map(() => new Array(1 << n).fill(0));
    for (let i = 0; i < m; i++) {
        for (let mask = 0; mask < (1 << n); mask++) {
            let count = 0;
            let valid = true;
            for (let j = 0; j < n; j++) {
                if ((mask & (1 << j)) > 0) {
                    if (seats[i][j] === '#') {
                        valid = false;
                        break;
                    }
                    count++;    
                    if (j > 0 && (mask & (1 << (j - 1))) > 0) {
                        valid = false;
                        break;
                    }
                }
            }
            if (!valid) {
                continue;
            }
            if (i > 0) {
                for (let prevMask = 0; prevMask < (1 << n); prevMask++) {
                    if ((mask & (prevMask << 1)) === 0 && (mask & (prevMask >> 1)) === 0) {
                        dp[i][mask] = Math.max(dp[i][mask], dp[i - 1][prevMask] + count);
                    }
                }
            } else {
                dp[i][mask] = count;
            }
        }
    }
    return Math.max(...dp[m - 1]);  
};
