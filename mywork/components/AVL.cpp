template<class K, class V>
class AVLTree {
public:
    class Node {
    public:
        Entry<K,V>* entry;
        Node* left;
        Node* right;
        int balance;
        typename SplayTree<K,V>::Node* corr;

        Node(Entry<K,V>* entry = NULL, Node* left = NULL, Node* right = NULL) {
            this->entry = entry;
            this->left = left;
            this->right = right;
            this->balance = EH;
            this->corr = NULL;
        }
        ~Node() {}
    };
    class Node;
    enum BalanceValue {LH = -1, EH = 0, RH = 1 };

    Node *root;

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree(){}
    int     getHeight(Node* root) {
        if (!root) return 0;
        return max(getHeight(root->left), getHeight(root->right)) + 1;
    }
    int     getHeight() {
        return this->getHeight(this->root);
    }
    void    printNSpace(int n) {
        for (int i = 0; i < n - 1; i++) cout << " ";
    }
    void    printTreeStructure() {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->entry->key;
                
                q.push(temp->left);
                q.push(temp->right);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }

    void    r_rotate(Node* &root) {
        Node *tmp = root->left;
        root->left = tmp->right;
        tmp->right = root;
        root = tmp;
    }
    void    l_rotate(Node* &root) {
        Node *tmp = root->right;
        root->right = tmp->left;
        tmp->left = root;
        root = tmp;
    }
    bool    balance(Node* &root) {
        if (root->balance == LH) {
            // cout << "balancing " << root->entry->key << root->left->entry->key<< endl;
            if (root->left->balance == EH) {
                r_rotate(root);
                root->balance = RH; 
                root->right->balance = LH; 
                return false;
            }
            else if (root->left->balance == LH) {
                r_rotate(root);
                root->balance = EH; 
                root->right->balance = EH;
                // cout << "right balanced " << root->right->entry->key << " "  << root->right->balance << endl;
                return false;
            }
            else {
                l_rotate(root->left);
                r_rotate(root);
                
                if (root->balance == LH) {
                    root->left->balance = EH; root->right->balance = RH;
                }
                else if (root->balance == EH) {
                    root->left->balance = EH; root->right->balance = EH;
                }
                else {
                    root->left->balance = LH; root->right->balance = EH;
                }
                root->balance = EH;
                return false;
            }
        }
        else {
            // cout << "balancing " << root->entry->key << root->right->entry->key<< endl;
            if (root->right->balance == EH) {
                l_rotate(root);
                root->balance = LH; 
                root->left->balance = RH; 
                return false;
            }
            else if (root->right->balance == RH) {
                l_rotate(root);
                root->balance = EH; 
                root->left->balance = EH; 
                return false;
            }
            else {
                r_rotate(root->right);
                l_rotate(root);
                
                if (root->balance == RH) {
                    root->right->balance = EH; root->left->balance = LH;
                }
                else if (root->balance == EH) {
                    root->right->balance = EH; root->left->balance = EH;
                }
                else {
                    root->right->balance = RH; root->left->balance = EH;
                }
                root->balance = EH;
                return false;
            }
        }
        return true;
    }
    bool    add(Entry<K,V> *entry, Node* &root, Node* &return_node) {
        if (!root) {
            root = new Node(entry); 
            return_node = root;
            return true; 
        }
        if (entry->key == root->entry->key) throw "Duplicate key"; //THROWING HERE
        else if (entry->key > root->entry->key) {
            if (add(entry, root->right, return_node)) {
                if (root->balance == RH) {
                    return balance(root);
                }
                else if (root->balance == EH) {
                    root->balance = RH;
                    return true;
                }
                else {
                    root->balance = EH;
                    return false;
                }
            }
            return false;
        }
        else {
            if (add(entry, root->left, return_node)) {
                if (root->balance == LH) {
                    // cout << "START BALANCE LH" << root->entry->key << " " << root->left->entry->key << endl;
                    return balance(root);
                }
                else if (root->balance == EH) {
                    root->balance = LH;
                    return true;
                }
                else {
                    root->balance = EH;
                    return false;
                }
            }
            return false;
        }
    }
    Node*   BKUadd(K key, V value) {
        //TODO
        Entry<K,V> *newEntry = new Entry<K,V> (key, value);
        Node* return_node = nullptr;
        add(newEntry, root, return_node);
        return return_node;
    }
    Node*   BKUadd(Entry<K,V>* entry) {
        Node* return_node = nullptr;
        add(entry, root, return_node);
        // if (!flag) throw "Duplicate key";
        return return_node;
    }
    bool    remove(K key, Node* &root) {
        if (!root) return false;
        // cout << "removing at " << root->entry->key << endl;
        if (root->entry->key < key) {
            if (remove(key, root->right)) {
                if (root->balance == EH) {
                    root->balance = LH;
                }
                else if (root->balance == RH) {
                    root->balance = EH;
                    return true;
                }
                else return !balance(root);
            }
            return false;
        }
        else if (root->entry->key > key) {
            if (remove(key, root->left)) {
                if (root->balance == EH) {
                    root->balance = RH;
                }
                else if (root->balance == LH) {
                    root->balance = EH;
                    return true;
                }
                else return !balance(root);
            }
            return false;
        }
        else {
            if (!root->left && !root->right) {
                delete root;
                root = nullptr;
                return true;
            }
            else if (!root->left) {
                Node* tmp = root;
                root = root->right;
                delete tmp;
                return true;
            }
            else {
                Node *tmp = root->left;
                while (tmp->right) tmp = tmp->right;
                root->entry->key = tmp->entry->key; //cloning
                root->corr = tmp->corr;
                if (remove(tmp->entry->key, root->left)) {
                    if (root->balance == EH) {
                        root->balance = RH;
                    }
                    else if (root->balance == LH) {
                        root->balance = EH;
                        return true;
                    }
                    else return !balance(root);
                }
                return false;
            }
        }
    }    
    void    BKUremove(K key) {
        remove(key, root);
    }
    Node*   search(K key, Node* &root, Node* searched, vector<int> &traversedList=vector<int>(0)) {//SPECIAL BKU SEARCH
        if (!root) return nullptr;
        if (root == searched) return nullptr;
        if (root->entry->key == key) return root;
        else traversedList.push_back(root->entry->key);
        if (root->entry->key < key) return search(key, root->right, searched, traversedList);
        else return search(key, root->left, searched, traversedList);
    }
    Node*   search(K key, Node* &root, vector<int> &traversedList=vector<int>(0)) {
        if (!root) return nullptr;
        if (root->entry->key == key) return root;
        else traversedList.push_back(root->entry->key);
        if (root->entry->key < key) return search(key, root->right, traversedList);
        else return search(key, root->left, traversedList);
    }

    
public: ///for only trees
    void    add(K key, V value) {
        Entry<K,V> *newEntry = new Entry<K,V> (key, value);
        Node* return_node = nullptr;
        add(newEntry, root, return_node);
    }
    void    add(Entry<K,V>* entry) {
        Node* return_node = nullptr;
        add(entry, root, return_node);
    }
    void    remove(K key) {
        remove(key, root);
    }
    V       search(K key) {
        Node* flag = search(key, root);
        if (!flag) throw "Not found";
        else return search(key, root)->value;
    }

    void   traverseNLR (void (*func)(K key, V value), Node* &root) {
        if (!root) return ;
        func(root->entry->key, root->entry->value);
        traverseNLR(func, root->left);
        traverseNLR(func, root->right);
    }

    void   traverseNLR(void (*func)(K key, V value)) {
        traverseNLR(func, root);
    }

    void clear();
};

// int main() {

//     AVLTree<int, int> avl;
//     int arr[] = {10,52,98,4,3,2,1};
//     for (int i = 0; i < 7; i++){
//         avl.add(arr[i], arr[i]);
//         avl.printTreeStructure();
//         cout << "- - - - - - - - - - - -  - - -" << endl;
//     }
    
//     void(*pSwap) (int , int ) = [](int a, int b){
//         cout << "FUCKING WOW SHIT AT NODE " << a << " " << b << endl;
//     };

//     avl.traverseNLR(pSwap);

//     return 0;
// }
// AVLTree<int> avl;
    // for (int i = 0; i < 9; i++){
    //     avl.insert(i);
    //     cout << "Complete insert";
    // }
    // avl.printTreeStructure();

    
    // vector<int> a {0,1,2,3,43314,131,23,1,23,1,2,184231};
    // vector<int> a {2,4,3}
    // vector<int> a{0,0,0,0,1,1,1};
    // srand(time(NULL));
    // vector<int> a;
    // for (int i = 0; i < 50; ++i) a.push_back(rand()%15);
    // vector<int> a {10,52,98,32,68,92,40,13,42,63,99,100};
    // vector<int> a {6,3,9,11,10};
    
    // vector<int> a{10,52,98,32,68,92,40,13,42,63};
    
    // for (int i = 1; i <= (int)a.size(); ++i) {
    //     AVLTree<int> avl;
    //     for (int j = 0; j < i; ++j){
    //         avl.insert(a[j]);
    //     }
    //     avl.printTreeStructure();
    //     cout << " ================== " << endl;
        
    // }

    // AVLTree<int> avl;
    // // vector<int> arr= {10,12,18,32,68,92,40,13,42,63, 20, 10};
    // vector<int> arr= {10,12,18,32,68,13,40,13,42,13, 13, 10};
    // for (int i = 0; i < (int)arr.size(); i++){
    //     avl.insert(arr[i]);
    // }
    // avl.printTreeStructure();
    // for (int i : arr) {
    //     cout << "Removing " << i << endl;
    //     avl.remove(i);
    //     avl.printTreeStructure();
    // }

    // AVLTree<int> avl;
    // int arr[] = {10,52,98,32,68,92,40,13,42,63,99,100};
    // for (int i = 0; i < 12; i++){
    //     avl.insert(arr[i]);
    // }
    // avl.remove(13);
    // avl.printTreeStructure();
