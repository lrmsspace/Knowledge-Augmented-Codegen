// Source: https://leetcode.com/problems/count-good-triplets-in-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed arrays nums1 and nums2 of length n, both of which are permutations of [0, 1, ..., n - 1].
//
// A good triplet is a set of 3 distinct values which are present in increasing order by position both in nums1 and nums2. In other words, if we consider pos1v as the index of the value v in nums1 and pos2v as the index of the value v in nums2, then a good triplet will be a set (x, y, z) where 0 <= x, y, z <= n - 1, such that pos1x < pos1y < pos1z and pos2x < pos2y < pos2z.
//
// Return the total number of good triplets.
//
// Example:
// Input: nums1 = [2,0,1,3], nums2 = [0,1,2,3]
// Output: 1
// Explanation: 
// There are 4 triplets (x,y,z) such that pos1x < pos1y < pos1z. They are (2,0,1), (2,0,3), (2,1,3), and (0,1,3). 
// Out of those triplets, only the triplet (0,1,3) satisfies pos2x < pos2y < pos2z. Hence, there is only 1 good triplet.
//
// Constraints:
// n == nums1.length == nums2.length
// 	3 <= n <= 105
// 	0 <= nums1[i], nums2[i] <= n - 1
// 	nums1 and nums2 are permutations of [0, 1, ..., n - 1].
//

class Solution {
public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> posInNums2(n);
        for (int i = 0; i < n; ++i) {
            posInNums2[nums2[i]] = i;
        }
        
        // Fenwick Tree (Binary Indexed Tree) for counting
        vector<int> fenwLeft(n + 1, 0);
        vector<int> fenwRight(n + 1, 0);
        
        auto fenwUpdate = [](vector<int>& fenw, int idx, int delta) {
            for (++idx; idx < fenw.size(); idx += idx & -idx) {
                fenw[idx] += delta;
            }
        };
        
        auto fenwQuery = [](vector<int>& fenw, int idx) {
            int sum = 0;
            for (++idx; idx > 0; idx -= idx & -idx) {
                sum += fenw[idx];
            }
            return sum;
        };
        
        // Count elements to the right
        vector<int> rightCount(n, 0);
        for (int i = n - 1; i >= 0; --i) {
            int pos = posInNums2[nums1[i]];
            rightCount[i] = fenwQuery(fenwRight, pos - 1);
            fenwUpdate(fenwRight, pos, 1);
        }
        
        long long result = 0;
        // Count elements to the left and calculate result
        for (int i = 0; i < n; ++i) {
            int pos = posInNums2[nums1[i]];
            int leftCount = fenwQuery(fenwLeft, pos - 1);
            result += static_cast<long long>(leftCount) * rightCount[i];
            fenwUpdate(fenwLeft, pos, 1);
        }
        
        return result;          
    }
};
