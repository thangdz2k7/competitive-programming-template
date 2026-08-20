// p_tree

#define left _left_
#define right _right_

static char buf[1000 << 20];
void* operator new(size_t s) {
    static size_t i = sizeof buf;
    assert(s < i);
    return (void*) &buf[i -= s];
}
void operator delete(void*) {}

const pli inf = {1e12, -1};

int n, k;

struct Node {
    Node *left, *right;
    pli Min = inf;

    Node (pli val){
        left = nullptr; right = nullptr; Min = val;
    }

    Node (Node *left, Node *right){
        this -> left = left;
        this -> right = right;
        this -> Min = min(left -> Min, right -> Min);
    }
};

Node *T[2][N];

Node *build(int l = 0, int r = n - 1){
    if (l == r) return new Node(inf);

    int mid = l + r >> 1;
    return new Node(build(l, mid), build(mid + 1, r));
}

Node *update(Node *old, int u, pli val, int l = 0, int r = n - 1){
    if (l == r) return new Node(val);

    auto &left = old -> left;
    auto &right = old -> right;
    int mid = l + r >> 1;
    if (mid >= u) return new Node(update(left, u, val, l, mid), right);
    return new Node(left, update(right, u, val, mid + 1, r));
}

pli get(Node *cur, int u, int v, int l = 0, int r = n - 1){
    if (r < u || v < l) return inf;
    if (u <= l && r <= v) return cur -> Min;

    int mid = l + r >> 1;
    return min(get(cur -> left, u, v, l, mid), get(cur -> right, u, v, mid + 1, r));
}
