// Source: https://leetcode.com/problems/rank-transform-of-an-array/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of integers arr, replace each element with its rank.
//
// The rank represents how large the element is. The rank has the following rules:
//
//
// 	Rank is an integer starting from 1.
// 	The larger the element, the larger the rank. If two elements are equal, their rank must be the same.
// 	Rank should be as small as possible.
//
// Example:
// Input: arr = [40,10,20,30]
// Output: [4,1,2,3]
// Explanation: 40 is the largest element. 10 is the smallest. 20 is the second smallest. 30 is the third smallest.
//
// Constraints:
// 0 <= arr.length <= 105
// 	-109 <= arr[i] <= 109
//

/**
 * @param {number[]} arr
 * @return {number[]}
 */
var arrayRankTransform = function(arr) {
    const sortedUnique = Array.from(new Set(arr)).sort((a, b) => a - b);
    const rankMap = new Map();
    sortedUnique.forEach((num, index) => {
        rankMap.set(num, index + 1);
    });
    return arr.map(num => rankMap.get(num));
};
