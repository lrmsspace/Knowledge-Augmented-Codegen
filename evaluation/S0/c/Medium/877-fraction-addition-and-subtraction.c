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

char* fractionAddition(char* expression) {
    int numerator = 0, denominator = 1;
    char *p = expression;
    
    while (*p) {
        int sign = 1;
        if (*p == '+' || *p == '-') {
            if (*p == '-') sign = -1;
            p++;
        }
        
        int num = 0;
        while (*p >= '0' && *p <= '9') {
            num = num * 10 + (*p - '0');
            p++;
        }
        
        p++; // skip '/'
        
        int denom = 0;
        while (*p >= '0' && *p <= '9') {
            denom = denom * 10 + (*p - '0');
            p++;
        }
        
        numerator = numerator * denom + sign * num * denominator;
        denominator *= denom;
        
        // Reduce the fraction
        int gcd = 1, a = abs(numerator), b = denominator;
        while (b) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        gcd = a;
        
        numerator /= gcd;
        denominator /= gcd;
    }
    
    // Allocate result string
    char *result = (char *)malloc(20 * sizeof(char));
    sprintf(result, "%d/%d", numerator, denominator);
    
    return result;      
}
