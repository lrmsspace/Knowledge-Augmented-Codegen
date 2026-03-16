// Source: https://leetcode.com/problems/defuse-the-bomb/   |   Difficulty: Easy
//
// Problem Description:
// You have a bomb to defuse, and your time is running out! Your informer will provide you with a circular array code of length of n and a key k.
//
// To decrypt the code, you must replace every number. All the numbers are replaced simultaneously.
//
//
// 	If k > 0, replace the ith number with the sum of the next k numbers.
// 	If k < 0, replace the ith number with the sum of the previous k numbers.
// 	If k == 0, replace the ith number with 0.
//
//
// As code is circular, the next element of code[n-1] is code[0], and the previous element of code[0] is code[n-1].
//
// Given the circular array code and an integer key k, return the decrypted code to defuse the bomb!
//
// Example:
// Input: code = [5,7,1,4], k = 3
// Output: [12,10,16,13]
// Explanation: Each number is replaced by the sum of the next 3 numbers. The decrypted code is [7+1+4, 1+4+5, 4+5+7, 5+7+1]. Notice that the numbers wrap around.
//
// Constraints:
// n == code.length
// 	1 <= n <= 100
// 	1 <= code[i] <= 100
// 	-(n - 1) <= k <= n - 1
//

class Solution {
    public int[] decrypt(int[] code, int k) {
        int n = code.length;
        int[] result = new int[n];

        for (int i = 0; i < n; i++) {
            int sum = 0;
            if (k > 0) {
                for (int j = 1; j <= k; j++) {
                    sum += code[(i + j) % n];
                }
            } else if (k < 0) {
                for (int j = 1; j <= -k; j++) {
                    sum += code[(i - j + n) % n];
                }
            }
            result[i] = sum;
        }

        return result;          
    }
}
