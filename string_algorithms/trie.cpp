#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class TrieNode {
    bool _isEnd;
    vector<shared_ptr<TrieNode>> _children;
public:
    TrieNode() {
        _isEnd = false;
        _children = vector<shared_ptr<TrieNode>>(26, nullptr);
    }

    void setEnd(bool isEnd) {
        _isEnd = isEnd;
    }

    bool getIsEnd() const {
        return _isEnd;
    }

    shared_ptr<TrieNode> addChild(int index) {
        // check indec 0 to 26;
        if (_children[index] == nullptr) {
            _children[index] = make_shared<TrieNode>();
        }

        return _children[index];
    }

    shared_ptr<TrieNode> getChild(int index) {
        return _children[index];
    }
};

class Trie {
    shared_ptr<TrieNode> root;
public:
    Trie() {
        root = make_shared<TrieNode>();
    }

    void addString(const string &str) {
        auto currentRoot = root;
        for (auto chr : str) {
            if (currentRoot->getChild(chr-'a') == nullptr) {
                currentRoot->addChild(chr-'a');
            }
            currentRoot = currentRoot->getChild(chr-'a');
        }
        currentRoot->setEnd(true);
    }

    bool exists(const string &str, bool isExactMatch = false) {
        auto currentRoot = root;
        for (auto chr : str) {
            if (currentRoot->getChild(chr-'a') == nullptr) {
                return false;
            }
            currentRoot = currentRoot->getChild(chr-'a');
        }
        return isExactMatch?currentRoot->getIsEnd():true;
    }
};

int main() {
    auto trie = make_shared<Trie>();

    trie->addString("HelloHareesh");
    trie->addString("HeyHareesh");

    cout << "hello prefix exists: " << trie->exists("hello") << endl;
    cout << "Hello prefix exists: " << trie->exists("Hello") << endl;
    cout << "HelloHareesh exactly exist: " << trie->exists("HelloHareesh") << endl;
    
    return 0;
}