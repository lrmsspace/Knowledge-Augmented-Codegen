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

int numberOfRounds(char* loginTime, char* logoutTime) {
    int loginHour = (loginTime[0] - '0') * 10 + (loginTime[1] - '0');
    int loginMin = (loginTime[3] - '0') * 10 + (loginTime[4] - '0');
    int logoutHour = (logoutTime[0] - '0') * 10 + (logoutTime[1] - '0');
    int logoutMin = (logoutTime[3] - '0') * 10 + (logoutTime[4] - '0');

    int loginTotalMin = loginHour * 60 + loginMin;
    int logoutTotalMin = logoutHour * 60 + logoutMin;

    if (logoutTotalMin < loginTotalMin) {
        logoutTotalMin += 24 * 60;
    }

    // Round up login time to the next quarter hour
    if (loginMin % 15 != 0) {
        loginTotalMin += 15 - (loginMin % 15);
    }

    // Round down logout time to the previous quarter hour
    logoutTotalMin -= logoutMin % 15;

    if (logoutTotalMin <= loginTotalMin) {
        return 0;
    }

    return (logoutTotalMin - loginTotalMin) / 15;       
}
