// Source: https://leetcode.com/problems/unit-conversion-i/   |   Difficulty: Medium
//
// Problem Description:
// There are n types of units indexed from 0 to n - 1. You are given a 2D integer array conversions of length n - 1, where conversions[i] = [sourceUniti, targetUniti, conversionFactori]. This indicates that a single unit of type sourceUniti is equivalent to conversionFactori units of type targetUniti.
//
// Return an array baseUnitConversion of length n, where baseUnitConversion[i] is the number of units of type i equivalent to a single unit of type 0. Since the answer may be large, return each baseUnitConversion[i] modulo 109 + 7.
//
// Example:
// Input: conversions = [[0,1,2],[1,2,3]]
//
// Output: [1,2,6]
//
// Explanation:
//
//
// 	Convert a single unit of type 0 into 2 units of type 1 using conversions[0].
// 	Convert a single unit of type 0 into 6 units of type 2 using conversions[0], then conversions[1].
//
// Constraints:
// 2 <= n <= 105
// 	conversions.length == n - 1
// 	0 <= sourceUniti, targetUniti < n
// 	1 <= conversionFactori <= 109
// 	It is guaranteed that unit 0 can be converted into any other unit through a unique combination of conversions without using any conversions in the opposite direction.
//

class Solution {
public:
    vector<int> baseUnitConversions(vector<vector<int>>& conversions) {
        const int MOD = 1e9 + 7;
        int n = conversions.size() + 1;
        vector<vector<pair<int, long long>>> graph(n);
        
        for (const auto& conv : conversions) {
            int src = conv[0];
            int tgt = conv[1];
            long long factor = conv[2];
            graph[src].emplace_back(tgt, factor);
            graph[tgt].emplace_back(src, modInverse(factor, MOD));
        }

        vector<int> result(n, -1);
        result[0] = 1;
        dfs(0, graph, result, MOD);
        
        return result;          
    }
};
