// Source: https://leetcode.com/problems/minimum-index-sum-of-two-lists/   |   Difficulty: Easy
//
// Problem Description:
// Given two arrays of strings list1 and list2, find the common strings with the least index sum.
//
// A common string is a string that appeared in both list1 and list2.
//
// A common string with the least index sum is a common string such that if it appeared at list1[i] and list2[j] then i + j should be the minimum value among all the other common strings.
//
// Return all the common strings with the least index sum. Return the answer in any order.
//
// Example:
// Input: list1 = ["Shogun","Tapioca Express","Burger King","KFC"], list2 = ["Piatti","The Grill at Torrey Pines","Hungry Hunter Steakhouse","Shogun"]
// Output: ["Shogun"]
// Explanation: The only common string is "Shogun".
//
// Constraints:
// 1 <= list1.length, list2.length <= 1000
// 	1 <= list1[i].length, list2[i].length <= 30
// 	list1[i] and list2[i] consist of spaces ' ' and English letters.
// 	All the strings of list1 are unique.
// 	All the strings of list2 are unique.
// 	There is at least a common string between list1 and list2.
//

/**
 * @param {string[]} list1
 * @param {string[]} list2
 * @return {string[]}
 */
var findRestaurant = function(list1, list2) {
    const map = new Map();
    const result = [];
    let minIndexSum = Infinity;    

    for (let i = 0; i < list1.length; i++) {
        map.set(list1[i], i);
    }

    for (let j = 0; j < list2.length; j++) {
        if (map.has(list2[j])) {
            const i = map.get(list2[j]);
            const indexSum = i + j;
            if (indexSum < minIndexSum) {
                minIndexSum = indexSum;
                result.length = 0; // Clear the result array
                result.push(list2[j]);
            } else if (indexSum === minIndexSum) {
                result.push(list2[j]);
            }
        }
    }

    return result;
};      