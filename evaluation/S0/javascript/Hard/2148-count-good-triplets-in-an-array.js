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

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number}
 */
var goodTriplets = function(nums1, nums2) {
    const n = nums1.length;
    const pos2 = new Array(n);  
    for (let i = 0; i < n; i++) {
        pos2[nums2[i]] = i;
    }
    const fenwickTree = new FenwickTree(n);
    let count = 0;
    for (let i = 0; i < n; i++) {
        const pos = pos2[nums1[i]];
        count += fenwickTree.query(pos - 1) * (i - fenwickTree.query(pos));
        fenwickTree.update(pos, 1);
    }
    return count;   
};
