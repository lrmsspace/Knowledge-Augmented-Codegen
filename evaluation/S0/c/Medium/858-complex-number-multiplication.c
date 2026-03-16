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

char* complexNumberMultiply(char* num1, char* num2) {
    int a, b, c, d;
    sscanf(num1, "%d+%di", &a, &b);
    sscanf(num2, "%d+%di", &c, &d);
    
    int real = a * c - b * d;
    int imag = a * d + b * c;
    
    char* result = (char*)malloc(20 * sizeof(char));
    sprintf(result, "%d+%di", real, imag);
    
    return result;      
}
