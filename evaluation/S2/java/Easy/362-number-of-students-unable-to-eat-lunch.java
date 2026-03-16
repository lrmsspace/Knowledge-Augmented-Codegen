// Source: https://leetcode.com/problems/number-of-students-unable-to-eat-lunch/   |   Difficulty: Easy
//
// Problem Description:
// The school cafeteria offers circular and square sandwiches at lunch break, referred to by numbers 0 and 1 respectively. All students stand in a queue. Each student either prefers square or circular sandwiches.
//
// The number of sandwiches in the cafeteria is equal to the number of students. The sandwiches are placed in a stack. At each step:
//
//
// 	If the student at the front of the queue prefers the sandwich on the top of the stack, they will take it and leave the queue.
// 	Otherwise, they will leave it and go to the queue's end.
//
//
// This continues until none of the queue students want to take the top sandwich and are thus unable to eat.
//
// You are given two integer arrays students and sandwiches where sandwiches[i] is the type of the i​​​​​​th sandwich in the stack (i = 0 is the top of the stack) and students[j] is the preference of the j​​​​​​th student in the initial queue (j = 0 is the front of the queue). Return the number of students that are unable to eat.
//
// Example:
// Input: students = [1,1,0,0], sandwiches = [0,1,0,1]
// Output: 0 
// Explanation:
// - Front student leaves the top sandwich and returns to the end of the line making students = [1,0,0,1].
// - Front student leaves the top sandwich and returns to the end of the line making students = [0,0,1,1].
// - Front student takes the top sandwich and leaves the line making students = [0,1,1] and sandwiches = [1,0,1].
// - Front student leaves the top sandwich and returns to the end of the line making students = [1,1,0].
// - Front student takes the top sandwich and leaves the line making students = [1,0] and sandwiches = [0,1].
// - Front student leaves the top sandwich and returns to the end of the line making students = [0,1].
// - Front student takes the top sandwich and leaves the line making students = [1] and sandwiches = [1].
// - Front student takes the top sandwich and leaves the line making students = [] and sandwiches = [].
// Hence all students are able to eat.
//
// Constraints:
// 1 <= students.length, sandwiches.length <= 100
// 	students.length == sandwiches.length
// 	sandwiches[i] is 0 or 1.
// 	students[i] is 0 or 1.
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
//   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
//   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
//   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
//   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
//   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
// - Check if two segments intersect (geometry, number, simulation)
//   • When to use: Use this when determining if two line segments in a 2D plane share any common points, especially when floating-point precision issues need to be avoided.
//   • Idea: This algorithm determines if two line segments intersect by handling collinear and non-collinear cases separately, primarily using integer arithmetic to avoid precision errors. It typically runs in O(1) time.
//   • Invariants: If segments are collinear, their 1D projections on both axes must overlap for intersection.; If segments are not collinear, each segment's endpoints must lie on opposite sides of the line containing the other segment.
//   • Tips: Handle collinear segments as a distinct special case.; Utilize cross products for efficient orientation checks.
//   • Pitfalls: Failing to correctly identify and handle collinear segments.; Introducing floating-point errors by using division for slopes.
// - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, two-pointers)
//   • When to use: When efficiently searching for all occurrences of a pattern string within a larger text string, or when computing the longest proper prefix of a string that is also a suffix for all its prefixes.
//   • Idea: The KMP algorithm efficiently finds all occurrences of a pattern within a text by pre-processing the pattern to build a prefix function (LPS array), which avoids redundant character comparisons. It achieves a time complexity of O(N + M) for text length N and pattern length M.
//   • Invariants: The prefix function array `pi` stores for each `i` the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation for `pi[i]`, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix of `s[0...i-1]`.
//   • Tips: Precompute the prefix function (LPS array) for the pattern to guide shifts.; Use two pointers: one for the text (or current character in pattern for prefix function), one for the pattern (or length of matched prefix).
//   • Pitfalls: Incorrectly calculating or using the prefix function values, leading to wrong shifts.; Off-by-one errors when indexing or shifting pointers, especially at boundaries.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int countStudents(int[] students, int[] sandwiches) {
        int count0 = 0, count1 = 0;
        for (int student : students) {
            if (student == 0) {
                count0++;
            } else {
                count1++;
            }
        }

        for (int sandwich : sandwiches) {
            if (sandwich == 0 && count0 > 0) {
                count0--;
            } else if (sandwich == 1 && count1 > 0) {
                count1--;
            } else {
                break;
            }
        }

        return count0 + count1;         
    }
}
