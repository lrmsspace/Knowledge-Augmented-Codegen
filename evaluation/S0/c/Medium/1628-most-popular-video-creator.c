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
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** mostPopularCreator(char** creators, int creatorsSize, char** ids, int idsSize, int* views, int viewsSize, int* returnSize, int** returnColumnSizes) {
   
    #define MAX_CREATORS 100000
    #define MAX_ID_LEN 6
    #define MAX_CREATOR_LEN 6

    typedef struct {
        char creator[MAX_CREATOR_LEN];
        long long totalViews;
        char topId[MAX_ID_LEN];
        int topViews;
    } CreatorInfo;

    CreatorInfo creatorMap[MAX_CREATORS];
    int creatorCount = 0;

    int findCreatorIndex(char* creator) {
        for (int i = 0; i < creatorCount; i++) {
            if (strcmp(creatorMap[i].creator, creator) == 0) {
                return i;
            }
        }
        return -1;
    }

    for (int i = 0; i < creatorsSize; i++) {
        int idx = findCreatorIndex(creators[i]);
        if (idx == -1) {
            idx = creatorCount++;
            strcpy(creatorMap[idx].creator, creators[i]);
            creatorMap[idx].totalViews = 0;
            creatorMap[idx].topViews = -1;
            creatorMap[idx].topId[0] = '\0';
        }
        creatorMap[idx].totalViews += views[i];
        if (views[i] > creatorMap[idx].topViews || 
           (views[i] == creatorMap[idx].topViews && strcmp(ids[i], creatorMap[idx].topId) < 0)) {
            creatorMap[idx].topViews = views[i];
            strcpy(creatorMap[idx].topId, ids[i]);
        }
    }

    long long maxPopularity = 0;
    for (int i = 0; i < creatorCount; i++) {
        if (creatorMap[i].totalViews > maxPopularity) {
            maxPopularity = creatorMap[i].totalViews;
        }
    }

    char*** result = (char***)malloc(MAX_CREATORS * sizeof(char**));
    *returnColumnSizes = (int*)malloc(MAX_CREATORS * sizeof(int));
    *returnSize = 0;
    for (int i = 0; i < creatorCount; i++) {
        if (creatorMap[i].totalViews == maxPopularity) {
            result[*returnSize] = (char**)malloc(2 * sizeof(char*));
            result[*returnSize][0] = (char*)malloc(MAX_CREATOR_LEN * sizeof(char));
            result[*returnSize][1] = (char*)malloc(MAX_ID_LEN * sizeof(char));
            strcpy(result[*returnSize][0], creatorMap[i].creator);
            strcpy(result[*returnSize][1], creatorMap[i].topId);
            (*returnColumnSizes)[*returnSize] = 2;
            (*returnSize)++;
        }
    }
    return result;
}
