// Source: https://leetcode.com/problems/handling-sum-queries-after-update/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed arrays nums1 and nums2 and a 2D array queries of queries. There are three types of queries:
//
//
// 	For a query of type 1, queries[i] = [1, l, r]. Flip the values from 0 to 1 and from 1 to 0 in nums1 from index l to index r. Both l and r are 0-indexed.
// 	For a query of type 2, queries[i] = [2, p, 0]. For every index 0 <= i < n, set nums2[i] = nums2[i] + nums1[i] * p.
// 	For a query of type 3, queries[i] = [3, 0, 0]. Find the sum of the elements in nums2.
//
//
// Return an array containing all the answers to the third type queries.
//
// Example:
// Input: nums1 = [1,0,1], nums2 = [0,0,0], queries = [[1,1,1],[2,1,0],[3,0,0]]
// Output: [3]
// Explanation: After the first query nums1 becomes [1,1,1]. After the second query, nums2 becomes [1,1,1], so the answer to the third query is 3. Thus, [3] is returned.
//
// Constraints:
// 1 <= nums1.length,nums2.length <= 105
// 	nums1.length = nums2.length
// 	1 <= queries.length <= 105
// 	queries[i].length = 3
// 	0 <= l <= r <= nums1.length - 1
// 	0 <= p <= 106
// 	0 <= nums1[i] <= 1
// 	0 <= nums2[i] <= 109
//

class Solution {
public:
    vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        int n = nums1.size();
        vector<long long> result;
        long long sumNums2 = 0;
        for (int num : nums2) {
            sumNums2 += num;
        }
        
        // Precompute prefix XOR for nums1
        vector<int> prefixXOR(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixXOR[i + 1] = prefixXOR[i] ^ nums1[i];
        }
        
        for (const auto& query : queries) {
            int type = query[0];
            if (type == 1) {
                int l = query[1];
                int r = query[2];
                // Flip the values in nums1 from index l to r
                for (int i = l; i <= r; i++) {
                    nums1[i] ^= 1;
                }
            } else if (type == 2) {
                int p = query[1];
                // Update nums2 based on nums1
                for (int i = 0; i < n; i++) {
                    if (nums1[i] == 1) {
                        sumNums2 += p;
                    }
                }
            } else if (type == 3) {
                // Append the sum of nums2 to result
                result.push_back(sumNums2);
            }
        }
        
        return result;          
    }
};
