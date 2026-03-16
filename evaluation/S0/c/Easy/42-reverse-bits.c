// Source: https://leetcode.com/problems/reverse-bits/   |   Difficulty: Easy
//
// Problem Description:
// Reverse bits of a given 32 bits signed integer.
//
// Example:
// Input: n = 43261596
//
// Output: 964176192
//
// Explanation:
//
//
// 	
// 		
// 			Integer
// 			Binary
// 		
// 		
// 			43261596
// 			00000010100101000001111010011100
// 		
// 		
// 			964176192
// 			00111001011110000010100101000000
//
// Constraints:
// 0 <= n <= 231 - 2
// 	n is even.
//
//
//  
// Follow up: If this function is called many times, how would you optimize it?
//

int reverseBits(int n) {
    int result = 0;
    for (int i = 0; i < 32; i++) {
        result <<= 1;          // Shift result to the left to make space for the next bit
        result |= (n & 1);    // Add the least significant bit of n to result
        n >>= 1;              // Shift n to the right to process the next bit
    }
    return result;      
}
