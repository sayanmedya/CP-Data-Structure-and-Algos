#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef map<int,int> mii;
#define M 1000000007
#define pi 3.141592653589793
#define pb push_back
#define all(v) v.begin(),v.end()
#define F first
#define S second
#define tc int t;cin>>t;while(t--)
#define pqmax priority_queue<int>
#define pqmin priority_queue<int,vector<int>,greater<int>>
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL)

// reference : Competitive Programming 3 by Steven Halim & Felix Halim
class dsu {
private:
    vi p, rank;
public:
    dsu(int n) {
        p.assign(n, 0);
        rank.assign(n, 0);
        for (int i = 0;i < n;i++)
            p[i] = i;
    }
    int findSet(int a) {
        return p[a] == a ? a : p[a] = findSet(p[a]); // storing root/parent of the set and returning the value : 'path compression'
    }
    bool isSameSet(int a, int b) {
        return findSet(a) == findSet(b);
    }
    void unionSet(int a, int b) {
        int x = findSet(a), y = findSet(b);
        rank[x] < rank[y] ? p[x] = y : p[y] = x; // checking rank of a set to minimize height : 'union by rank'
        if (rank[x] == rank[y])
            rank[x]++;
    }
};

int main()
{
    // usage of dsu class is given below
    dsu a(5); // creates 5 disjoint sets i.e {{0}, {1}, {2}, {3}, {4}}
    a.unionSet(1, 4); // now the structue becomes {{0}, {1,4}, {2}, {3}}
    a.unionSet(3, 4); // now the structue becomes {{0}, {1,4,3}, {2}}
    a.isSameSet(2, 0); // returns false
    a.isSameSet(4, 1); // returns true;
    cout << "Happy Coding\n";
    return 0;
}
