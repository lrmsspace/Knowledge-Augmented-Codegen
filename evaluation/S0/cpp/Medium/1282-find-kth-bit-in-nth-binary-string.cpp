// Source: https://leetcode.com/problems/find-kth-bit-in-nth-binary-string/   |   Difficulty: Medium
//
// Problem Description:
// Given two positive integers n and k, the binary string Sn is formed as follows:
//
//
// 	S1 = "0"
// 	Si = Si - 1 + "1" + reverse(invert(Si - 1)) for i > 1
//
//
// Where + denotes the concatenation operation, reverse(x) returns the reversed string x, and invert(x) inverts all the bits in x (0 changes to 1 and 1 changes to 0).
//
// For example, the first four strings in the above sequence are:
//
//
// 	S1 = "0"
// 	S2 = "011"
// 	S3 = "0111001"
// 	S4 = "011100110110001"
//
//
// Return the kth bit in Sn. It is guaranteed that k is valid for the given n.
//
// Example:
// Input: n = 3, k = 1
// Output: "0"
// Explanation: S3 is "0111001".
// The 1st bit is "0".
//
// Constraints:
// 1 <= n <= 20
// 	1 <= k <= 2n - 1
//

class Solution {
public:
    char findKthBit(int n, int k) {
        if (n == 1) {
            return '0';
        }
        
        int mid = 1 << (n - 1); // Length of Sn is 2^n - 1, mid is the position of the middle '1'
        
        if (k == mid) {
            return '1';
        } else if (k < mid) {
            return findKthBit(n - 1, k);
        } else {
            // Find the mirrored position in Sn-1
            int mirroredPos = mid - (k - mid);
            char mirroredBit = findKthBit(n - 1, mirroredPos);
            return mirroredBit == '0' ? '1' : '0'; // Invert the bit
        }           
    }
};
