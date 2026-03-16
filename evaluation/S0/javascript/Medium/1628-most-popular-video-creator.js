// Source: https://leetcode.com/problems/most-popular-video-creator/   |   Difficulty: Medium
//
// Problem Description:
// You are given two string arrays creators and ids, and an integer array views, all of length n. The ith video on a platform was created by creators[i], has an id of ids[i], and has views[i] views.
//
// The popularity of a creator is the sum of the number of views on all of the creator's videos. Find the creator with the highest popularity and the id of their most viewed video.
//
//
// 	If multiple creators have the highest popularity, find all of them.
// 	If multiple videos have the highest view count for a creator, find the lexicographically smallest id.
//
//
// Note: It is possible for different videos to have the same id, meaning that ids do not uniquely identify a video. For example, two videos with the same ID are considered as distinct videos with their own viewcount.
//
// Return a 2D array of strings answer where answer[i] = [creatorsi, idi] means that creatorsi has the highest popularity and idi is the id of their most popular video. The answer can be returned in any order.
//
// Example:
// Input: creators = ["alice","bob","alice","chris"], ids = ["one","two","three","four"], views = [5,10,5,4]
//
// Output: [["alice","one"],["bob","two"]]
//
// Explanation:
//
// The popularity of alice is 5 + 5 = 10.
// The popularity of bob is 10.
// The popularity of chris is 4.
// alice and bob are the most popular creators.
// For bob, the video with the highest view count is "two".
// For alice, the videos with the highest view count are "one" and "three". Since "one" is lexicographically smaller than "three", it is included in the answer.
//
// Constraints:
// n == creators.length == ids.length == views.length
// 	1 <= n <= 105
// 	1 <= creators[i].length, ids[i].length <= 5
// 	creators[i] and ids[i] consist only of lowercase English letters.
// 	0 <= views[i] <= 105
//

/**
 * @param {string[]} creators
 * @param {string[]} ids
 * @param {number[]} views
 * @return {string[][]}
 */
var mostPopularCreator = function(creators, ids, views) {
    const creatorData = new Map();
    let maxPopularity = 0;
    for (let i = 0; i < creators.length; i++) {
        const creator = creators[i];
        const id = ids[i];
        const viewCount = views[i];
        if (!creatorData.has(creator)) {
            creatorData.set(creator, { totalViews: 0, topVideoId: id, topVideoViews: 0 });
        }   
        const data = creatorData.get(creator);
        data.totalViews += viewCount;
        if (viewCount > data.topVideoViews || (viewCount === data.topVideoViews && id < data.topVideoId)) {
            data.topVideoViews = viewCount;
            data.topVideoId = id;
        }
        maxPopularity = Math.max(maxPopularity, data.totalViews);
    }
    const result = [];
    for (const [creator, data] of creatorData.entries()) {
        if (data.totalViews === maxPopularity) {
            result.push([creator, data.topVideoId]);
        }
    }
    return result;  
};
