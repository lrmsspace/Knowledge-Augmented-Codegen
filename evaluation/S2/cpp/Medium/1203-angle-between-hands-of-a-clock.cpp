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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    double angleClock(int hour, int minutes) {
        // Calculate the angle of the hour hand
        double hourAngle = (hour % 12) * 30 + (minutes / 60.0) * 30;
        // Calculate the angle of the minute hand
        double minuteAngle = minutes * 6;

        // Calculate the absolute difference between the two angles
        double angle = abs(hourAngle - minuteAngle);

        // Return the smaller angle
        return min(angle, 360 - angle);         
    }
};
