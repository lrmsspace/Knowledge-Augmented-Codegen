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
// - Minimum Enclosing Circle (geometry, number, simulation)
//   • When to use: When you need to find the smallest circle that contains all given points in a 2D plane, often with a requirement for expected linear time complexity.
//   • Idea: This algorithm iteratively constructs the Minimum Enclosing Circle (MEC) by considering points one by one, potentially updating the circle if a new point lies outside. It achieves an expected linear time complexity, O(N), through randomization.
//   • Invariants: The current circle C is the MEC for the subset of points processed so far.; If C is defined by 1 point p_i, it is the MEC of points processed so far that passes through p_i.
//   • Tips: Randomly shuffle input points to achieve expected linear time complexity.; The Minimum Enclosing Circle is always defined by 2 or 3 points on its boundary.
//   • Pitfalls: A naive implementation without randomization can lead to O(N^3) worst-case time complexity.; Floating-point precision issues can arise in geometric calculations, requiring careful handling.
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool isRobotBounded(char* instructions) {
    // Directions: North, East, South, West
    int dirX[] = {0, 1, 0, -1};
    int dirY[] = {1, 0, -1, 0};
    
    int x = 0, y = 0; // Robot's position
    int dir = 0;      // Robot's direction index (0: North)
    
    for (int i = 0; instructions[i] != '\0'; i++) {
        char instruction = instructions[i];
        
        if (instruction == 'G') {
            x += dirX[dir];
            y += dirY[dir];
        } else if (instruction == 'L') {
            dir = (dir + 3) % 4; // Turn left
        } else if (instruction == 'R') {
            dir = (dir + 1) % 4; // Turn right
        }
    }
    
    // The robot is bounded in a circle if it returns to the origin
    // or it doesn't face north after one cycle of instructions.
    return (x == 0 && y == 0) || (dir != 0);        
}
