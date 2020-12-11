template <class K, class V>
class SplayTree {
public:
    class Node {
    public:
        Entry<K,V>* entry;
        Node* left;
        Node* right;
        Node* parent;
        typename AVLTree<K,V>::Node* corr;

        Node(Entry<K,V>* entry = NULL, Node* left = NULL, Node* right = NULL, Node* parent = NULL) {
            this->entry = entry;
            this->left = left;
            this->right = right;
            this->parent = parent;
            this->corr = NULL;
        }
        
        ~Node() {
            this->entry = nullptr;
            left = nullptr;
            right = nullptr;
            // corr = nullptr;
        }
    };

public:
    Node* root;

    SplayTree(): root(NULL) {};
    // ~SplayTree() { this->clear(); };
    
    int     getHeight(Node* &root) {
        if (!root) return 0;
        return max(getHeight(root->left), getHeight(root->right)) + 1;
    }
    int     getHeight() {
        return getHeight(root);
    }
    void    printNSpace(int n) {
        for (int i = 0; i < n - 1; i++) cout << " ";
    }
    void    printTreeStructure() {
        int height = this->getHeight();
        if (this->root == NULL) {
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

    void    l_rotate(Node* x) {
        Node *y = x->right;
        if (y) {
            x->right = y->left;
            if (y->left) y->left->parent = x;
            y->parent = x->parent;
        }
        
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        if (y) y->left = x;
        x->parent = y;
    }
    void    r_rotate(Node* x) {
        Node *y = x->left;
        if (y) {
            x->left = y->right;
            if (y->right) y->right->parent = x;
            y->parent = x->parent;
        }
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        if (y) y->right = x;
        x->parent = y;  
    }
    void    splayOnce(Node* &root) {
        if (!root->parent->parent) {//left or right 
            if (root->parent->left == root) r_rotate(root->parent);
            else l_rotate(root->parent);
        } 
        else if (root->parent->left == root && root->parent->parent->left == root->parent) {//zig-zig-left
            r_rotate(root->parent->parent);
            r_rotate(root->parent);
        } 
        else if (root->parent->right == root && root->parent->parent->right == root->parent) {//zig-zig-right
            l_rotate(root->parent->parent);
            l_rotate(root->parent);
        } 
        else if (root->parent->left == root && root->parent->parent->right == root->parent) {//zig-zag-left
            r_rotate(root->parent);
            l_rotate(root->parent);
        } 
        else { //zig-zag-right
            l_rotate(root->parent);
            r_rotate(root->parent);
        }
        // cout << "END 1 LOOP SPLAY" << endl;
    }
    void    splay(Node* &root) {//this method assumes that the key existed
        while (root->parent) {
            // cout << "START 1 LOOP SPLAY" << endl;
            splayOnce(root);
        }
    }   

    Node*   add(Entry<K,V>* entry, Node*& root, Node* parent) {
        // cout << "COMPLEX ADD" << endl;
        // cout << "--- value = " << root->entry->value << endl;
        if (!root) {
            root = new Node(entry, nullptr, nullptr, parent);
            return root;
        }
        else {
            if (entry->key == root->entry->key) return nullptr;
            else if (entry->key > root->entry->key) return add(entry, root->right, root);
            else return add(entry, root->left, root);
        }
    }
    Node*   BKUadd(K key, V value) {
        // cout << "GET IN" << endl;
        Entry<K,V>* newEntry = new Entry<K,V>(key, value);
        Node* flag = add(newEntry, root, nullptr); 
        // cout << "DONE SIMPLE ADD JOB" << endl;
        if (!flag) throw "Duplicate key";
        else splay(flag);
        return root;
    }
    Node*   BKUadd(Entry<K,V>* entry) {
        Node* flag = add(entry, root, nullptr); 
        if (!flag) throw "Duplicate key";
        else splay(flag);
        return root;
    }
    void    replace(Node *u, Node *v) {
        if (!u->parent) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        if (v) v->parent = u->parent;
    }
    Entry<K,V>*    BKUremove(K key) {
        Node* z = BKUsearch(key, root);
        if (!root || !z) return nullptr;

        splay(z);

        Entry<K,V>* result = z->entry;
        
        if (!z->right) {replace(z, z->left); }
        else if (!z->left) {replace(z, z->right); }
        else {
            Node *y = root->left;
            while (y->right) y = y->right; //splaying maxL
            if (y->parent != root) {
                replace(y, y->left);
                y->left = z->left;
                y->left->parent = y;
            }
            replace(z, y);
            y->right = z->right;
            y->right->parent = y;
        }
        
        delete z;
        if (!result) throw "Not found";
        return result;
    }
    Node*   search(K key, Node* root, vector<int> &traversedList=vector<int>(0)) {
        if (!root) return nullptr;
        if (root->entry->key == key) return root;
        else  traversedList.push_back(root->entry->key);
        if (key > root->entry->key) return search(key, root->right, traversedList);
        else return search(key, root->left, traversedList); 
    }
    Node*   BKUsearch(K key, vector<int> &traversedList=vector<int>(0)) {
        Node* tmp = search(key, root, traversedList);
        if (tmp) return tmp;
        else throw "Not found";
    }

public:
    void    add(K key, V value) {
        Entry<K,V>* newEntry = new Entry<K,V>(key, value);
        Node* flag = add(newEntry, root, nullptr); 
        if (!flag) throw "Duplicate key";
        else splay(flag);
    }
    void    add(Entry<K,V>* entry) {
        Node* flag = add(entry, root, nullptr); 
        if (!flag) throw "Duplicate key";
        else splay(flag);
    }
    void    remove(K key) {
        Node* z = BKUsearch(key, root);
        if (!root || !z) return ;

        splay(z);

        Entry<K,V>* result = z->entry;
        
        if (!z->right) {replace(z, z->left); }
        else if (!z->left) {replace(z, z->right); }
        else {
            Node *y = root->left;
            while (y->right) y = y->right; //splaying maxL
            if (y->parent != root) {
                replace(y, y->left);
                y->left = z->left;
                y->left->parent = y;
            }
            replace(z, y);
            y->right = z->right;
            y->right->parent = y;
        }
        
        delete z;
        if (!result) throw "Not found";
    }
    V       search(K key) {
        Node* tmp = search(key, root);
        if (tmp) {
            splay(tmp);
            return root->entry->value;
        }
        else throw "Not found";
    }

    void    traverseNLR (void (*func)(K key, V value), Node* &root) {
        if (!root) return ;
        func(root->entry->key, root->entry->value);
        traverseNLR(func, root->left);
        traverseNLR(func, root->right);
    }
    void    traverseNLR(void (*func)(K key, V value)) {
        traverseNLR(func, root);
    }

    void    clear();
};

// int main() {

//     SplayTree<int,int> SPTree;
//     int a[] = {1,5,3,2,4,9,6,10};
//     for (int i = 0; i < 8; ++i) {
//         SPTree.add(a[i],a[i]);
//         cout << "- - - - - - - - - - - - - - - - - - -" << endl;
//     }
//     SPTree.printTreeStructure();

//     for (int i = 0; i < 8; ++i) {
//         SPTree.remove(a[i]);
//         SPTree.printTreeStructure();
//         cout << "- - - - - - - - - - - - - - - - - - -" << endl;
//     }

//     return 0;
// }
//dont delete entry 2gether with remove