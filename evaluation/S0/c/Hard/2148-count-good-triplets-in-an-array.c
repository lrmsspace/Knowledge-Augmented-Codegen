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

long long goodTriplets(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int n = nums1Size;
    int* posInNums2 = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        posInNums2[nums2[i]] = i;
    }

    int* fenwickTree = (int*)calloc(n + 1, sizeof(int));

    long long result = 0;
    for (int j = 0; j < n; j++) {
        int val = nums1[j];
        int pos2 = posInNums2[val];

        // Count elements less than pos2
        long long leftCount = 0;
        for (int k = pos2; k > 0; k -= k & -k) {
            leftCount += fenwickTree[k];
        }

        // Count elements greater than pos2
        long long rightCount = 0;
        for (int k = n; k > pos2 + 1; k -= k & -k) {
            rightCount += fenwickTree[k];
        }

        result += leftCount * rightCount;

        // Update Fenwick Tree
        for (int k = pos2 + 1; k <= n; k += k & -k) {
            fenwickTree[k]++;
        }
    }

    free(posInNums2);
    free(fenwickTree);

    return result;
}
