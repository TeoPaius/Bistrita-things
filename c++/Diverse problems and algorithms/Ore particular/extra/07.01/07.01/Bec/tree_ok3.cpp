// OK - pe toate testele

 
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

ofstream fout("tree.out");
#define INF 99999

typedef vector<int> VI;

int n, P;
VI t;
VI nr;     // nr[x] - nr noduri ale intregului subarbore cu rad in x
VI sons;
int minim = INF;

void Read();
VI DF(int x);


int main()
{
	Read();
	
	if ( P == n )
	{
		cout << 0 << '\n';
		fout.close();
		return 0;
	}
	VI res = DF(1);
	
	cout << minim << '\n';
	
	fout.close();
	return 0;
}

VI DF(int x)
{
	nr[x]++;
	VI X(n + 1, INF);
	X[1] = sons[x]; // ca sa raman doar cu nodul x in subarbore, tai muchiile spre fii
	if ( x != 1 ) 
		X[1]++;  // daca nu e radacina, tai si nodul spre tata
	for (int f = 1; f <= n; ++f )
		if ( t[f] == x )
		{	
			VI F = DF(f);
			nr[x] += nr[f];
			VI Aux(X); // initializez cu ce am de la fii lui x, procesati inaintea lui f, apoi pun ce obtin de la f
			
			for ( int j = 1; j <= nr[f]; ++j )  // pt fiecare subarbore cu j noduri din f
				for ( int i = 1; i + j  <= nr[x]; i++ )  // pt fiecare numar de noduri i, posibil in x 
				{
					if ( X[i] == INF ) continue;
					if ( F[j] == INF ) continue;
					if ( Aux[i + j] > X[i] + F[j] - 2  ) // -2 pt ca a[x][i] si a[f][j] sunt calculate cu taierea muchiei intre x si f
						Aux[i + j] = X[i] + F[j] - 2;				
				}
			X = Aux;	
		}
	
	minim = min(minim, X[P]);
	return X;
}

void Read()
{
	ifstream fin("0-TREE.in");
	int son, father;
	cin >> n >> P;
	nr.resize(n + 1);
	t.resize(n + 1);
	sons.resize(n + 1);
	for ( int i = 1; i < n; ++i )
	{
		cin >> father >> son;
		t[son] = father;
		sons[father]++;
	}
	
	fin.close();
}
	


