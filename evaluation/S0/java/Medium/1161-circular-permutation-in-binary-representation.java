// Source: https://leetcode.com/problems/circular-permutation-in-binary-representation/   |   Difficulty: Medium
//
// Problem Description:
// Given 2 integers n and start. Your task is return any permutation p of (0,1,2.....,2^n -1) such that :
//
//
// 	p[0] = start
// 	p[i] and p[i+1] differ by only one bit in their binary representation.
// 	p[0] and p[2^n -1] must also differ by only one bit in their binary representation.
//
// Example:
// Input: n = 2, start = 3
// Output: [3,2,0,1]
// Explanation: The binary representation of the permutation is (11,10,00,01). 
// All the adjacent element differ by one bit. Another valid permutation is [3,1,0,2]
//
// Constraints:
// 1 <= n <= 16
// 	0 <= start < 2 ^ n
//

class Solution {

    public List<Integer> circularPermutation(int n, int start) {

        
        List<Integer> result = new ArrayList<>();
        int totalNumbers = 1 << n; // 2^n

        for (int i = 0; i < totalNumbers; i++) {
            // Generate Gray code and then XOR with start to get the desired permutation
            int grayCode = i ^ (i >> 1);
            result.add(grayCode ^ start);
        }

        return result;
    }

}
