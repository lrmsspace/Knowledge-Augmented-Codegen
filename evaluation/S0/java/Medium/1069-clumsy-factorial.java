// Source: https://leetcode.com/problems/clumsy-factorial/   |   Difficulty: Medium
//
// Problem Description:
// The factorial of a positive integer n is the product of all positive integers less than or equal to n.
//
//
// 	For example, factorial(10) = 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1.
//
//
// We make a clumsy factorial using the integers in decreasing order by swapping out the multiply operations for a fixed rotation of operations with multiply '*', divide '/', add '+', and subtract '-' in this order.
//
//
// 	For example, clumsy(10) = 10 * 9 / 8 + 7 - 6 * 5 / 4 + 3 - 2 * 1.
//
//
// However, these operations are still applied using the usual order of operations of arithmetic. We do all multiplication and division steps before any addition or subtraction steps, and multiplication and division steps are processed left to right.
//
// Additionally, the division that we use is floor division such that 10 * 9 / 8 = 90 / 8 = 11.
//
// Given an integer n, return the clumsy factorial of n.
//
// Example:
// Input: n = 4
// Output: 7
// Explanation: 7 = 4 * 3 / 2 + 1
//
// Constraints:
// 1 <= n <= 104
//

class Solution {
    public int clumsy(int n) {
        int result = 0;
        int sign = 1; // Used to alternate between addition and subtraction
        int index = 0; // To track the operation: 0->*, 1->/, 2->+, 3->-

        int current = n;
        n--;

        while (n > 0) {
            if (index % 4 == 0) { // Multiplication
                current *= n;
            } else if (index % 4 == 1) { // Division
                current /= n;
            } else if (index % 4 == 2) { // Addition
                result += sign * current;
                current = n; // Reset current to the next number
                sign = 1; // Next operation is addition
            } else if (index % 4 == 3) { // Subtraction
                result += sign * current;
                current = n; // Reset current to the next number
                sign = -1; // Next operation is subtraction
            }
            index++;
            n--;
        }

        result += sign * current; // Add the last computed value
        return result;          
    }
}
