// Source: https://leetcode.com/problems/find-palindrome-with-fixed-length/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array queries and a positive integer intLength, return an array answer where answer[i] is either the queries[i]th smallest positive palindrome of length intLength or -1 if no such palindrome exists.
//
// A palindrome is a number that reads the same backwards and forwards. Palindromes cannot have leading zeros.
//
// Example:
// Input: queries = [1,2,3,4,5,90], intLength = 3
// Output: [101,111,121,131,141,999]
// Explanation:
// The first few palindromes of length 3 are:
// 101, 111, 121, 131, 141, 151, 161, 171, 181, 191, 202, ...
// The 90th palindrome of length 3 is 999.
//
// Constraints:
// 1 <= queries.length <= 5 * 104
// 	1 <= queries[i] <= 109
// 	1 <= intLength <= 15
//

class Solution {
    public long[] kthPalindrome(int[] queries, int intLength) {
        int halfLength = (intLength + 1) / 2;
        long start = (long) Math.pow(10, halfLength - 1);
        long end = (long) Math.pow(10, halfLength) - 1;
        long[] result = new long[queries.length];

        for (int i = 0; i < queries.length; i++) {
            long k = queries[i];
            long firstHalf = start + k - 1;

            if (firstHalf > end) {
                result[i] = -1;
            } else {
                StringBuilder sb = new StringBuilder();
                sb.append(firstHalf);
                String secondHalf = sb.reverse().toString();
                if (intLength % 2 == 1) {
                    secondHalf = secondHalf.substring(1);
                }
                sb.reverse().append(secondHalf);
                result[i] = Long.parseLong(sb.toString());
            }
        }

        return result;          
    }
}
