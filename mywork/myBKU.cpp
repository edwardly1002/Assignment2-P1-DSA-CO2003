#include "components/myBKU.h"
#include "components/Entry.cpp"
#include "components/AVL.cpp"
#include "components/Splay.cpp"

template <class K, class V>
class BKUTree {
private:
    AVLTree<K,V>* avl;
    SplayTree<K,V>* splay;
    queue<K> keys;
    int maxNumOfKeys;

public:
    BKUTree(int maxNumOfKeys = 5) {
        avl = new AVLTree<K,V>;
        splay = new SplayTree<K,V>;
        this->maxNumOfKeys = maxNumOfKeys;
    }
    ~BKUTree() { this-> clear(); }

    void addToQueue(K key) {
        keys.push(key);
        if (keys.size() > maxNumOfKeys) keys.pop();
    }

    void    add(K key, V value) {
        typename SplayTree<K,V>::Node* splayNode = splay->BKUadd(key,value);
        typename AVLTree<K,V>::Node* avlNode = avl->BKUadd(key, value);
        // cout << "DONE simple here" << endl;
        splayNode->corr = avlNode;
        avlNode->corr = splayNode;
        addToQueue(key);
    }
    void    remove(K key) {
        Entry<K,V>* entry = splay->BKUremove(key);
        avl->BKUremove(key);

        int n = keys.size();
        for (int i = 0; i < n; ++i) {
            int tmp = keys.front();
            keys.pop();
            if (tmp != key) keys.push(tmp);
        }
        if (keys.size() < n && splay->root) keys.push(splay->root->entry->key);

        delete entry;
    }
    bool    inQueue(K key, vector<int> &traversedList) {
        for (int i = 0; i < keys.size(); ++i) {
            int p = keys.front();
            keys.pop();
            keys.push(p);
            if (p == key) return true;

            traversedList.push_back(p);
        }
        return false;
    }
    V       search(K key, vector<K>& traversedList) {
        int result;
        if (splay->root && key == splay->root->entry->key) { //At top of Splay
            return splay->root->entry->value;
        }
        else traversedList.push_back(splay->root->entry->key);
        
        if (inQueue(key, traversedList)) { //Found in queue
            typename SplayTree<K,V>::Node* splayNode = splay->BKUsearch(key, traversedList);
            result = splayNode->entry->value;
            splay->splayOnce(splayNode);
        }
        else { //Find  in AVL 
            typename AVLTree<K,V>::Node* avlNode = splay->root->corr;
            typename AVLTree<K,V>::Node* entrySearch = avl->search(key, avlNode, traversedList);
            if (entrySearch) { //children of corr 
                result = entrySearch->entry->value;
            }
            else { //The whole, AVL
                // cout << "Searching the whole tree with AVLNODE = " << avlNode->entry->key << endl;
                entrySearch = avl->search(key, avl->root, avlNode, traversedList);
                if (!entrySearch) throw "Not found";
                else {
                    result = entrySearch->entry->value;
                }
            }
            typename SplayTree<K,V>::Node* splayNode = entrySearch->corr;
            splay->splayOnce(splayNode);
        }
        addToQueue(result);
        return result;
    }

    void    displayTrees() {
        cout << "QUEUES: " << endl;
        for (int i = 0; i < keys.size(); ++i) {
            int p = keys.front();
            keys.pop();
            keys.push(p);
            cout << p << endl;
        }
        cout << endl;
        cout << "AVL tree: " << endl;
        avl->printTreeStructure();
        cout << "Splay tree: " << endl;
        splay->printTreeStructure();
    }
    void    traverseNLROnAVL(void (*func)(K key, V value));
    void    traverseNLROnSplay(void (*func)(K key, V value));

    void    clear();

};

int main() {

    // BKUTree<int,int>* myBKU = new BKUTree<int,int>;
    // int a[] = {1,2,5,3,4,10,12,9,8,11};
    // int n = 10;
    // for (int i = 0; i < n; ++i) {
    //     myBKU->add(a[i], a[i]);
    // }
    // for (int i = 0; i < n; ++i) {
    //     myBKU->remove(a[i]);
    // }
    BKUTree<int,int>* myBKU = new BKUTree<int,int>;
    int a[] = {1,2,5,3,4,10,12,9};
    int n = 8;
    for (int i = 0; i < n; ++i) {
        myBKU->add(a[i], a[i]);
    }
    myBKU->displayTrees();

    vector<int> traverseList;
    try {
        cout << "SEARCH FOR: 3  -->  " << myBKU->search(a[3], traverseList) << endl;
        cout << "Output traversedList: " << endl;
        for (int i : traverseList) cout << i << " ";
        cout << endl;
    }
    catch (const char* e) {
        cout << "Bach caught exception: " << e << endl;
    }
    myBKU->displayTrees();

    // cout << "HAHA" << endl;
    // myBKU->displayTrees();
    


    return 0;
}