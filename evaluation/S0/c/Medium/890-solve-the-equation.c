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

char* solveEquation(char* equation) {
    int coeff_x = 0; // Coefficient of x
    int constant = 0; // Constant term
    int sign = 1; // Current sign
    int side = 1; // Left side of the equation

    int i = 0;
    int n = strlen(equation);

    while (i < n) {
        if (equation[i] == '=') {
            side = -1; // Switch to right side
            sign = 1; // Reset sign for new side
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
        int has_num = 0;

        while (i < n && isdigit(equation[i])) {
            num = num * 10 + (equation[i] - '0');
            i++;
            has_num = 1;
        }

        if (i < n && equation[i] == 'x') {
            if (!has_num) num = 1; // Implicit coefficient of x
            coeff_x += side * sign * num;
            i++;
        } else {
            constant += side * sign * num;
        }
    }

    if (coeff_x == 0) {
        if (constant == 0) {
            return "Infinite solutions";
        } else {
            return "No solution";
        }
    } else {
        int result = -constant / coeff_x;
        static char buffer[20];
        sprintf(buffer, "x=%d", result);
        return buffer;
    }       
}
