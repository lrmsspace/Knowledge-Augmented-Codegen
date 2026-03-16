// Source: https://leetcode.com/problems/angle-between-hands-of-a-clock/   |   Difficulty: Medium
//
// Problem Description:
// Given two numbers, hour and minutes, return the smaller angle (in degrees) formed between the hour and the minute hand.
//
// Answers within 10-5 of the actual value will be accepted as correct.
//
// Example:
// Input: hour = 12, minutes = 30
// Output: 165
//
// Constraints:
// 1 <= hour <= 12
// 	0 <= minutes <= 59
//

class Solution {
public:
    double angleClock(int hour, int minutes) {
        double minuteAngle = minutes * 6.0; // Each minute represents 6 degrees (360/60)
        double hourAngle = (hour % 12) * 30.0 + (minutes / 60.0) * 30.0; // Each hour represents 30 degrees (360/12) plus minute contribution

        double angle = fabs(hourAngle - minuteAngle);
        return min(angle, 360.0 - angle); // Return the smaller angle           
    }
};
