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
    public String abbreviateProduct(int left, int right) {
        long mod = 100000L;
        long suffix = 1L;
        int count2 = 0, count5 = 0;
        double logSum = 0.0;

        for (int i = left; i <= right; i++) {
            int num = i;

            while (num % 2 == 0) {
                count2++;
                num /= 2;
            }
            while (num % 5 == 0) {
                count5++;
                num /= 5;
            }

            suffix = (suffix * (num % mod)) % mod;
            logSum += Math.log10(i);
        }

        int trailingZeros = Math.min(count2, count5);
        count2 -= trailingZeros;
        count5 -= trailingZeros;

        for (int i = 0; i < count2; i++) {
            suffix = (suffix * 2) % mod;
        }
        for (int i = 0; i < count5; i++) {
            suffix = (suffix * 5) % mod;
        }

        logSum -= trailingZeros * Math.log10(10);
        int totalDigits = (int) Math.floor(logSum) + 1;

        String suffixStr = String.format("%05d", suffix);
        if (totalDigits <= 10) {
            return suffixStr.substring(suffixStr.length() - totalDigits) + "e" + trailingZeros;
        } else {
            double fractionalPart = logSum - Math.floor(logSum);
            double leadingNum = Math.pow(10, fractionalPart + 4);
            String leadingStr = String.valueOf((int) leadingNum);
            return leadingStr + "..." + suffixStr + "e" + trailingZeros;
        }           
    }
}
