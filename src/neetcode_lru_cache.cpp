// https://neetcode.io/problems/lru-cache
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct Node {
    int key;
    int value;
    Node *next;
    Node *prev;

    Node(){}

    Node(int k, int v) {
        key = k;
        value = v;
        next = nullptr;
        prev = nullptr;
    }
};

class LRUCache {
   private:
    unordered_map<int, Node> cache;
    Node *most_recent;
    Node *least_recent;
    size_t capacity;

   public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        this->least_recent = &Node(-1, -1); 
        this->most_recent = &Node(-1, -1); 
        this->most_recent->prev = this->least_recent;
        this->least_recent->next = this->most_recent;
    }

    void delete_lru_node() {
        Node* node = this->least_recent->next;
        this->least_recent->next = node->next;
        node->next->prev = this->least_recent;
        node->prev = nullptr;
        delete node;
    }

    void move_node_to_back(Node node) {
        node.prev->next = node.next;
        node.next->prev = node.prev;
        this->most_recent->prev = &node;
        node.next = this->most_recent;
    }

    int get(int key) {
        if(this->cache.find(key) == this->cache.end()) return -1;

        auto it = this->cache.find(key);
        this->move_node_to_back(it->second);
        return it->second.value;
    }

    void put(int key, int value) {
        if(this->cache.find(key) != this->cache.end()) {
            auto it = this->cache.find(key);
            this->move_node_to_back(it->second);
            it->second.value = value;
            return;
        } 
        Node *node = new Node(key, value);
        this->cache[key] = *node;

        if(this->cache.size() > this->capacity) {
            this->delete_lru_node();
        }
        this->move_node_to_back(*node);
    }
};

enum Action{get, put};

struct TestCase {
    LRUCache *cache;
    Action action;
    int key, value;
    int expected;

    void run(int n) {
        cout << "Testcase #: " << n << " ";
        if (action == Action::get) {
            int v = cache->get(key);
            if (v != expected) {
                cout << boolalpha << "Failed! - expected '" << expected << "' got '" << v << "'\n";
                return;
            }
        }
        if (action == Action::put) {
            cache->put(key, value);
        }
        cout << "Passed!\n";
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    LRUCache c(3);

    vector<TestCase> testcases = {
        {&c, Action::put, 1, 10, -1},
        {&c, Action::get, 1, -1, 10},
    };

    int i = 1;
    for (auto &testCase : testcases) {
        testCase.run(i++);
    }
    return 0;
}
