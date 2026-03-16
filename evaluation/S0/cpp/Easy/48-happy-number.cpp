// Source: https://leetcode.com/problems/happy-number/   |   Difficulty: Easy
//
// Problem Description:
// Write an algorithm to determine if a number n is happy.
//
// A happy number is a number defined by the following process:
//
//
// 	Starting with any positive integer, replace the number by the sum of the squares of its digits.
// 	Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
// 	Those numbers for which this process ends in 1 are happy.
//
//
// Return true if n is a happy number, and false if not.
//
// Example:
// Input: n = 19
// Output: true
// Explanation:
// 12 + 92 = 82
// 82 + 22 = 68
// 62 + 82 = 100
// 12 + 02 + 02 = 1
//
// Constraints:
// 1 <= n <= 231 - 1
//

class Solution {
public:
    bool isHappy(int n) {
        auto getNext = [](int number) {
            int totalSum = 0;
            while (number > 0) {
                int digit = number % 10;
                number /= 10;
                totalSum += digit * digit;
            }
            return totalSum;
        };

        int slow = n;
        int fast = getNext(n);
        while (fast != 1 && slow != fast) {
            slow = getNext(slow);
            fast = getNext(getNext(fast));
        }
        return fast == 1;           
    }
};
