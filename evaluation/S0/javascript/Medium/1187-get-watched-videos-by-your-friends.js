// Source: https://leetcode.com/problems/get-watched-videos-by-your-friends/   |   Difficulty: Medium
//
// Problem Description:
// There are n people, each person has a unique id between 0 and n-1. Given the arrays watchedVideos and friends, where watchedVideos[i] and friends[i] contain the list of watched videos and the list of friends respectively for the person with id = i.
//
// Level 1 of videos are all watched videos by your friends, level 2 of videos are all watched videos by the friends of your friends and so on. In general, the level k of videos are all watched videos by people with the shortest path exactly equal to k with you. Given your id and the level of videos, return the list of videos ordered by their frequencies (increasing). For videos with the same frequency order them alphabetically from least to greatest.
//
// Example:
// Input: watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 1
// Output: ["B","C"] 
// Explanation: 
// You have id = 0 (green color in the figure) and your friends are (yellow color in the figure):
// Person with id = 1 -> watchedVideos = ["C"] 
// Person with id = 2 -> watchedVideos = ["B","C"] 
// The frequencies of watchedVideos by your friends are: 
// B -> 1 
// C -> 2
//
// Constraints:
// n == watchedVideos.length == friends.length
// 	2 <= n <= 100
// 	1 <= watchedVideos[i].length <= 100
// 	1 <= watchedVideos[i][j].length <= 8
// 	0 <= friends[i].length < n
// 	0 <= friends[i][j] < n
// 	0 <= id < n
// 	1 <= level < n
// 	if friends[i] contains j, then friends[j] contains i
//

/**
 * @param {string[][]} watchedVideos
 * @param {number[][]} friends
 * @param {number} id
 * @param {number} level
 * @return {string[]}
 */
var watchedVideosByFriends = function(watchedVideos, friends, id, level) {
    
    const n = watchedVideos.length;
    const visited = new Array(n).fill(false);
    const queue = [];
    visited[id] = true;
    queue.push(id);
    let currentLevel = 0;
    while (queue.length > 0 && currentLevel < level) {
        const size = queue.length;
        for (let i = 0; i < size; i++) {
            const person = queue.shift();
            for (const friend of friends[person]) {
                if (!visited[friend]) {
                    visited[friend] = true;
                    queue.push(friend);
                }
            }
        }
        currentLevel++;
    }
    const freqMap = new Map();
    while (queue.length > 0) {
        const person = queue.shift();
        for (const video of watchedVideos[person]) {
            freqMap.set(video, (freqMap.get(video) || 0) + 1);
        }
    }
    const freqArray = Array.from(freqMap.entries());
    freqArray.sort((a, b) => {
        if (a[1] === b[1]) {
            return a[0].localeCompare(b[0]);
        }
        return a[1] - b[1];
    }
    );
    return freqArray.map(entry => entry[0]);    
            
};
