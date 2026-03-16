// Source: https://leetcode.com/problems/find-the-count-of-numbers-which-are-not-special/   |   Difficulty: Medium
//
// Problem Description:
// You are given 2 positive integers l and r. For any number x, all positive divisors of x except x are called the proper divisors of x.
//
// A number is called special if it has exactly 2 proper divisors. For example:
//
//
// 	The number 4 is special because it has proper divisors 1 and 2.
// 	The number 6 is not special because it has proper divisors 1, 2, and 3.
//
//
// Return the count of numbers in the range [l, r] that are not special.
//
// Example:
// Input: l = 5, r = 7
//
// Output: 3
//
// Explanation:
//
// There are no special numbers in the range [5, 7].
//
// Constraints:
// 1 <= l <= r <= 109
//

int nonSpecialCount(int l, int r) {
    // A number is special if it has exactly 2 proper divisors.
    // The only numbers that have exactly 2 proper divisors are the squares of prime numbers.
    // Therefore, we need to count the number of perfect squares of prime numbers in the range [l, r].
    // We can do this by iterating through all prime numbers whose squares are less than or equal to r,
    // and counting how many of those squares are greater than or equal to l.

    int count = 0;

    // Function to check if a number is prime
    int isPrime(int num) {
        if (num < 2) return 0;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) return 0;
        }
        return 1;
    }

    for (long long i = 2; i * i <= r; i++) {
        if (isPrime(i)) {
            long long square = i * i;
            if (square >= l && square <= r) {
                count++;
            }
        }
    }

    return (r - l + 1) - count; // Total numbers in range - special numbers     
}
