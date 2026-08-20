// DSU

struct DSU{
    vi par;

    DSU(int n){
        par.resize(n);
        for (int i = 0; i < n; ++ i) par[i] = i;
    }

    int find(int u){
        if (u == par[u]) return u;
        return par[u] = find(par[u]);
    }

    bool check(int u, int v){
        return find(u) == find(v);
    }

    void joint(int u, int v){
        u = find(u); v = find(v);
        if (u == v) return;
        par[u] = v;
    }
};
