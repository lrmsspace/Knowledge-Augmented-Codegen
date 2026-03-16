// Source: https://leetcode.com/problems/categorize-box-according-to-criteria/   |   Difficulty: Easy
//
// Problem Description:
// Given four integers length, width, height, and mass, representing the dimensions and mass of a box, respectively, return a string representing the category of the box.
//
//
// 	The box is "Bulky" if:
//
// 	
// 		Any of the dimensions of the box is greater or equal to 104.
// 		Or, the volume of the box is greater or equal to 109.
// 	
// 	
// 	If the mass of the box is greater or equal to 100, it is "Heavy".
// 	If the box is both "Bulky" and "Heavy", then its category is "Both".
// 	If the box is neither "Bulky" nor "Heavy", then its category is "Neither".
// 	If the box is "Bulky" but not "Heavy", then its category is "Bulky".
// 	If the box is "Heavy" but not "Bulky", then its category is "Heavy".
//
//
// Note that the volume of the box is the product of its length, width and height.
//
// Example:
// Input: length = 1000, width = 35, height = 700, mass = 300
// Output: "Heavy"
// Explanation: 
// None of the dimensions of the box is greater or equal to 104. 
// Its volume = 24500000 <= 109. So it cannot be categorized as "Bulky".
// However mass >= 100, so the box is "Heavy".
// Since the box is not "Bulky" but "Heavy", we return "Heavy".
//
// Constraints:
// 1 <= length, width, height <= 105
// 	1 <= mass <= 103
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

char* categorizeBox(int length, int width, int height, int mass) {
    // Check if the box is "Bulky"
    int isBulky = (length >= 104 || width >= 104 || height >= 104) || ((long long)length * width * height >= 1000000000);
    
    // Check if the box is "Heavy"
    int isHeavy = (mass >= 100);
    
    // Determine the category of the box
    if (isBulky && isHeavy) {
        return "Both";
    } else if (isBulky) {
        return "Bulky";
    } else if (isHeavy) {
        return "Heavy";
    } else {
        return "Neither";
    }       
}
