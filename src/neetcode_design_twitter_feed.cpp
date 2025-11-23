// https://neetcode.io/problems/design-twitter-feed
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Twitter {
    vector<vector<int>> followers;
    vector<vector<pair<int, int>>> tweets;
    int tweet_ts;

   public:
    Twitter() {
        for (int i = 0; i < 100; i++) tweets.push_back(vector<pair<int, int>>{});
        for (int i = 0; i < 100; i++) followers.push_back(vector<int>{});
        tweet_ts = 0;
    }

    void postTweet(int userId, int tweetId) {
        this->tweets[userId].push_back({tweetId, tweet_ts++});
    }

    vector<int> getNewsFeed(int userId) {
        auto comp = [](pair<int, int>& a, pair<int, int>& b) { return a.second < b.second; };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> pq(
            comp);  // max heap
        for (auto& x : tweets[userId]) pq.push(x);

        vector<int> ufollowers = followers[userId];

        for (int& x : ufollowers) {
            if (x < 0) continue;
            for (auto& n : tweets[x]) pq.push(n);
        }
        vector<int> tweetItems;
        while (!pq.empty() && tweetItems.size() < 10) {
            tweetItems.push_back(pq.top().first);
            pq.pop();
        }
        return tweetItems;
    }

    void follow(int followerId, int followeeId) {
        if(followerId == followeeId) return;
        for(auto& x: this->followers[followerId]) if(x == followeeId) return;
        this->followers[followerId].push_back(followeeId);
    }

    void unfollow(int followerId, int followeeId) {
        vector<int> ufollowers = this->followers[followerId];
        uint32_t idx = 0;
        for (uint32_t i = 0; i < ufollowers.size(); i++) {
            if (ufollowers[i] == followeeId) {
                idx = i;
                break;
            }
        }
        this->followers[followerId][idx] = -1;
    }
};
enum Commands { PostTweet, GetNewsFeed, Follow, Unfollow };

struct TestCase {
    vector<int> commands;
    vector<vector<int>> values;
    Twitter* t;

    void run() {
        cout << "Running test case\n";
        cout << "=================\n";
        assert(values.size() == commands.size());

        int userId, tweetId, followerId, followeeId;
        vector<int> feed;
        for (uint32_t i = 0; i < commands.size(); i++) {
            switch (commands[i]) {
                case PostTweet:
                    userId = values[i][0];
                    tweetId = values[i][1];
                    t->postTweet(userId, tweetId);
                    cout << "User(" << userId << ") posted tweet: " << tweetId << "\n";
                    break;
                case GetNewsFeed:
                    userId = values[i][0];
                    feed = t->getNewsFeed(userId);
                    cout << "NewsFeed user(" << userId << "): ";
                    for (int x : feed) cout << x << " ";
                    cout << "\n";
                    break;
                case Follow:
                    followerId = values[i][0];
                    followeeId = values[i][1];
                    t->follow(followerId, followeeId);
                    cout << "User(" << followerId << ") started following User(" << followeeId
                         << ")\n";
                    break;
                case Unfollow:
                    followerId = values[i][0];
                    followeeId = values[i][1];
                    t->unfollow(followerId, followeeId);
                    cout << "User(" << followerId << ") stopped following User(" << followeeId
                         << ")\n";
                    break;
                default:
                    cout << "Wrong command\n";
            }
        }
        cout << "\n";
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    vector<TestCase> testcases = {
        {
            .commands = {
                PostTweet, PostTweet, GetNewsFeed, GetNewsFeed, Follow,
                GetNewsFeed, GetNewsFeed, Unfollow, GetNewsFeed, Follow, Follow, GetNewsFeed
            },
            .values = {
                {1,10}, {2,20}, {1}, {2}, {1,2},
                {1}, {2}, {1,2}, {1}, {1,2}, {1,2}, {1}
            },
            .t = new Twitter()
        },
        {
            .commands = {
                PostTweet, PostTweet, PostTweet, PostTweet, PostTweet,
                PostTweet, PostTweet, PostTweet, PostTweet, PostTweet,
                PostTweet, GetNewsFeed
            },
            .values = {
                {1,5}, {1,3}, {1,101}, {1,13}, {1,10}, {1,2},
                {1,94}, {1,505}, {1,333}, {1,22}, {1,11},
                {1}
            },
            .t = new Twitter()
        }
    };

    for (auto& x : testcases) x.run();

    return 0;
}
