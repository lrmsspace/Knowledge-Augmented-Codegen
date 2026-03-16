// Source: https://leetcode.com/problems/count-palindromic-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// Given a string of digits s, return the number of palindromic subsequences of s having length 5. Since the answer may be very large, return it modulo 109 + 7.
//
// Note:
//
//
// 	A string is palindromic if it reads the same forward and backward.
// 	A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
//
// Example:
// Input: s = "103301"
// Output: 2
// Explanation: 
// There are 6 possible subsequences of length 5: "10330","10331","10301","10301","13301","03301". 
// Two of them (both equal to "10301") are palindromic.
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of digits.
//

int countPalindromes(char* s) {
    int mod = 1000000007;
    int n = strlen(s);
    int leftCount[10][10] = {0};  // Count of pairs (d1, d2) to the left of current position
    int rightCount[10][10] = {0}; // Count of pairs (d1, d2) to the right of current position
    int digitCount[10] = {0};     // Count of individual digits to the right of current position

    // Initialize rightCount with all pairs from the entire string
    for (int i = n - 1; i >= 0; --i) {
        int digit = s[i] - '0';
        for (int d = 0; d < 10; ++d) {
            rightCount[digit][d] += digitCount[d];
        }
        digitCount[digit]++;
    }

    long long result = 0;

    // Traverse the string and calculate palindromic subsequences
    for (int i = 0; i < n; ++i) {
        int digit = s[i] - '0';

        // Remove current digit's contribution from rightCount
        for (int d = 0; d < 10; ++d) {
            rightCount[digit][d] -= digitCount[d];
        }
        digitCount[digit]--;

        // Calculate palindromic subsequences with center at s[i]
        for (int d1 = 0; d1 < 10; ++d1) {
            for (int d2 = 0; d2 < 10; ++d2) {
                result = (result + (long long)leftCount[d1][d2] * rightCount[d1][d2]) % mod;
            }
        }

        // Update leftCount with current digit
        for (int d = 0; d < 10; ++d) {
            leftCount[d][digit] += digitCount[d];
        }
        digitCount[digit]++;
    }

    return (int)result;     
}
