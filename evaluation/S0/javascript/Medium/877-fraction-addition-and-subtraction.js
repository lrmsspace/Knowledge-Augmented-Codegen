// Source: https://leetcode.com/problems/fraction-addition-and-subtraction/   |   Difficulty: Medium
//
// Problem Description:
// Given a string expression representing an expression of fraction addition and subtraction, return the calculation result in string format.
//
// The final result should be an irreducible fraction. If your final result is an integer, change it to the format of a fraction that has a denominator 1. So in this case, 2 should be converted to 2/1.
//
// Example:
// Input: expression = "-1/2+1/2"
// Output: "0/1"
//
// Constraints:
// The input string only contains '0' to '9', '/', '+' and '-'. So does the output.
// 	Each fraction (input and output) has the format ±numerator/denominator. If the first input fraction or the output is positive, then '+' will be omitted.
// 	The input only contains valid irreducible fractions, where the numerator and denominator of each fraction will always be in the range [1, 10]. If the denominator is 1, it means this fraction is actually an integer in a fraction format defined above.
// 	The number of given fractions will be in the range [1, 10].
// 	The numerator and denominator of the final result are guaranteed to be valid and in the range of 32-bit int.
//

/**
 * @param {string} expression
 * @return {string}
 */
var fractionAddition = function(expression) {
    const gcd = (a, b) => {
        if (b === 0) return a;
        return gcd(b, a % b);
    };

    let numerator = 0;
    let denominator = 1;
    let i = 0;
    const n = expression.length;
    while (i < n) {
        let sign = 1;
        if (expression[i] === '+' || expression[i] === '-') {
            if (expression[i] === '-') sign = -1;
            i++;
        }
        let num = 0;
        while (i < n && expression[i] >= '0' && expression[i] <= '9') {
            num = num * 10 + (expression[i].charCodeAt(0) - '0'.charCodeAt(0));
            i++;
        }
        i++; // skip '/'    
        let denom = 0;
        while (i < n && expression[i] >= '0' && expression[i] <= '9') {
            denom = denom * 10 + (expression[i].charCodeAt(0) - '0'.charCodeAt(0));
            i++;
        }
        numerator = numerator * denom + sign * num * denominator;
        denominator *= denom;
        const g = gcd(Math.abs(numerator), denominator);
        numerator /= g;
        denominator /= g;
    }
    return `${numerator}/${denominator}`;
};
