#include <iostream>
#include <queue>
using namespace std;


// 11. Find the winner of the circular game
int findTheWinner(int n, int k) {
    // Create a queue and add all friends from 1 to n in it
    queue<int> friends;
    for (int i=1; i<=n; i++) friends.push(i);

    // Play the game till there are more than 1 friends left in the queue
    while (friends.size() > 1) {
        // Count k - 1 friends in queue from start
        for (int i=1; i<k; i++) {
            int currentFriend = friends.front(); friends.pop();
            friends.push(currentFriend);
        }
        // Remove the kth friend
        friends.pop();
    }

    return friends.front();
}


// 12.


// 13.



int main() {

    

    return 0;
}