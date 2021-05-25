#include <vector>
#include <iostream>

using namespace std;

struct Node{
    bool reverse = false;
    int sz = 1;
    int y, key;
    int value, mn;
    Node *left = nullptr;
    Node *right = nullptr;
    Node (int _key, int val) { key = _key, value = val, mn = val, y = rand();}
};

int get_size(Node *root){
    if (root == nullptr) return 0;
    return root->sz;
}

void upd(Node *t){
    if (t == nullptr) return;
    t->sz = 1 + get_size(t->left) + get_size(t->right);
    t->mn = t->value;
    if (t->left != nullptr)  t->mn = min(t->mn, t->left->mn);
    if (t->right != nullptr)  t->mn = min(t->mn, t->right->mn);
}

void push (Node *v) {
    if (v == nullptr) return;
    if (v->reverse) {
        swap(v->left, v->right);
        if (v->left)
            v->left->reverse ^= 1;
        if (v->right)
            v->right->reverse ^= 1;
    }
    v->reverse = false;
}

Node *merge(Node* v1, Node *v2){
    push(v1);
    push(v2);
    if (v1 == nullptr) return v2;
    if (v2 == nullptr) return v1;
    if (v1->y > v2->y){
        v1->right = merge(v1->right, v2);
        upd(v1);
        return v1;
    }
    else{
        v2->left = merge(v1, v2->left);
        upd(v2);
        return v2;
    }
}

pair<Node*, Node*> split (Node *p, int k) {
    if (!p) return {0, 0};
    push(p);
    if (get_size(p->left) < k) {
        pair<Node*, Node*> q = split(p->right, k - get_size(p->left) - 1);
        p->right = q.first;
        upd(p);
        return {p, q.second};
    }
    else {
        pair<Node*, Node*> q = split(p->left, k);
        p->left = q.second;
        upd(p);
        return {q.first, p};
    }
}

Node* insert(int x, int val, Node* root) {
    auto q = split(root, x);
    Node *tmp = new Node(x, val);
    root = merge(q.first, merge(tmp, q.second));
    upd(root);
    return root;
}

void output(Node *t) {
    if (!t) return;
    output(t->left);
    cout << t->value << " ";
    output(t->right);
}

void reverse_seg(Node* root, int l, int r) {
    pair<Node*, Node*> q1 = split(root, r);
    pair<Node*, Node*> q2 = split(q1.first, l);
    q2.second->reverse = true;
    root = merge(q2.first, merge(q2.second, q1.second));
}

int main(){
    vector<int> mas;
    int n, m;
    cin >> n >> m;
    Node *root = nullptr;
    int val;
    for (int i = 0; i < n; ++i) {
        cin >> val;
        root = insert(i + 1, val, root);
    }
    for (int i = 0; i < m; ++i) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 2) {
            Node *t1, *t2, *t3, *t4;
            pair<Node *, Node *> p1 = split(root, r);
            t1 = p1.first;
            t2 = p1.second;
            pair<Node *, Node *> p2 = split(t1, l - 1);
            t3 = p2.first;
            t4 = p2.second;
            cout << t4->mn << "\n";
            root = merge(merge(t3, t4), t2);
        } else {
            reverse_seg(root, l - 1, r);
            //output(root);
        }
    }
}