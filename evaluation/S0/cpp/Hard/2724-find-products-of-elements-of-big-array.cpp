// Source: https://leetcode.com/problems/find-products-of-elements-of-big-array/   |   Difficulty: Hard
//
// Problem Description:
// The powerful array of a non-negative integer x is defined as the shortest sorted array of powers of two that sum up to x. The table below illustrates examples of how the powerful array is determined. It can be proven that the powerful array of x is unique.
//
//
// 	
// 		
// 			num
// 			Binary Representation
// 			powerful array
// 		
// 		
// 			1
// 			00001
// 			[1]
// 		
// 		
// 			8
// 			01000
// 			[8]
// 		
// 		
// 			10
// 			01010
// 			[2, 8]
// 		
// 		
// 			13
// 			01101
// 			[1, 4, 8]
// 		
// 		
// 			23
// 			10111
// 			[1, 2, 4, 16]
// 		
// 	
//
//
// The array big_nums is created by concatenating the powerful arrays for every positive integer i in ascending order: 1, 2, 3, and so on. Thus, big_nums begins as [1, 2, 1, 2, 4, 1, 4, 2, 4, 1, 2, 4, 8, ...].
//
// You are given a 2D integer matrix queries, where for queries[i] = [fromi, toi, modi] you should calculate (big_nums[fromi] * big_nums[fromi + 1] * ... * big_nums[toi]) % modi.
//
// Return an integer array answer such that answer[i] is the answer to the ith query.
//
// Example:
// Input: queries = [[1,3,7]]
//
// Output: [4]
//
// Explanation:
//
// There is one query.
//
// big_nums[1..3] = [2,1,2]. The product of them is 4. The result is 4 % 7 = 4.
//
// Constraints:
// 1 <= queries.length <= 500
// 	queries[i].length == 3
// 	0 <= queries[i][0] <= queries[i][1] <= 1015
// 	1 <= queries[i][2] <= 105
//

class Solution {
public:
    vector<int> findProductsOfElements(vector<vector<long long>>& queries) {
        const int MAX_POW = 50;  // Since 2^50 > 10^15
        vector<long long> prefixProducts(MAX_POW + 1, 1);
        vector<int> results;

        for (const auto& query : queries) {
            long long from = query[0];
            long long to = query[1];
            int mod = query[2];

            // Calculate the product for the range [from, to]
            long long product = 1;
            for (int pow = 0; pow <= MAX_POW; ++pow) {
                long long powValue = 1LL << pow;  // 2^pow
                long long countInRange = countOccurrences(from, to, powValue);
                if (countInRange > 0) {
                    product = (product * modPow(powValue % mod, countInRange, mod)) % mod;
                }
            }

            results.push_back(static_cast<int>(product));
        }

        return results;         
    }
};
