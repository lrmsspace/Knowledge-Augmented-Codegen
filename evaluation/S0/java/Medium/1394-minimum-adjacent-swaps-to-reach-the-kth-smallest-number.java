// Source: https://leetcode.com/problems/minimum-adjacent-swaps-to-reach-the-kth-smallest-number/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string num, representing a large integer, and an integer k.
//
// We call some integer wonderful if it is a permutation of the digits in num and is greater in value than num. There can be many wonderful integers. However, we only care about the smallest-valued ones.
//
//
// 	For example, when num = "5489355142":
//
// 	
// 		The 1st smallest wonderful integer is "5489355214".
// 		The 2nd smallest wonderful integer is "5489355241".
// 		The 3rd smallest wonderful integer is "5489355412".
// 		The 4th smallest wonderful integer is "5489355421".
// 	
// 	
//
//
// Return the minimum number of adjacent digit swaps that needs to be applied to num to reach the kth smallest wonderful integer.
//
// The tests are generated in such a way that kth smallest wonderful integer exists.
//
// Example:
// Input: num = "5489355142", k = 4
// Output: 2
// Explanation: The 4th smallest wonderful number is "5489355421". To get this number:
// - Swap index 7 with index 8: "5489355142" -> "5489355412"
// - Swap index 8 with index 9: "5489355412" -> "5489355421"
//
// Constraints:
// 2 <= num.length <= 1000
// 	1 <= k <= 1000
// 	num only consists of digits.
//

class Solution {
    public int getMinSwaps(String num, int k) {
        char[] arr = num.toCharArray();
        int n = arr.length;

        // Find the k-th smallest wonderful number
        for (int i = 0; i < k; i++) {
            nextPermutation(arr);
        }

        char[] target = arr.clone();
        arr = num.toCharArray();
        int swaps = 0;

        // Count minimum adjacent swaps to transform num to target
        for (int i = 0; i < n; i++) {
            if (arr[i] != target[i]) {
                int j = i + 1;
                while (arr[j] != target[i]) {
                    j++;
                }
                while (j > i) {
                    swap(arr, j, j - 1);
                    swaps++;
                    j--;
                }
            }
        }

        return swaps;           
    }
}
