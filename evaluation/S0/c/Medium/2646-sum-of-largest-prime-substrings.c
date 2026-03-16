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

long long sumOfLargestPrimes(char* s) {
    int n = strlen(s);
    int max_num = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int num = atoi(strndup(s + i, j - i + 1));
            if (num > max_num) {
                max_num = num;
            }
        }
    }

    // Sieve of Eratosthenes to find all primes up to max_num
    int size = max_num + 1;
    char* is_prime = (char*)malloc(size);
    memset(is_prime, 1, size);
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i * i <= max_num; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= max_num; j += i) {
                is_prime[j] = 0;
            }
        }
    }

    // Collect unique primes from substrings
    int* primes_found = (int*)calloc(size, sizeof(int));
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int num = atoi(strndup(s + i, j - i + 1));
            if (is_prime[num]) {
                primes_found[num] = 1;
            }
        }
    }

    // Find the three largest unique primes
    long long sum = 0;
    int count = 0;
    for (int i = size - 1; i >= 2 && count < 3; i--) {
        if (primes_found[i]) {
            sum += i;
            count++;
        }
    }

    free(is_prime);
    free(primes_found);
    return sum;     
}
