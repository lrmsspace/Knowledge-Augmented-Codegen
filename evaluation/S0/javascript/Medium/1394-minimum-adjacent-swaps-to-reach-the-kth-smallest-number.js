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

/**
 * @param {string} num
 * @param {number} k
 * @return {number}
 */
var getMinSwaps = function(num, k) {
    const getKthPermutation = (s, k) => {
        const arr = s.split('');
        for (let i = 0; i < k; i++) {
            let j = arr.length - 2;
            while (j >= 0 && arr[j] >= arr[j + 1]) {
                j--;
            }
            let l = arr.length - 1;
            while (arr[l] <= arr[j]) {
                l--;
            }
            [arr[j], arr[l]] = [arr[l], arr[j]];
            let left = j + 1;
            let right = arr.length - 1;
            while (left < right) {
                [arr[left], arr[right]] = [arr[right], arr[left]];
                left++;
                right--;
            }
        }
        return arr;
    };

    const target = getKthPermutation(num, k);
    let swaps = 0;
    const arr = num.split('');
    for (let i = 0; i < arr.length; i++) {
        if (arr[i] !== target[i]) {
            let j = i + 1;
            while (arr[j] !== target[i]) {
                j++;
            }
            while (j > i) {
                [arr[j], arr[j - 1]] = [arr[j - 1], arr[j]];
                swaps++;
                j--;
            }
        }
    }   
    return swaps;   
};
