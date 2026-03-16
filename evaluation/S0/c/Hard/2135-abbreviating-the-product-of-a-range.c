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

char* abbreviateProduct(int left, int right) {
    int64_t mod = 100000LL;
    int64_t prefix = 1LL;
    int trailingZeros = 0;
    double logSum = 0.0;

    for (int i = left; i <= right; ++i) {
        int num = i;
        while (num % 10 == 0) {
            trailingZeros++;
            num /= 10;
        }
        while (num % 2 == 0) {
            num /= 2;
            trailingZeros++;
        }
        while (num % 5 == 0) {
            num /= 5;
            trailingZeros++;
        }
        prefix = (prefix * (num % mod)) % mod;
        logSum += log10((double)i);
    }

    int totalDigits = (int)logSum + 1;
    char *result = (char *)malloc(32 * sizeof(char));
    if (totalDigits <= 10) {
        snprintf(result, 32, "%llde%d", prefix, trailingZeros);
    } else {
        double fractionalPart = logSum - (int)logSum;
        double firstFiveDigitsDouble = pow(10.0, fractionalPart + 4);
        int firstFiveDigits = (int)firstFiveDigitsDouble;

        snprintf(result, 32, "%05de%lld...%05d", firstFiveDigits, trailingZeros, (int)(prefix % mod));
    }

    return result;      
}
