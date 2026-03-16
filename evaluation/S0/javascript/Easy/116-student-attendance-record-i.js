// Source: https://leetcode.com/problems/student-attendance-record-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s representing an attendance record for a student where each character signifies whether the student was absent, late, or present on that day. The record only contains the following three characters:
//
//
// 	'A': Absent.
// 	'L': Late.
// 	'P': Present.
//
//
// The student is eligible for an attendance award if they meet both of the following criteria:
//
//
// 	The student was absent ('A') for strictly fewer than 2 days total.
// 	The student was never late ('L') for 3 or more consecutive days.
//
//
// Return true if the student is eligible for an attendance award, or false otherwise.
//
// Example:
// Input: s = "PPALLP"
// Output: true
// Explanation: The student has fewer than 2 absences and was never late 3 or more consecutive days.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s[i] is either 'A', 'L', or 'P'.
//

/**
 * @param {string} s
 * @return {boolean}
 */
var checkRecord = function(s) {
    let absences = 0;
    let lateStreak = 0;
    for (let i = 0; i < s.length; i++) {
        if (s[i] === 'A') {
            absences++;
            if (absences >= 2) return false;
            lateStreak = 0;
        } else if (s[i] === 'L') {
            lateStreak++;
            if (lateStreak >= 3) return false;
        } else {
            lateStreak = 0;
        }
    }
    return true;
};      