// Source: https://leetcode.com/problems/friends-of-appropriate-ages/   |   Difficulty: Medium
//
// Problem Description:
// There are n persons on a social media website. You are given an integer array ages where ages[i] is the age of the ith person.
//
// A Person x will not send a friend request to a person y (x != y) if any of the following conditions is true:
//
//
// 	age[y] <= 0.5 * age[x] + 7
// 	age[y] > age[x]
// 	age[y] > 100 && age[x] < 100
//
//
// Otherwise, x will send a friend request to y.
//
// Note that if x sends a request to y, y will not necessarily send a request to x. Also, a person will not send a friend request to themself.
//
// Return the total number of friend requests made.
//
// Example:
// Input: ages = [16,16]
// Output: 2
// Explanation: 2 people friend request each other.
//
// Constraints:
// n == ages.length
// 	1 <= n <= 2 * 104
// 	1 <= ages[i] <= 120
//

/**
 * @param {number[]} ages
 * @return {number}
 */
var numFriendRequests = function(ages) {
    const count = new Array(121).fill(0);
    for (const age of ages) {
        count[age]++;
    }
    let result = 0;
    for (let ageA = 15; ageA <= 120; ageA++) {
        if (count[ageA] === 0) continue;
        for (let ageB = 15; ageB <= 120; ageB++) {
            if (count[ageB] === 0) continue;
            if (ageB <= 0.5 * ageA + 7) continue;
            if (ageB > ageA) continue;
            if (ageB > 100 && ageA < 100) continue;
            result += count[ageA] * (ageA === ageB ? count[ageB] - 1 : count[ageB]);
        }
    }
    return result;
};