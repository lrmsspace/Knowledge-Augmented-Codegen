// Source: https://leetcode.com/problems/abbreviating-the-product-of-a-range/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integers left and right with left <= right. Calculate the product of all integers in the inclusive range [left, right].
//
// Since the product may be very large, you will abbreviate it following these steps:
//
//
// 	Count all trailing zeros in the product and remove them. Let us denote this count as C.
//
// 	
// 		For example, there are 3 trailing zeros in 1000, and there are 0 trailing zeros in 546.
// 	
// 	
// 	Denote the remaining number of digits in the product as d. If d > 10, then express the product as <pre>...<suf> where <pre> denotes the first 5 digits of the product, and <suf> denotes the last 5 digits of the product after removing all trailing zeros. If d <= 10, we keep it unchanged.
// 	
// 		For example, we express 1234567654321 as 12345...54321, but 1234567 is represented as 1234567.
// 	
// 	
// 	Finally, represent the product as a string "<pre>...<suf>eC".
// 	
// 		For example, 12345678987600000 will be represented as "12345...89876e5".
// 	
// 	
//
//
// Return a string denoting the abbreviated product of all integers in the inclusive range [left, right].
//
// Example:
// Input: left = 1, right = 4
// Output: "24e0"
// Explanation: The product is 1 × 2 × 3 × 4 = 24.
// There are no trailing zeros, so 24 remains the same. The abbreviation will end with "e0".
// Since the number of digits is 2, which is less than 10, we do not have to abbreviate it further.
// Thus, the final representation is "24e0".
//
// Constraints:
// 1 <= left <= right <= 104
//

class Solution {
public:
    string abbreviateProduct(int left, int right) {
        long long trailingZeros = 0;
        double logSum = 0.0;
        long long mod = 100000;  // to keep last 5 digits
        long long lastFive = 1;
        
        for (int i = left; i <= right; i++) {
            int num = i;
            
            // Count factors of 2 and 5 for trailing zeros
            while (num % 2 == 0) {
                trailingZeros++;
                num /= 2;
            }
            while (num % 5 == 0) {
                trailingZeros++;
                num /= 5;
            }
            
            logSum += log10(i);
            lastFive = (lastFive * (i % mod)) % mod;
        }
        
        // Calculate number of digits
        long long totalDigits = (long long)logSum + 1;
        
        string prefix, suffix;
        
        if (totalDigits <= 10) {
            // Calculate full product modulo to get exact digits
            long long product = 1;
            for (int i = left; i <= right; i++) {
                product = (product * i) % 10000000000LL; // keep last 10 digits
            }
            prefix = to_string(product);
            suffix = "";
        } else {
            // Get first 5 digits using logarithm
            double fractionalPart = logSum - floor(logSum);
            double firstFiveVal = pow(10, fractionalPart + 4); // +4 to get first 5 digits
            int firstFiveInt = (int)firstFiveVal;
            prefix = to_string(firstFiveInt);
            
            // Get last 5 digits
            suffix = to_string(lastFive);
            while (suffix.length() < 5) suffix = "0" + suffix; // pad with zeros if needed
        }
        
        return prefix + "..." + suffix + "e" + to_string(trailingZeros);            
    }
};
