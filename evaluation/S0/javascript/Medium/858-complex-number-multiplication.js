// Source: https://leetcode.com/problems/complex-number-multiplication/   |   Difficulty: Medium
//
// Problem Description:
// A complex number can be represented as a string on the form "real+imaginaryi" where:
//
//
// 	real is the real part and is an integer in the range [-100, 100].
// 	imaginary is the imaginary part and is an integer in the range [-100, 100].
// 	i2 == -1.
//
//
// Given two complex numbers num1 and num2 as strings, return a string of the complex number that represents their multiplications.
//
// Example:
// Input: num1 = "1+1i", num2 = "1+1i"
// Output: "0+2i"
// Explanation: (1 + i) * (1 + i) = 1 + i2 + 2 * i = 2i, and you need convert it to the form of 0+2i.
//
// Constraints:
// num1 and num2 are valid complex numbers.
//

/**
 * @param {string} num1
 * @param {string} num2
 * @return {string}
 */
var complexNumberMultiply = function(num1, num2) {
    const parseComplex = (num) => {
        const [real, imaginary] = num.split('+');
        return [parseInt(real), parseInt(imaginary.slice(0, -1))];
    };

    const [a, b] = parseComplex(num1);
    const [c, d] = parseComplex(num2);
    const realPart = a * c - b * d;
    const imaginaryPart = a * d + b * c;
    return `${realPart}+${imaginaryPart}i`;
};
