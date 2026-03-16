// Source: https://leetcode.com/problems/the-number-of-full-rounds-you-have-played/   |   Difficulty: Medium
//
// Problem Description:
// You are participating in an online chess tournament. There is a chess round that starts every 15 minutes. The first round of the day starts at 00:00, and after every 15 minutes, a new round starts.
//
//
// 	For example, the second round starts at 00:15, the fourth round starts at 00:45, and the seventh round starts at 01:30.
//
//
// You are given two strings loginTime and logoutTime where:
//
//
// 	loginTime is the time you will login to the game, and
// 	logoutTime is the time you will logout from the game.
//
//
// If logoutTime is earlier than loginTime, this means you have played from loginTime to midnight and from midnight to logoutTime.
//
// Return the number of full chess rounds you have played in the tournament.
//
// Note: All the given times follow the 24-hour clock. That means the first round of the day starts at 00:00 and the last round of the day starts at 23:45.
//
// Example:
// Input: loginTime = "09:31", logoutTime = "10:14"
// Output: 1
// Explanation: You played one full round from 09:45 to 10:00.
// You did not play the full round from 09:30 to 09:45 because you logged in at 09:31 after it began.
// You did not play the full round from 10:00 to 10:15 because you logged out at 10:14 before it ended.
//
// Constraints:
// loginTime and logoutTime are in the format hh:mm.
// 	00 <= hh <= 23
// 	00 <= mm <= 59
// 	loginTime and logoutTime are not equal.
//

class Solution {
    public int numberOfRounds(String loginTime, String logoutTime) {
        int loginMinutes = convertToMinutes(loginTime);
        int logoutMinutes = convertToMinutes(logoutTime);

        if (logoutMinutes < loginMinutes) {
            logoutMinutes += 24 * 60; // Adjust for next day logout
        }

        int fullRoundsStart = (loginMinutes + 14) / 15 * 15; // Next quarter hour after login
        int fullRoundsEnd = logoutMinutes / 15 * 15; // Last quarter hour before logout

        int fullRounds = (fullRoundsEnd - fullRoundsStart) / 15;
        return Math.max(0, fullRounds);         
    }
}
