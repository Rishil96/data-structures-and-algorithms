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


// 12. Reveal cards in increasing order
vector<int> deckRevealedIncreasing(vector<int>& deck) {
    // Add all indexes in deque to be used to place cards in order
    deque<int> dq;
    for (int i=0; i<deck.size(); i++) dq.push_back(i);

    // Answer array
    vector<int> answer(deck.size(), 0);

    // Sort cards in increasing order
    sort(deck.begin(), deck.end());

    // Loop through the deck to place cards
    for (int i=0; i<deck.size(); i++) {
        // Get front index
        int index = dq.front(); dq.pop_front();

        // Place current card on index
        answer[index] = deck[i];

        // Place new front index in deque to the back
        dq.push_back(dq.front()); dq.pop_front();
    }

    return answer;
}


// 13. Number of people aware of the secret
int peopleAwareOfSecret(int n, int delay, int forget) {
    const int MOD = 1e9 + 7; 
    int currActiveSpreaders = 0;        // Current active spreaders of secret
    int ans = 1;                        // On day 1, 1 person knows the secret as per problem statement

    // Add entries of new people that got to know the secret should be made 
    queue<pair<int, int>> delayQ;       // Track number of people who are waiting for delay to be over
    queue<pair<int, int>> forgetQ;      // Track number of people who have not forgot the secret yet

    delayQ.push({1, 1});
    forgetQ.push({1, 1});

    for (int day=1; day<=n; day++) {
        // Step 1: Check if anyone is going to forget the secret today
        /* 
        Get it from front of forget queue, subtract the people that forgets the secret today 
        from current active spreaders and the answer 
        */
        if (!forgetQ.empty() && forgetQ.front().first + forget <= day) {
            auto front = forgetQ.front(); forgetQ.pop();
            int forgettingToday = front.second;
            ans = (ans - forgettingToday + MOD) % MOD;
            currActiveSpreaders = (currActiveSpreaders - forgettingToday + MOD) % MOD;
        }

        // Step 2: Check how many people are becoming active spreaders today
        /*
        Get the front of delay queue, if the delay ends today add the number of people to the current active spreaders
        */
        if (!delayQ.empty() && delayQ.front().first + delay <= day) {
            auto front = delayQ.front(); delayQ.pop();
            currActiveSpreaders = (currActiveSpreaders + front.second) % MOD;
        }

        // Step 3: Spread the secret by adding the current active spreaders to the answer and push the new people data in both queues
        if (currActiveSpreaders > 0) {
            ans = (ans + currActiveSpreaders) % MOD;
            delayQ.push({day, currActiveSpreaders});
            forgetQ.push({day, currActiveSpreaders});
        }
    }

    return ans;
}


int main() {

    

    return 0;
}