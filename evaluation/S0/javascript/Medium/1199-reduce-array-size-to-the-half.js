// Source: https://leetcode.com/problems/reduce-array-size-to-the-half/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array arr. You can choose a set of integers and remove all the occurrences of these integers in the array.
//
// Return the minimum size of the set so that at least half of the integers of the array are removed.
//
// Example:
// Input: arr = [3,3,3,3,5,5,5,2,2,7]
// Output: 2
// Explanation: Choosing {3,7} will make the new array [5,5,5,2,2] which has size 5 (i.e equal to half of the size of the old array).
// Possible sets of size 2 are {3,5},{3,2},{5,2}.
// Choosing set {2,7} is not possible as it will make the new array [3,3,3,3,5,5,5] which has a size greater than half of the size of the old array.
//
// Constraints:
// 2 <= arr.length <= 105
// 	arr.length is even.
// 	1 <= arr[i] <= 105
//

/**
 * @param {number[]} arr
 * @return {number}
 */
var minSetSize = function(arr) {
    const frequencyMap = new Map();
    for (const num of arr) {
        frequencyMap.set(num, (frequencyMap.get(num) || 0) + 1);
    }
    const frequencies = Array.from(frequencyMap.values());
    frequencies.sort((a, b) => b - a);
    let removedCount = 0;
    let setSize = 0;
    const halfSize = arr.length / 2;
    for (const freq of frequencies) {
        removedCount += freq;
        setSize += 1;
        if (removedCount >= halfSize) {
            return setSize;
        }
    }
    return setSize; 
                
};
