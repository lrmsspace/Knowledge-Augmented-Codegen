// Source: https://leetcode.com/problems/merge-two-2d-arrays-by-summing-values/   |   Difficulty: Easy
//
// Problem Description:
// You are given two 2D integer arrays nums1 and nums2.
//
//
// 	nums1[i] = [idi, vali] indicate that the number with the id idi has a value equal to vali.
// 	nums2[i] = [idi, vali] indicate that the number with the id idi has a value equal to vali.
//
//
// Each array contains unique ids and is sorted in ascending order by id.
//
// Merge the two arrays into one array that is sorted in ascending order by id, respecting the following conditions:
//
//
// 	Only ids that appear in at least one of the two arrays should be included in the resulting array.
// 	Each id should be included only once and its value should be the sum of the values of this id in the two arrays. If the id does not exist in one of the two arrays, then assume its value in that array to be 0.
//
//
// Return the resulting array. The returned array must be sorted in ascending order by id.
//
// Example:
// Input: nums1 = [[1,2],[2,3],[4,5]], nums2 = [[1,4],[3,2],[4,1]]
// Output: [[1,6],[2,3],[3,2],[4,6]]
// Explanation: The resulting array contains the following:
// - id = 1, the value of this id is 2 + 4 = 6.
// - id = 2, the value of this id is 3.
// - id = 3, the value of this id is 2.
// - id = 4, the value of this id is 5 + 1 = 6.
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 200
// 	nums1[i].length == nums2[j].length == 2
// 	1 <= idi, vali <= 1000
// 	Both arrays contain unique ids.
// 	Both arrays are in strictly ascending order by id.
//

class Solution {
    public int[][] mergeArrays(int[][] nums1, int[][] nums2) {
        Map<Integer, Integer> map = new HashMap<>();

        for (int[] num : nums1) {
            map.put(num[0], map.getOrDefault(num[0], 0) + num[1]);
        }

        for (int[] num : nums2) {
            map.put(num[0], map.getOrDefault(num[0], 0) + num[1]);
        }

        List<int[]> resultList = new ArrayList<>();
        for (Map.Entry<Integer, Integer> entry : map.entrySet()) {
            resultList.add(new int[]{entry.getKey(), entry.getValue()});
        }

        resultList.sort(Comparator.comparingInt(a -> a[0]));

        return resultList.toArray(new int[resultList.size()][]);            
    }
}
