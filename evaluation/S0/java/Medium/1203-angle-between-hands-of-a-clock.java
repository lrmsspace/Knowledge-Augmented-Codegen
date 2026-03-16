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
    public double angleClock(int hour, int minutes) {
        // Calculate the angle of the minute hand from 12 o'clock
        double minuteAngle = minutes * 6; // 360 degrees / 60 minutes = 6 degrees per minute

        // Calculate the angle of the hour hand from 12 o'clock
        double hourAngle = (hour % 12) * 30 + (minutes / 60.0) * 30; // 360 degrees / 12 hours = 30 degrees per hour

        // Find the difference between the two angles
        double angleDifference = Math.abs(hourAngle - minuteAngle);

        // The smaller angle between the two hands
        return Math.min(angleDifference, 360 - angleDifference);            
    }
}
