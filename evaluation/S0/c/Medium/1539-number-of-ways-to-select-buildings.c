// Source: https://leetcode.com/problems/number-of-ways-to-select-buildings/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed binary string s which represents the types of buildings along a street where:
//
//
// 	s[i] = '0' denotes that the ith building is an office and
// 	s[i] = '1' denotes that the ith building is a restaurant.
//
//
// As a city official, you would like to select 3 buildings for random inspection. However, to ensure variety, no two consecutive buildings out of the selected buildings can be of the same type.
//
//
// 	For example, given s = "001101", we cannot select the 1st, 3rd, and 5th buildings as that would form "011" which is not allowed due to having two consecutive buildings of the same type.
//
//
// Return the number of valid ways to select 3 buildings.
//
// Example:
// Input: s = "001101"
// Output: 6
// Explanation: 
// The following sets of indices selected are valid:
// - [0,2,4] from "001101" forms "010"
// - [0,3,4] from "001101" forms "010"
// - [1,2,4] from "001101" forms "010"
// - [1,3,4] from "001101" forms "010"
// - [2,4,5] from "001101" forms "101"
// - [3,4,5] from "001101" forms "101"
// No other selection is valid. Thus, there are 6 total ways.
//
// Constraints:
// 3 <= s.length <= 105
// 	s[i] is either '0' or '1'.
//

long long numberOfWays(char* s) {
    long long count0 = 0, count1 = 0;
    long long result = 0;
    long long n = 0;

    // First, count the total number of '0's and '1's in the string
    for (n = 0; s[n] != '\0'; n++) {
        if (s[n] == '0') {
            count0++;
        } else {
            count1++;
        }
    }

    long long left0 = 0, left1 = 0;

    // Iterate through the string to calculate the number of valid combinations
    for (long long i = 0; i < n; i++) {
        if (s[i] == '0') {
            count0--;
            result += left1 * count1; // Form "101"
            left0++;
        } else {
            count1--;
            result += left0 * count0; // Form "010"
            left1++;
        }
    }

    return result;      
}
