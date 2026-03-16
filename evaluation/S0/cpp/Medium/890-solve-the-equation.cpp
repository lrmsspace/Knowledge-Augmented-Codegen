// Source: https://leetcode.com/problems/solve-the-equation/   |   Difficulty: Medium
//
// Problem Description:
// Solve a given equation and return the value of 'x' in the form of a string "x=#value". The equation contains only '+', '-' operation, the variable 'x' and its coefficient. You should return "No solution" if there is no solution for the equation, or "Infinite solutions" if there are infinite solutions for the equation.
//
// If there is exactly one solution for the equation, we ensure that the value of 'x' is an integer.
//
// Example:
// Input: equation = "x+5-3+x=6+x-2"
// Output: "x=2"
//
// Constraints:
// 3 <= equation.length <= 1000
// 	equation has exactly one '='.
// 	equation consists of integers with an absolute value in the range [0, 100] without any leading zeros, and the variable 'x'.
// 	The input is generated that if there is a single solution, it will be an integer.
//

class Solution {
public:
    string solveEquation(string equation) {
        int coeffX = 0; // Coefficient of x
        int constant = 0; // Constant term
        int sign = 1; // Current sign
        int n = equation.size();
        int i = 0;
        bool leftSide = true; // Flag to indicate which side of the equation we are on

        while (i < n) {
            if (equation[i] == '=') {
                leftSide = false;
                sign = 1; // Reset sign for the right side
                i++;
                continue;
            }

            if (equation[i] == '+') {
                sign = 1;
                i++;
            } else if (equation[i] == '-') {
                sign = -1;
                i++;
            }

            int num = 0;
            bool isNumber = false;

            while (i < n && isdigit(equation[i])) {
                num = num * 10 + (equation[i] - '0');
                i++;
                isNumber = true;
            }

            if (i < n && equation[i] == 'x') {
                if (!isNumber) num = 1; // Implicit coefficient of x
                coeffX += (leftSide ? sign : -sign) * num;
                i++;
            } else {
                constant += (leftSide ? -sign : sign) * num;
            }
        }

        if (coeffX == 0) {
            if (constant == 0) return "Infinite solutions";
            else return "No solution";
        }

        int result = constant / coeffX;
        return "x=" + to_string(result);            
    }
};
