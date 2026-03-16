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

class Solution {
public:
    int nonSpecialCount(int l, int r) {
        auto isSpecial = [](int num) {
            int count = 0;
            for (int i = 1; i * i <= num; ++i) {
                if (num % i == 0) {
                    if (i * i != num) {
                        count += 2; // i and num / i
                    } else {
                        count += 1; // perfect square
                    }
                }
                if (count > 2) return false; // More than 2 proper divisors
            }
            return count == 2;
        };

        int nonSpecialCount = 0;
        for (int num = l; num <= r; ++num) {
            if (!isSpecial(num)) {
                ++nonSpecialCount;
            }
        }
        return nonSpecialCount;         
    }
};
