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
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - Suffix Array (string, array, merge-sort)
//   • When to use: Use when needing to efficiently query properties of all suffixes or substrings of a given text, especially for pattern matching or finding repeated structures. It is particularly useful for problems requiring lexicographical ordering of all suffixes.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing their starting indices. It enables efficient string operations like pattern searching and finding longest common prefixes, typically constructed in O(N log N) time.
//   • Invariants: After k iterations, suffixes are sorted correctly up to a certain length (e.g., 2^k).; All suffixes of the original string are represented by their starting indices in the array.
//   • Tips: Append a unique sentinel character (e.g., '$') smaller than any other character to the string.; Utilize the LCP array, often built alongside, for advanced string queries and optimizations.
//   • Pitfalls: Naive sorting of suffixes by string comparison leads to an inefficient O(N^2 log N) complexity.; High memory usage for very long strings due to storing all suffixes implicitly or explicitly.
// - String Sorts (array, string, number, radix-sort, counting-sort)
//   • When to use: Use when sorting a large collection of fixed-length strings or integers, especially when the key range (alphabet size) is small. It is efficient for data with uniform key lengths.
//   • Idea: LSD Radix Sort sorts elements by processing digits or characters from the least significant to the most significant, using a stable counting sort for each position. It achieves a time complexity of O(W * (N + R)), where W is the key length, N is the number of items, and R is the radix.
//   • Invariants: After each pass 'd' (from 'w-1' down to '0'), the array 'a' is stably sorted based on characters from position 'd' to 'w-1'.; The 'count' array accurately reflects the frequency of each character at the current digit 'd' before cumulation.
//   • Tips: Utilize counting sort as the stable inner sorting algorithm for each digit pass.; Process characters or digits from right to left (least significant to most significant).
//   • Pitfalls: Inefficient for variable-length strings without proper padding or specialized handling.; Can be slower than comparison sorts for small input sizes or very large radix (R).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** watchedVideosByFriends(char*** watchedVideos, int watchedVideosSize, int* watchedVideosColSize, int** friends, int friendsSize, int* friendsColSize, int id, int level, int* returnSize) {
    // BFS to find friends at the specified level
    int visited[watchedVideosSize];
    for (int i = 0; i < watchedVideosSize; i++) {
        visited[i] = 0;
    }
    visited[id] = 1;

    int queue[watchedVideosSize];
    int front = 0, rear = 0;
    queue[rear++] = id;

    int currentLevel = 0;
    while (front < rear && currentLevel < level) {
        int size = rear - front;
        for (int i = 0; i < size; i++) {
            int person = queue[front++];
            for (int j = 0; j < friendsColSize[person]; j++) {
                int friendId = friends[person][j];
                if (!visited[friendId]) {
                    visited[friendId] = 1;
                    queue[rear++] = friendId;
                }
            }
        }
        currentLevel++;
    }

    // Count video frequencies
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

    // Sort videos by frequency and lexicographically
    qsort(videoCounts, videoCountSize, sizeof(VideoCount), [](const void* a, const void* b) {
        VideoCount* va = (VideoCount*)a;
        VideoCount* vb = (VideoCount*)b;
        if (va->count != vb->count) {
            return va->count - vb->count;
        }
        return strcmp(va->video, vb->video);
    });
    // Prepare result
    char** result = (char**)malloc(videoCountSize * sizeof(char*));
    for (int i = 0; i < videoCountSize; i++) {
        result[i] = videoCounts[i].video;
    }
    *returnSize = videoCountSize;
    return result;
}
