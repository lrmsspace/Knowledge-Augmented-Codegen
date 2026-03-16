// Source: https://leetcode.com/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one/   |   Difficulty: Medium
//
// Problem Description:
// Given the binary representation of an integer as a string s, return the number of steps to reduce it to 1 under the following rules:
//
//
// 	
// 	If the current number is even, you have to divide it by 2.
// 	
// 	
// 	If the current number is odd, you have to add 1 to it.
// 	
//
//
// It is guaranteed that you can always reach one for all test cases.
//
// Example:
// Input: s = "1101"
// Output: 6
// Explanation: "1101" corressponds to number 13 in their decimal representation.
// Step 1) 13 is odd, add 1 and obtain 14. 
// Step 2) 14 is even, divide by 2 and obtain 7.
// Step 3) 7 is odd, add 1 and obtain 8.
// Step 4) 8 is even, divide by 2 and obtain 4.  
// Step 5) 4 is even, divide by 2 and obtain 2. 
// Step 6) 2 is even, divide by 2 and obtain 1.
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of characters '0' or '1'
// 	s[0] == '1'
//

class Solution {
public:
    int numSteps(string s) {
        int steps = 0;
        int carry = 0;
        int n = s.size();

        // Process the binary string from the least significant bit to the most significant bit
        for (int i = n - 1; i > 0; --i) {
            int bit = s[i] - '0';
            if ((bit + carry) % 2 == 0) {
                // Even case: divide by 2
                steps += 1;
            } else {
                // Odd case: add 1 (which may cause a carry)
                steps += 2; // one for adding 1 and one for dividing by 2
                carry = 1;  // set carry for the next higher bit
            }
        }

        // If there's a carry left after processing all bits, we need one more step to handle it
        if (carry == 1) {
            steps += 1;
        }

        return steps;           
    }
};
