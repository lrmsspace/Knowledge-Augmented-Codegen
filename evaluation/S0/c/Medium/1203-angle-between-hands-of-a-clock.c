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

double angleClock(int hour, int minutes) {
    // Calculate the angle of the minute hand from 12 o'clock
    double minute_angle = minutes * 6.0; // 360 degrees / 60 minutes = 6 degrees per minute

    // Calculate the angle of the hour hand from 12 o'clock
    double hour_angle = (hour % 12) * 30.0 + (minutes / 60.0) * 30.0; // 360 degrees / 12 hours = 30 degrees per hour

    // Calculate the absolute difference between the two angles
    double angle_diff = fabs(hour_angle - minute_angle);

    // The smaller angle between the two hands
    return fmin(angle_diff, 360.0 - angle_diff);        
}
