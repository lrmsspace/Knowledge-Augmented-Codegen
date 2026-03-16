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
public:
    vector<long long> kthPalindrome(vector<int>& queries, int intLength) {
        vector<long long> result;
        int halfLength = (intLength + 1) / 2;
        long long start = pow(10, halfLength - 1);
        long long end = pow(10, halfLength) - 1;

        for (int q : queries) {
            long long firstHalf = start + q - 1;
            if (firstHalf > end) {
                result.push_back(-1);
                continue;
            }

            string firstHalfStr = to_string(firstHalf);
            string secondHalfStr = firstHalfStr;
            reverse(secondHalfStr.begin(), secondHalfStr.end());

            if (intLength % 2 == 1) {
                secondHalfStr = secondHalfStr.substr(1);
            }

            string palindromeStr = firstHalfStr + secondHalfStr;
            result.push_back(stoll(palindromeStr));
        }

        return result;          
    }
};
