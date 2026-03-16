// Source: https://leetcode.com/problems/count-days-spent-together/   |   Difficulty: Easy
//
// Problem Description:
// Alice and Bob are traveling to Rome for separate business meetings.
//
// You are given 4 strings arriveAlice, leaveAlice, arriveBob, and leaveBob. Alice will be in the city from the dates arriveAlice to leaveAlice (inclusive), while Bob will be in the city from the dates arriveBob to leaveBob (inclusive). Each will be a 5-character string in the format "MM-DD", corresponding to the month and day of the date.
//
// Return the total number of days that Alice and Bob are in Rome together.
//
// You can assume that all dates occur in the same calendar year, which is not a leap year. Note that the number of days per month can be represented as: [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31].
//
// Example:
// Input: arriveAlice = "08-15", leaveAlice = "08-18", arriveBob = "08-16", leaveBob = "08-19"
// Output: 3
// Explanation: Alice will be in Rome from August 15 to August 18. Bob will be in Rome from August 16 to August 19. They are both in Rome together on August 16th, 17th, and 18th, so the answer is 3.
//
// Constraints:
// All dates are provided in the format "MM-DD".
// 	Alice and Bob's arrival dates are earlier than or equal to their leaving dates.
// 	The given dates are valid dates of a non-leap year.
//

class Solution {
public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        vector<int> daysInMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        auto dateToDayOfYear = [&](const string& date) {
            int month = stoi(date.substr(0, 2));
            int day = stoi(date.substr(3, 2));
            int dayOfYear = day;
            for (int m = 1; m < month; ++m) {
                dayOfYear += daysInMonth[m - 1];
            }
            return dayOfYear;
        };

        int arriveAliceDay = dateToDayOfYear(arriveAlice);
        int leaveAliceDay = dateToDayOfYear(leaveAlice);
        int arriveBobDay = dateToDayOfYear(arriveBob);
        int leaveBobDay = dateToDayOfYear(leaveBob);

        int startOverlap = max(arriveAliceDay, arriveBobDay);
        int endOverlap = min(leaveAliceDay, leaveBobDay);

        if (startOverlap > endOverlap) {
            return 0;
        }

        return endOverlap - startOverlap + 1;           
    }
};
