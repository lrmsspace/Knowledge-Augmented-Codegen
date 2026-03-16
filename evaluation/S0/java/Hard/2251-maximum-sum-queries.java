// Source: https://leetcode.com/problems/maximum-sum-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed integer arrays nums1 and nums2, each of length n, and a 1-indexed 2D array queries where queries[i] = [xi, yi].
//
// For the ith query, find the maximum value of nums1[j] + nums2[j] among all indices j (0 <= j < n), where nums1[j] >= xi and nums2[j] >= yi, or -1 if there is no j satisfying the constraints.
//
// Return an array answer where answer[i] is the answer to the ith query.
//
// Example:
// Input: nums1 = [4,3,1,2], nums2 = [2,4,9,5], queries = [[4,1],[1,3],[2,5]]
// Output: [6,10,7]
// Explanation: 
// For the 1st query xi = 4 and yi = 1, we can select index j = 0 since nums1[j] >= 4 and nums2[j] >= 1. The sum nums1[j] + nums2[j] is 6, and we can show that 6 is the maximum we can obtain.
//
// For the 2nd query xi = 1 and yi = 3, we can select index j = 2 since nums1[j] >= 1 and nums2[j] >= 3. The sum nums1[j] + nums2[j] is 10, and we can show that 10 is the maximum we can obtain. 
//
// For the 3rd query xi = 2 and yi = 5, we can select index j = 3 since nums1[j] >= 2 and nums2[j] >= 5. The sum nums1[j] + nums2[j] is 7, and we can show that 7 is the maximum we can obtain.
//
// Therefore, we return [6,10,7].
//
// Constraints:
// nums1.length == nums2.length 
// 	n == nums1.length 
// 	1 <= n <= 105
// 	1 <= nums1[i], nums2[i] <= 109 
// 	1 <= queries.length <= 105
// 	queries[i].length == 2
// 	xi == queries[i][1]
// 	yi == queries[i][2]
// 	1 <= xi, yi <= 109
//

class Solution {
    public int[] maximumSumQueries(int[] nums1, int[] nums2, int[][] queries) {
        int n = nums1.length;
        int q = queries.length;
        int[][] arr = new int[n + q][3];
        
        for (int i = 0; i < n; i++) {
            arr[i][0] = nums1[i];
            arr[i][1] = nums2[i];
            arr[i][2] = -1; // mark as data point
        }
        
        for (int i = 0; i < q; i++) {
            arr[n + i][0] = queries[i][0];
            arr[n + i][1] = queries[i][1];
            arr[n + i][2] = i; // mark as query point
        }
        
        Arrays.sort(arr, (a, b) -> b[0] != a[0] ? Integer.compare(b[0], a[0]) : Integer.compare(b[1], a[1]));
        
        TreeMap<Integer, Integer> map = new TreeMap<>();
        int[] result = new int[q];
        Arrays.fill(result, -1);
        
        for (int[] item : arr) {
            if (item[2] == -1) { // data point
                int y = item[1];
                int sum = item[0] + item[1];
                
                Integer key = map.ceilingKey(y);
                if (key != null && map.get(key) >= sum) {
                    continue;
                }
                
                while (true) {
                    Integer lowerKey = map.lowerKey(y);
                    if (lowerKey == null || map.get(lowerKey) > sum) {
                        break;
                    }
                    map.remove(lowerKey);
                }
                
                map.put(y, sum);
            } else { // query point
                int y = item[1];
                Integer key = map.ceilingKey(y);
                if (key != null) {
                    result[item[2]] = map.get(key);
                }
            }
        }
        
        return result;          
    }
}
