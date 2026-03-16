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
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** watchedVideosByFriends(char*** watchedVideos, int watchedVideosSize, int* watchedVideosColSize, int** friends, int friendsSize, int* friendsColSize, int id, int level, int* returnSize) {
    // BFS to find friends at the given level
    int visited[watchedVideosSize];
    memset(visited, 0, sizeof(visited));
    visited[id] = 1;
    
    int queue[watchedVideosSize];
    int front = 0, rear = 0;
    queue[rear++] = id;
    
    for (int l = 0; l < level; l++) {
        int size = rear - front;
        for (int i = 0; i < size; i++) {
            int curr = queue[front++];
            for (int j = 0; j < friendsColSize[curr]; j++) {
                int friendId = friends[curr][j];
                if (!visited[friendId]) {
                    visited[friendId] = 1;
                    queue[rear++] = friendId;
                }
            }
        }
    }
    
    // Count frequencies of videos watched by friends at the given level
    typedef struct {
        char* video;
        int count;
    } VideoCount;
    
    VideoCount videoCounts[10000];
    int videoCountSize = 0;
    
    for (int i = front; i < rear; i++) {
        int friendId = queue[i];
        for (int j = 0; j < watchedVideosColSize[friendId]; j++) {
            char* video = watchedVideos[friendId][j];
            int found = 0;
            for (int k = 0; k < videoCountSize; k++) {
                if (strcmp(videoCounts[k].video, video) == 0) {
                    videoCounts[k].count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                videoCounts[videoCountSize].video = video;
                videoCounts[videoCountSize].count = 1;
                videoCountSize++;
            }
        }
    }
    
    // Sort videos by frequency and alphabetically
    qsort(videoCounts, videoCountSize, sizeof(VideoCount), [](const void* a, const void* b) {
        VideoCount* va = (VideoCount*)a;
        VideoCount* vb = (VideoCount*)b;
        if (va->count != vb->count) {
            return va->count - vb->count;
        }
        return strcmp(va->video, vb->video);
    });  
    // Prepare the result
    char** result = (char**)malloc(videoCountSize * sizeof(char*));
    for (int i = 0; i < videoCountSize; i++) {
        result[i] = videoCounts[i].video;
    }
    *returnSize = videoCountSize;
    return result;   
}
