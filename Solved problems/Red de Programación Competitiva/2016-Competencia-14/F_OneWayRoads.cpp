// tags: Max Flow, Bipartite Graph, Dinic, Binary Search
#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
typedef long long int ll;
typedef pair<int,int> pii;

int N, M, V;
int s, t;
vector<pii> edge_list;

struct Dinic {
  struct edge {
    int to, rev;
    ll f, cap;
  };

  vector<vector<edge>> g;
  vector<ll> dist;
  vector<int> q, work;
  int n, sink;

  bool bfs(int start, int finish) {
    dist.assign(n, -1);
    dist[start] = 0;
    int head = 0, tail = 0;
    q[tail++] = start;
    while (head < tail) {
      int u = q[head++];
      for (const edge &e : g[u]) {
        int v = e.to;
        if (dist[v] == -1 and e.f < e.cap) {
          dist[v] = dist[u] + 1;
          q[tail++] = v;
        }
      }
    }
    return dist[finish] != -1;
  }

  ll dfs(int u, ll f) {
    if (u == sink)
      return f;
    for (int &i = work[u]; i < (int)g[u].size(); ++i) {
      edge &e = g[u][i];
      int v = e.to;
      if (e.cap <= e.f or dist[v] != dist[u] + 1)
        continue;
      ll df = dfs(v, min(f, e.cap - e.f));
      if (df > 0) {
        e.f += df;
        g[v][e.rev].f -= df;
        return df;
      }
    }
    return 0;
  }

  Dinic(int n) {
    this->n = n;
    g.resize(n);
    dist.resize(n);
    q.resize(n);
  }

  void add_edge(int u, int v, ll cap) {
    edge a = {v, (int)g[v].size(), 0, cap};
    edge b = {u, (int)g[u].size(), 0, cap};
    g[u].push_back(a);
    g[v].push_back(b);
  }

  ll max_flow(int source, int dest) {
    sink = dest;
    ll ans = 0;
    while (bfs(source, dest)) {
      work.assign(n, 0);
      while (ll delta = dfs(source, LLONG_MAX))
        ans += delta;
    }
    return ans;
  }
};

ll max_flow(int maxdeg) {
  Dinic din(V);
  rep (e, 0, M-1) {
    int a = M + edge_list[e].first;
    int b = M + edge_list[e].second;
    din.add_edge(s, e, 1);
    din.add_edge(e, a, 1);
    din.add_edge(e, b, 1);
  }
  rep(i,0,N-1) {
    din.add_edge(M+i, t, maxdeg);
  }
  return din.max_flow(s, t);
}

int main() {
  scanf("%d%d", &N,&M);
  edge_list.resize(M);
  rep(i,0,M-1) {   
    int a,b; scanf("%d%d", &a, &b); --a; --b;
    edge_list[i] = pii(a,b);
  }
  V = N+M+2;
  s = V-2;
  t = V-1;

  int dmin = 0, dmax = N;
  while (dmin < dmax) {
    int m = (dmin+dmax)/2;
    if (max_flow(m) == M)
      dmax = m;
    else
      dmin = m+1;
  }
  int ans = dmin;
  printf("%d\n", ans);
  return 0;
}