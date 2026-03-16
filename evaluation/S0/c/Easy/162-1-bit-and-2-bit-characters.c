// Source: https://leetcode.com/problems/1-bit-and-2-bit-characters/   |   Difficulty: Easy
//
// Problem Description:
// We have two special characters:
//
//
// 	The first character can be represented by one bit 0.
// 	The second character can be represented by two bits (10 or 11).
//
//
// Given a binary array bits that ends with 0, return true if the last character must be a one-bit character.
//
// Example:
// Input: bits = [1,0,0]
// Output: true
// Explanation: The only way to decode it is two-bit character and one-bit character.
// So the last character is one-bit character.
//
// Constraints:
// 1 <= bits.length <= 1000
// 	bits[i] is either 0 or 1.
//

bool isOneBitCharacter(int* bits, int bitsSize) {
    int i = 0;
    while (i < bitsSize - 1) {
        if (bits[i] == 1) {
            i += 2;
        } else {
            i += 1;
        }
    }
    return i == bitsSize - 1;       
}
