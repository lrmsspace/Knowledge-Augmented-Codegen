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

long long kMirror(int k, int n) {
    long long sum = 0;
    int count = 0;
    int len = 1;
    while (count < n) {
        int halfLen = (len + 1) / 2;
        int start = 1;
        for (int i = 1; i < halfLen; i++) start *= 10;
        int end = start * 10;
        for (int i = start; i < end && count < n; i++) {
            // Generate palindrome
            long long palin = i;
            int temp = (len % 2 == 0) ? i : i / 10;
            while (temp > 0) {
                palin = palin * 10 + (temp % 10);
                temp /= 10;
            }
            // Check if palin is k-mirror
            long long num = palin;
            long long rev = 0;
            while (num > 0) {
                rev = rev * k + (num % k);
                num /= k;
            }
            if (rev == palin) {
                sum += palin;
                count++;
            }
        }
        len++;
    }
    return sum;     
}
