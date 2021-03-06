// OK pe toate testele

// sa schimb cin, cout in fin fout
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

ofstream fout("tree.out");

const int Inf = 0x3f3f3f3f;
typedef vector<int> VI;

int n, P;
VI t, sons, nr;     // nr[x] - nr noduri ale intregului subarbore cu rad in x;
vector<VI> a;          // a[i][j] - nr min de arce care tr taiate pentru ca sa obtin un subarbore cu rad in x, avand j noduri

void Read();
void DF(int x);

int main()
{
	Read();
	
	if ( P == n )
	{
		cout << 0 << '\n';
		fout.close();
		return 0;
	}
	
	a = vector<VI>(n + 1, VI(n + 1, Inf));
	
	DF(1);
	
	int edges = Inf;
	for (int i = 1; i <= n; ++i )
		 edges = min(edges, a[i][P]);
		 
	cout << edges << '\n';
	
	fout.close();
	return 0;
}

void DF(int x)
{
	nr[x]++;
	a[x][1] = sons[x]; // ca sa raman doar cu nodul x in subarbore, tai muchiile spre fii
	if ( x != 1 ) 
		a[x][1]++;  // daca nu e radacina, tai si nodul spre tata
	for (int f = 1; f <= n; ++f )
		if ( t[f] == x )
		{	
			DF(f);
			nr[x] += nr[f];
			VI Aux(a[x]); // initializez cu ce am de la fii lui x, procesati inaintea lui f, apoi pun ce obtin de la f
			
			for ( int i = 2; i <= nr[x]; ++i )  // pt fiecare subarbore cu i noduri din x
				for ( int j = 1; j < i && j  <= nr[f]; j++ )  // pt fiecare numar de noduri j, posibil in f 
				{
					if ( a[x][i - j] == Inf ) continue;
					if ( a[f][j] == Inf ) continue;
					if ( Aux[i] > (a[x][i - j] - 1) + (a[f][j] - 1)  ) // -2 pt ca a[x][i] si a[f][j] sunt calculate cu taierea muchiei intre x si f
						Aux[i] = a[x][i - j] + a[f][j] - 2;				
				}
			a[x] = Aux;	
		}
}

void Read()
{
	ifstream fin("0-TREE.in");
	int son, father;
	cin >> n >> P;
	nr = t = sons = VI(n + 1);
	for ( int i = 1; i < n; ++i )
	{
		cin >> father >> son;
		t[son] = father;
		sons[father]++;
	}
	
	fin.close();
}
	


