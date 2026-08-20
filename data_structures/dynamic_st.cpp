const int MAX = 1e5 + 5;

int root[MAX], NumNode = 0;
int Left[MAX], Right[MAX], lazy_add[MAX];

void Update(int &s, int l, int r, int y, int v, int k){
    if (!s) s = ++NumNode;
    if (y <= l && r <= v){
        lazy_add[s] += k;
        return;
    }
    
    int mid = l + r >> 1;
    if (mid >= y) Update(Left[s], l, mid, y, v, k);
    if (mid < v) Update(Right[s], mid + 1, r, y, v, k);
}

void update(int x, int u, int y, int v, int k){
    for (; x <= n; x += x&-x) 
        Update(root[x], 1, m, y, v, k);
    for (u = u + 1; u <= n; u += u&-u) 
        Update(root[u], 1, m, y, v, -k);
}

int Get(int &s, int l, int r, int y){
    if (!s) return 0;
    
    int mid = l + r >> 1;
    if (mid >= y) return lazy_add[s] + Get(Left[s], l, mid, y);
    return lazy_add[s] + Get(Right[s], mid + 1, r, y);
}

int get(int x, int y){
    int ans = 0;
    for (; x; x -= x&-x)
        ans += Get(root[x], 1, m, y);
    return ans;
}
