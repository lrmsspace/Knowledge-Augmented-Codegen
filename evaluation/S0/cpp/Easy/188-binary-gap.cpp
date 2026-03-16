// Source: https://leetcode.com/problems/binary-gap/   |   Difficulty: Easy
//
// Problem Description:
// Given a positive integer n, find and return the longest distance between any two adjacent 1's in the binary representation of n. If there are no two adjacent 1's, return 0.
//
// Two 1's are adjacent if there are only 0's separating them (possibly no 0's). The distance between two 1's is the absolute difference between their bit positions. For example, the two 1's in "1001" have a distance of 3.
//
// Example:
// Input: n = 22
// Output: 2
// Explanation: 22 in binary is "10110".
// The first adjacent pair of 1's is "10110" with a distance of 2.
// The second adjacent pair of 1's is "10110" with a distance of 1.
// The answer is the largest of these two distances, which is 2.
// Note that "10110" is not a valid pair since there is a 1 separating the two 1's underlined.
//
// Constraints:
// 1 <= n <= 109
//

class Solution {
public:
    int binaryGap(int n) {
        int prev = -1;
        int ans = 0;
        for (int i = 0; n > 0; ++i, n >>= 1) {
            if (n & 1) {
                if (prev != -1) {
                    ans = std::max(ans, i - prev);
                }
                prev = i;
            }
        }
        return ans;         
    }
};
