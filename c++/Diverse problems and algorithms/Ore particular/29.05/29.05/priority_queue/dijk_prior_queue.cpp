// 100p infoarena
#include <queue>
#include <fstream>
#include <vector>
using namespace std;
#define x first
#define dist second
#define nod pair<int, int>

const int NMAX = 50001, Inf = NMAX*1000;
int n, m, d[NMAX];
vector<nod> a[NMAX];

struct cmp {
     bool operator()(const int A, const int B){
       return d[A] > d[B];
     }
};

priority_queue< int, vector<int>, cmp > pq;
bool u[NMAX];

void read()
{
     int i, j, k;
     ifstream f("dijkstra.in");
     f >> n >> m;
     while (m--)
     {
           f >> i >> j >> k;
           a[i].push_back(make_pair(j, k));
     }
}

void dijkstra()
{
     int k;
     vector<nod>::iterator it;
     for (k = 1; k <= n; ++k)
      d[k] = Inf, u[k] = false;

     pq.push(1);
     d[1] = 0; u[1] = true;
     while ( !pq.empty() )
     {
           k = pq.top();  // O(1)
           pq.pop();      // log
           u[k] = false;
           for (it = a[k].begin(); it != a[k].end(); ++it)
             if (d[it->x] > d[k] + it->dist)
             {
             	d[it->x] = d[k] + it->dist;
               	if (!u[it->x]) pq.push(it->x), u[it->x] = true;
             }
     }
}

void write()
{
     ofstream g("dijkstra.out");
     for (int i = 2;i <= n; ++i)
     {
         if (d[i] == Inf) d[i] = 0;
         	g << d[i] << ' ';
     }
}

int main()
{
    read();
    dijkstra();
    write();
    return 0;
}

