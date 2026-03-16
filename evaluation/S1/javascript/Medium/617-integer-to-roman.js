// Source: https://leetcode.com/problems/integer-to-roman/   |   Difficulty: Medium
//
// Problem Description:
// Seven different symbols represent Roman numerals with the following values:
//
//
// 	
// 		
// 			Symbol
// 			Value
// 		
// 	
// 	
// 		
// 			I
// 			1
// 		
// 		
// 			V
// 			5
// 		
// 		
// 			X
// 			10
// 		
// 		
// 			L
// 			50
// 		
// 		
// 			C
// 			100
// 		
// 		
// 			D
// 			500
// 		
// 		
// 			M
// 			1000
// 		
// 	
//
//
// Roman numerals are formed by appending the conversions of decimal place values from highest to lowest. Converting a decimal place value into a Roman numeral has the following rules:
//
//
// 	If the value does not start with 4 or 9, select the symbol of the maximal value that can be subtracted from the input, append that symbol to the result, subtract its value, and convert the remainder to a Roman numeral.
// 	If the value starts with 4 or 9 use the subtractive form representing one symbol subtracted from the following symbol, for example, 4 is 1 (I) less than 5 (V): IV and 9 is 1 (I) less than 10 (X): IX. Only the following subtractive forms are used: 4 (IV), 9 (IX), 40 (XL), 90 (XC), 400 (CD) and 900 (CM).
// 	Only powers of 10 (I, X, C, M) can be appended consecutively at most 3 times to represent multiples of 10. You cannot append 5 (V), 50 (L), or 500 (D) multiple times. If you need to append a symbol 4 times use the subtractive form.
//
//
// Given an integer, convert it to a Roman numeral.
//
// Example:
// Input: num = 3749
//
// Output: "MMMDCCXLIX"
//
// Explanation:
//
//
// 3000 = MMM as 1000 (M) + 1000 (M) + 1000 (M)
//  700 = DCC as 500 (D) + 100 (C) + 100 (C)
//   40 = XL as 10 (X) less of 50 (L)
//    9 = IX as 1 (I) less of 10 (X)
// Note: 49 is not 1 (I) less of 50 (L) because the conversion is based on decimal places
//
// Constraints:
// 1 <= num <= 3999
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} num
 * @return {string}
 */
var intToRoman = function(num) {
    const val = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1];
    const syms = ["M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"];

    let roman = '';
    for (let i = 0; i < val.length; i++) {
        while (num >= val[i]) {
            num -= val[i];
            roman += syms[i];
        }
    }
    return roman;
};
