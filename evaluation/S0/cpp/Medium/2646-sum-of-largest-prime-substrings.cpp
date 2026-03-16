// Source: https://leetcode.com/problems/sum-of-largest-prime-substrings/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, find the sum of the 3 largest unique prime numbers that can be formed using any of its substrings.
//
// Return the sum of the three largest unique prime numbers that can be formed. If fewer than three exist, return the sum of all available primes. If no prime numbers can be formed, return 0.
//
// Note: Each prime number should be counted only once, even if it appears in multiple substrings. Additionally, when converting a substring to an integer, any leading zeros are ignored.
//
// Example:
// Input: s = "12234"
//
// Output: 1469
//
// Explanation:
//
//
// 	The unique prime numbers formed from the substrings of "12234" are 2, 3, 23, 223, and 1223.
// 	The 3 largest primes are 1223, 223, and 23. Their sum is 1469.
//
// Constraints:
// 1 <= s.length <= 10
// 	s consists of only digits.
//

class Solution {
public:
    long long sumOfLargestPrimes(string s) {
        unordered_set<int> primes;
        int n = s.size();

        // Generate all substrings and check for primality
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                string sub = s.substr(i, j - i + 1);
                int num = stoi(sub);
                if (isPrime(num)) {
                    primes.insert(num);
                }
            }
        }

        // Get the three largest unique primes
        vector<int> primeList(primes.begin(), primes.end());
        sort(primeList.rbegin(), primeList.rend());

        long long sum = 0;
        for (int i = 0; i < min(3, (int)primeList.size()); ++i) {
            sum += primeList[i];
        }

        return sum;         
    }
};
