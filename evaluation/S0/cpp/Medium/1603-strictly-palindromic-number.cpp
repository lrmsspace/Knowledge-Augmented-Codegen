// Source: https://leetcode.com/problems/strictly-palindromic-number/   |   Difficulty: Medium
//
#include <vector>
using namespace std;

// Problem Description:
// An integer n is strictly palindromic if, for every base b between 2 and n - 2 (inclusive), the string representation of the integer n in base b is palindromic.
//
// Given an integer n, return true if n is strictly palindromic and false otherwise.
//
// A string is palindromic if it reads the same forward and backward.
//
// Example:
// Input: n = 9
// Output: false
// Explanation: In base 2: 9 = 1001 (base 2), which is palindromic.
// In base 3: 9 = 100 (base 3), which is not palindromic.
// Therefore, 9 is not strictly palindromic so we return false.
// Note that in bases 4, 5, 6, and 7, n = 9 is also not palindromic.
//
// Constraints:
// 4 <= n <= 105
//

class Solution {
public:
    bool isStrictlyPalindromic(int n) {
        // For every base b from 2 to n-2, check if n is palindromic in that base
        for (int base = 2; base <= n - 2; base++) {
            if (!isPalindromicInBase(n, base)) {
                return false;
            }
        }
        return true;
    }
    
private:
    // Helper function to check if a number is palindromic in a given base
    bool isPalindromicInBase(int n, int base) {
        vector<int> digits;
        int num = n;
        
        // Convert number to the given base
        while (num > 0) {
            digits.push_back(num % base);
            num /= base;
        }
        
        // Check if the digits form a palindrome
        int left = 0, right = digits.size() - 1;
        while (left < right) {
            if (digits[left] != digits[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
};