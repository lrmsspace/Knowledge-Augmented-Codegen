// Source: https://leetcode.com/problems/merge-triplets-to-form-target-triplet/   |   Difficulty: Medium
//
// Problem Description:
// A triplet is an array of three integers. You are given a 2D integer array triplets, where triplets[i] = [ai, bi, ci] describes the ith triplet. You are also given an integer array target = [x, y, z] that describes the triplet you want to obtain.
//
// To obtain target, you may apply the following operation on triplets any number of times (possibly zero):
//
//
// 	Choose two indices (0-indexed) i and j (i != j) and update triplets[j] to become [max(ai, aj), max(bi, bj), max(ci, cj)].
//
// 	
// 		For example, if triplets[i] = [2, 5, 3] and triplets[j] = [1, 7, 5], triplets[j] will be updated to [max(2, 1), max(5, 7), max(3, 5)] = [2, 7, 5].
// 	
// 	
//
//
// Return true if it is possible to obtain the target triplet [x, y, z] as an element of triplets, or false otherwise.
//
// Example:
// Input: triplets = [[2,5,3],[1,8,4],[1,7,5]], target = [2,7,5]
// Output: true
// Explanation: Perform the following operations:
// - Choose the first and last triplets [[2,5,3],[1,8,4],[1,7,5]]. Update the last triplet to be [max(2,1), max(5,7), max(3,5)] = [2,7,5]. triplets = [[2,5,3],[1,8,4],[2,7,5]]
// The target triplet [2,7,5] is now an element of triplets.
//
// Constraints:
// 1 <= triplets.length <= 105
// 	triplets[i].length == target.length == 3
// 	1 <= ai, bi, ci, x, y, z <= 1000
//

bool mergeTriplets(int** triplets, int tripletsSize, int* tripletsColSize, int* target, int targetSize) {
    int found[3] = {0, 0, 0};
    
    for (int i = 0; i < tripletsSize; i++) {
        if (triplets[i][0] <= target[0] && triplets[i][1] <= target[1] && triplets[i][2] <= target[2]) {
            if (triplets[i][0] == target[0]) {
                found[0] = 1;
            }
            if (triplets[i][1] == target[1]) {
                found[1] = 1;
            }
            if (triplets[i][2] == target[2]) {
                found[2] = 1;
            }
        }
    }
    
    return found[0] && found[1] && found[2];        
}
