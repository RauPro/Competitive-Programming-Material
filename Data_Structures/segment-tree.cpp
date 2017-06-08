#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

// Example of SegmentTree for rmq (minimum range query)
struct SegmentTree {
  vi st, A;            
  int n;
  int left (int p) { return p << 1; }
  int right(int p) { return (p << 1) + 1; }

  void build(int p, int l, int r) 
      if (l == r) { // base case
          st[p] = l; 
          return;
      }
      // recursive case
      int lp = left(p), rp = right(p);
      build(lp, l, (l+r)/2);
      build(rp, (l+r)/2+1, r);
      int i = st[lp], j = st[rp];
      st[p] = (A[i] <= A[j]) ? i : j;
  }

  void update_point(int p, int l, int r, int i, int val) {
    if (i > r or i < l) return; // check valid range
    if (l == r) { // base case
      A[i] = val;
      st[p] = l;
      return;
    }
    // recursive case
    int lp = left(p), rp = right(p);
    update_point(lp, l, (l+r)/2, i, val);
    update_point(rp, (l+r)/2+1, r, i, val);
    int i = st[lp], j = st[rp];
    st[p] = (A[i] <= A[j]) ? i : j;
  }

  int rmq(int p, int l, int r, int i, int j) {
      if (i > r or j < l) return -1; // check valid range
      if (i <= l && r <= j) return st[p]; // base case
      // recursive case
      int ii = rmq(left(p), l, (l+r)/2, i, j);
      int jj = rmq(right(p), (l+r)/2+1, r, i, j);
      if (ii == -1) return jj;
      if (jj == -1) return ii;
      return (A[ii] <= A[jj]) ? ii : jj; 
  }

  SegmentTree(const vi &_A) {
    A = _A; n = (int)A.size(); // copy content for local usage
    st.assign(4 * n, 0); // create large enough vector of zeroes
    build(1, 0, n - 1); // recursive build
  }

  int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); } // overloading

  int update_point(int i, int val) { // overloading
    return update_point(1, 0, n - 1, i, val); }
};
  
// usage
int main() {
  vi A = { 18, 17, 13, 19, 15, 11, 20 };
  SegmentTree st(A);
  st.rmq(1,3);
  st.update_point(5, 100);
  return 0;
}