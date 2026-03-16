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
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* intToRoman(int num) {
    // Define the mapping of integers to Roman numerals
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char* symbols[] = {
        "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"
    };

    // Allocate enough space for the result (maximum length for 3999 is 15)
    char* roman = (char*)malloc(16 * sizeof(char));
    roman[0] = '\0'; // Initialize as empty string

    int i = 0;
    while (num > 0) {
        while (num >= values[i]) {
            strcat(roman, symbols[i]);
            num -= values[i];
        }
        i++;
    }

    return roman;       
}
