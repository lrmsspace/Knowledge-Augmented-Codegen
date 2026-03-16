# Source: https://leetcode.com/problems/count-mentions-per-user/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer numberOfUsers representing the total number of users and an array events of size n x 3.
#
# Each events[i] can be either of the following two types:
#
#
# 	Message Event: ["MESSAGE", "timestampi", "mentions_stringi"]
#
# 	
# 		This event indicates that a set of users was mentioned in a message at timestampi.
# 		The mentions_stringi string can contain one of the following tokens:
# 		
# 			id<number>: where <number> is an integer in range [0,numberOfUsers - 1]. There can be multiple ids separated by a single whitespace and may contain duplicates. This can mention even the offline users.
# 			ALL: mentions all users.
# 			HERE: mentions all online users.
# 		
# 		
# 	
# 	
# 	Offline Event: ["OFFLINE", "timestampi", "idi"]
# 	
# 		This event indicates that the user idi had become offline at timestampi for 60 time units. The user will automatically be online again at time timestampi + 60.
# 	
# 	
#
#
# Return an array mentions where mentions[i] represents the number of mentions the user with id i has across all MESSAGE events.
#
# All users are initially online, and if a user goes offline or comes back online, their status change is processed before handling any message event that occurs at the same timestamp.
#
# Note that a user can be mentioned multiple times in a single message event, and each mention should be counted separately.
#
# Example:
# Input: numberOfUsers = 2, events = [["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","71","HERE"]]
#
# Output: [2,2]
#
# Explanation:
#
# Initially, all users are online.
#
# At timestamp 10, id1 and id0 are mentioned. mentions = [1,1]
#
# At timestamp 11, id0 goes offline.
#
# At timestamp 71, id0 comes back online and "HERE" is mentioned. mentions = [2,2]
#
# Constraints:
# 1 <= numberOfUsers <= 100
# 	1 <= events.length <= 100
# 	events[i].length == 3
# 	events[i][0] will be one of MESSAGE or OFFLINE.
# 	1 <= int(events[i][1]) <= 105
# 	The number of id<number> mentions in any "MESSAGE" event is between 1 and 100.
# 	0 <= <number> <= numberOfUsers - 1
# 	It is guaranteed that the user id referenced in the OFFLINE event is online at the time the event occurs.
#

class Solution(object):
    def countMentions(self, numberOfUsers, events):
        """
        :type numberOfUsers: int
        :type events: List[List[str]]
        :rtype: List[int]
        """
        mentions = [0] * numberOfUsers
        online = [True] * numberOfUsers
        events.sort(key=lambda x: int(x[1]))
        
        for event in events:
            event_type, timestamp, info = event
            timestamp = int(timestamp)
            
            if event_type == "OFFLINE":
                user_id = int(info)
                online[user_id] = False
                
                def bring_online(user_id, timestamp):
                    time.sleep(max(0, timestamp + 60 - time.time()))
                    online[user_id] = True
                
                import threading
                threading.Thread(target=bring_online, args=(user_id, timestamp)).start()
            
            elif event_type == "MESSAGE":
                mentions_list = info.split()
                
                for mention in mentions_list:
                    if mention == "ALL":
                        for i in range(numberOfUsers):
                            mentions[i] += 1
                    elif mention == "HERE":
                        for i in range(numberOfUsers):
                            if online[i]:
                                mentions[i] += 1
                    elif mention.startswith("id"):
                        user_id = int(mention[2:])
                        mentions[user_id] += 1
        
        return mentions