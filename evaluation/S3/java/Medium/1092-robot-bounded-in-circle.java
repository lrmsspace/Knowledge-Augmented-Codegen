// Source: https://leetcode.com/problems/robot-bounded-in-circle/   |   Difficulty: Medium
//
// Problem Description:
// On an infinite plane, a robot initially stands at (0, 0) and faces north. Note that:
//
//
// 	The north direction is the positive direction of the y-axis.
// 	The south direction is the negative direction of the y-axis.
// 	The east direction is the positive direction of the x-axis.
// 	The west direction is the negative direction of the x-axis.
//
//
// The robot can receive one of three instructions:
//
//
// 	"G": go straight 1 unit.
// 	"L": turn 90 degrees to the left (i.e., anti-clockwise direction).
// 	"R": turn 90 degrees to the right (i.e., clockwise direction).
//
//
// The robot performs the instructions given in order, and repeats them forever.
//
// Return true if and only if there exists a circle in the plane such that the robot never leaves the circle.
//
// Example:
// Input: instructions = "GGLLGG"
// Output: true
// Explanation: The robot is initially at (0, 0) facing the north direction.
// "G": move one step. Position: (0, 1). Direction: North.
// "G": move one step. Position: (0, 2). Direction: North.
// "L": turn 90 degrees anti-clockwise. Position: (0, 2). Direction: West.
// "L": turn 90 degrees anti-clockwise. Position: (0, 2). Direction: South.
// "G": move one step. Position: (0, 1). Direction: South.
// "G": move one step. Position: (0, 0). Direction: South.
// Repeating the instructions, the robot goes into the cycle: (0, 0) --> (0, 1) --> (0, 2) --> (0, 1) --> (0, 0).
// Based on that, we return true.
//
// Constraints:
// 1 <= instructions.length <= 100
// 	instructions[i] is 'G', 'L' or, 'R'.
//
// Helpful references (internal KB):
// - Check if two segments intersect (geometry, number, simulation)
//   • When to use: Use this when determining if two line segments in a 2D plane share any common points, especially when floating-point precision issues need to be avoided.
//   • Idea: This algorithm determines if two line segments intersect by handling collinear and non-collinear cases separately, primarily using integer arithmetic to avoid precision errors. It typically runs in O(1) time.
//   • Invariants: If segments are collinear, their 1D projections on both axes must overlap for intersection.; If segments are not collinear, each segment's endpoints must lie on opposite sides of the line containing the other segment.
//   • Tips: Handle collinear segments as a distinct special case.; Utilize cross products for efficient orientation checks.
//   • Pitfalls: Failing to correctly identify and handle collinear segments.; Introducing floating-point errors by using division for slopes.
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
//   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
//   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
//   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
//   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
//   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean isRobotBounded(String instructions) {
        // Directions: 0 = north, 1 = east, 2 = south, 3 = west
        int x = 0, y = 0, direction = 0;

        for (char instruction : instructions.toCharArray()) {
            if (instruction == 'G') {
                if (direction == 0) y++;       // Move north
                else if (direction == 1) x++;  // Move east
                else if (direction == 2) y--;  // Move south
                else if (direction == 3) x--;  // Move west
            } else if (instruction == 'L') {
                direction = (direction + 3) % 4; // Turn left
            } else if (instruction == 'R') {
                direction = (direction + 1) % 4; // Turn right
            }
        }

        // The robot is bounded in a circle if it returns to the origin or it doesn't face north after one cycle of instructions.
        return (x == 0 && y == 0) || direction != 0;            
    }
}
