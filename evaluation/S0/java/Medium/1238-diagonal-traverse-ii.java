// Source: https://leetcode.com/problems/diagonal-traverse-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D integer array nums, return all elements of nums in diagonal order as shown in the below images.
//
// Example:
// Input: nums = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [1,4,2,7,5,3,8,6,9]
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i].length <= 105
// 	1 <= sum(nums[i].length) <= 105
// 	1 <= nums[i][j] <= 105
//

class Solution {
    public int[] findDiagonalOrder(List<List<Integer>> nums) {
        List<List<Integer>> diagonals = new ArrayList<>();
        int maxDiagonalIndex = 0;

        for (int row = 0; row < nums.size(); row++) {
            for (int col = 0; col < nums.get(row).size(); col++) {
                int diagonalIndex = row + col;
                maxDiagonalIndex = Math.max(maxDiagonalIndex, diagonalIndex);

                if (diagonalIndex >= diagonals.size()) {
                    diagonals.add(new ArrayList<>());
                }
                diagonals.get(diagonalIndex).add(nums.get(row).get(col));
            }
        }

        List<Integer> resultList = new ArrayList<>();
        for (int i = 0; i <= maxDiagonalIndex; i++) {
            List<Integer> diagonal = diagonals.get(i);
            for (int j = diagonal.size() - 1; j >= 0; j--) {
                resultList.add(diagonal.get(j));
            }
        }

        int[] result = new int[resultList.size()];
        for (int i = 0; i < resultList.size(); i++) {
            result[i] = resultList.get(i);
        }

        return result;          
    }
}
