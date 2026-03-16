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

/**
 * @param {string} equation
 * @return {string}
 */
var solveEquation = function(equation) {
    const [left, right] = equation.split('=');

    const parseSide = (side) => {
        let xCoeff = 0;
        let constant = 0;
        let i = 0;
        let sign = 1;
        while (i < side.length) {
            if (side[i] === '+') {
                sign = 1;
                i++;
            } else if (side[i] === '-') {
                sign = -1;
                i++;
            } else {
                let start = i;
                while (i < side.length && side[i] !== '+' && side[i] !== '-') {
                    i++;
                }
                const token = side.slice(start, i);
                if (token.includes('x')) {
                    const coeff = token === 'x' ? 1 : parseInt(token);
                    xCoeff += sign * coeff;
                } else {
                    constant += sign * parseInt(token);
                }
            }
        }
        return [xCoeff, constant];
    };

    const [leftX, leftConst] = parseSide(left);
    const [rightX, rightConst] = parseSide(right);

    const xCoeff = leftX - rightX;
    const constant = rightConst - leftConst;

    if (xCoeff === 0) {
        if (constant === 0) {
            return "Infinite solutions";
        } else {
            return "No solution";
        }
    }

    return "x=" + (constant / xCoeff);
};