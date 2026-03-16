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
public:
    int maxStudents(vector<vector<char>>& seats) {
        int m = seats.size();
        int n = seats[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(1 << n, -1));
        dp[0][0] = 0;
        
        for (int i = 1; i <= m; i++) {
            for (int mask = 0; mask < (1 << n); mask++) {
                // Check if mask is valid
                bool valid = true;
                for (int j = 0; j < n; j++) {
                    if ((mask & (1 << j)) && seats[i - 1][j] == '#') {
                        valid = false;
                        break;
                    }
                    if (j > 0 && (mask & (1 << j)) && (mask & (1 << (j - 1)))) {
                        valid = false;
                        break;
                    }
                }
                if (!valid) continue;
                
                // Count students in current row
                int count = __builtin_popcount(mask);
                
                // Check previous row
                for (int prevMask = 0; prevMask < (1 << n); prevMask++) {
                    bool canPlace = true;
                    for (int j = 0; j < n; j++) {
                        if ((mask & (1 << j))) {
                            if (j > 0 && (prevMask & (1 << (j - 1)))) {
                                canPlace = false;
                                break;
                            }
                            if (j < n - 1 && (prevMask & (1 << (j + 1)))) {
                                canPlace = false;
                                break;
                            }
                        }
                    }
                    if (!canPlace) continue;
                    
                    if (dp[i - 1][prevMask] != -1) {
                        dp[i][mask] = max(dp[i][mask], dp[i - 1][prevMask] + count);
                    }
                }
            }
        }
        
        int result = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            result = max(result, dp[m][mask]);
        }
        
        return result;          
    }
};
