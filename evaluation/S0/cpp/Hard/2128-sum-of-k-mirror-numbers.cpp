// Source: https://leetcode.com/problems/sum-of-k-mirror-numbers/   |   Difficulty: Hard
//
// Problem Description:
// A k-mirror number is a positive integer without leading zeros that reads the same both forward and backward in base-10 as well as in base-k.
//
//
// 	For example, 9 is a 2-mirror number. The representation of 9 in base-10 and base-2 are 9 and 1001 respectively, which read the same both forward and backward.
// 	On the contrary, 4 is not a 2-mirror number. The representation of 4 in base-2 is 100, which does not read the same both forward and backward.
//
//
// Given the base k and the number n, return the sum of the n smallest k-mirror numbers.
//
// Example:
// Input: k = 2, n = 5
// Output: 25
// Explanation:
// The 5 smallest 2-mirror numbers and their representations in base-2 are listed as follows:
//   base-10    base-2
//     1          1
//     3          11
//     5          101
//     7          111
//     9          1001
// Their sum = 1 + 3 + 5 + 7 + 9 = 25.
//
// Constraints:
// 2 <= k <= 9
// 	1 <= n <= 30
//

class Solution {
public:
    long long kMirror(int k, int n) {
        long long result = 0;
        int count = 0;
        int length = 1;
        
        while (count < n) {
            // Generate palindromic numbers of current length
            int halfLen = (length + 1) / 2;
            int start = pow(10, halfLen - 1);
            int end = pow(10, halfLen);
            
            for (int i = start; i < end && count < n; i++) {
                string half = to_string(i);
                string palinStr = half;
                
                // Create full palindrome
                if (length % 2 == 1) {
                    reverse(half.begin(), half.end() - 1);
                } else {
                    reverse(half.begin(), half.end());
                }
                palinStr += half;
                
                long long palinNum = stoll(palinStr);
                
                // Check if palinNum is k-mirror
                if (isKMirror(palinNum, k)) {
                    result += palinNum;
                    count++;
                }
            }
            
            length++;
        }
        
        return result;          
    }
};
