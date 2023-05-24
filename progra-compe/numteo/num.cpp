#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <queue>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(decltype((cont).begin()) it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;

// Primero recordar las reglas de aritmetica modular:
// Si trabajamos en modulo m y suponemos que 0<=a,b<m
// En caso de que a o b no esten en el rango [0,m), podemos hacer: (a%m+m)%m
// El primer %m obliga al numero a estar en el rango (-m,m), el +m lo forza a no ser negativo y el segundo %m lo forza al rango [0,m)
// suma: a+b -> (a+b)%m
// resta: a-b -> (a-b+m)%m
// multiplicacion: a*b -> a*b%m
// division: a/b -> a*b^-1 -> a*b^(phi(m)-1)%m
// Recordar que b y m tienen que ser coprimos, sino no se puede obtener su inverso multiplicativo
// Recordar que si m es primo phi(m)=m-1, por lo tanto b^(m-2) es el inverso multiplicativo de b

// Usualmente cuando se trabaja con modulos se da 10^9+7, o 10^9+9
#define MOD 1000000007

// maxN usualmente vale 10^6 (Notar que por las pruebas que puse para demostrar que todo esta bien, si se elige un numero grande, como 10^6 se puede tardar incluso minutos en correr)
// No tengan miedo a modificar estas variables a romper el programa, asi se aprende :D
#define maxN 1000

// a*b%m;
// O(logN)
ll mulmod(ll a, ll b, ll m) {
	ll ret = 0;
	while (b) {
		if (b & 1) ret = (ret + a) % m; // Problema interesante: supongamos que ret+a puede excederse de 2^64 bits, como hacerle para no tener overflow??
		a = (a << 1) % m; 
		b >>= 1;
	}
	return ret;
}

// x^n mod m (tambien se usa la notacion x**n mod m)
// O(logN)
ll fastPow(ll x, ll n, ll m) {
	ll ret = 1;
	while (n) {
		if (n & 1) ret = mulmod(ret,x, m); // Recordar que solo lo tenemos que usar si MOD>2^32, sino usar ret=ret*x%m;, ya que es tiempo constante
		x = mulmod(x,x, m);
		n >>= 1;
	}
	return ret;
}

// Greatest Common Divisor
// O(logN)
ll gcd(ll a, ll b) {
	if (b) return gcd(b, a%b);
	return a;
}

// El extended GCD tiene la propiedad que g=a*inva+b*invb (donde g es el gcd, a y b se pasan a la funcion e inv son numeros que se obtienen y representan inverso multiplicativo al trabajar en modulos (inva es a^-1 en mod b y invb es b^-1 en mod a)
// Supongamos que a y b son coprimos, entonces g=1:
// Si trabajamos en mod a: 1 = b*invb
// Entonces invb es el inverso multiplicativo de b en mod a.
// Si trabajamos en mod b: 1 = a*inva
// De igual manera, inva es el inverso multiplicativo de a en modulo b
// Como nota #1 si a y b no son coprimos, g!=1
// inva es el inverso multiplicativo de a/g mod b/g (ya que si dividimos ambos lados de la ecuacion por g, ahora a y b seran coprimos y g=1)
// Como nota #2 inva e invb pueden ser negativos
// Por ende, si queremos trabajar con ellos como inversos multiplicativos ocupamos asegurarnos que sean positivos, ver ejemplo de uso mas abajo en main
// O(logN)
ll extendedGCD(ll a, ll b, ll &inva,ll &invb) {
	if (b) {
		ll g = extendedGCD(b, a%b, invb, inva);
		invb = invb - a / b*inva;
		return g;
	}
	inva = 1, invb = 0;
	return a;
}

// fac tiene N! (N factorial) y rfac tiene el inverso multiplicativo de N!
ll fac[maxN], rfac[maxN];

// Formula de combinatoria, la vamos a usar despues
// Tambien conocida como N choose K	
ll NK(int n, int k) {
	return fac[n] * rfac[k] % MOD*rfac[n - k] % MOD;
}

// Miller-Rabin primality test
// Over all Time Complexity is 9*(logN)**2, it can be said it's (logN)**3 because 9 is a 'big' constant
bool isPrime(ll n) {
	if (n<2) return false; //There shouldn't be any negative numbers here, though
	ll d = n - 1;
	int s = 0;
	while (d % 2 == 0) {
		s++;
		d >>= 1;
	}
	// It's garanteed that these values will work for any number smaller than 3*10**18 (3 and 18 zeros)
	int a[9] = { 2, 3, 5, 7, 11, 13, 17, 19, 23 };
	FOR(i, 0, 9) if (a[i] == n) return true;
	FOR(i, 0, 9) {
		ll fp = fastPow(a[i], d, n);
		bool inv = fp != 1;
		FOR(j, 0, s) {
			if (fp == n - 1) inv = false;
			fp = mulmod(fp, fp, n);
		}
		if (inv) return false;
	}
	return true;
}

// p[i]==true if i is prime, otherwise false
bool p[maxN];

// f[t] contiene el numero primo mas pequeño que divide a t
int f[maxN];

// Dos constantes pseudo aleatorias, ayudan a generar otros numeros pseudoaleatorios
ll A, B;

// Guarda los factores de un numero obtenidos mediante pollard rho
vector<ll> factorsPollardRho;

ll pseudoRandom(ll x, ll n) {
	return (mulmod(x, (x + A), n) + B) % n;
}

// Una funcion que se basa en el concepto de la paradoja del cumpleaños y otros conceptos para factorizar un numeros (es no deterministico, pero su complejidad es aproximadamente O(N^1/4))
void pollardRho(ll n) {
	if (n == 1) return;
	if (isPrime(n)) {
		factorsPollardRho.pb(n);
		return;
	}
	ll d = n, x, y;
	while (d == n) {
		d = 1;
		x = y = 2;
		A = 2 + rand() % (n - 2);
		B = 2 + rand() % (n - 2);

		while (d == 1) {
			x = pseudoRandom(x, n);
			y = pseudoRandom(pseudoRandom(y, n), n);
			d = gcd(abs(x - y), n);
		}
	}

	//if (n / d != d) ligera optimizacion, descomentar si solo nos interesan los factores primos, no cuantas veces aparecen
		pollardRho(n / d);
	pollardRho(d);
}

int main() {
	memset(p, true, sizeof(p));
	p[0] = p[1] = false;
	// Demostracion de complejidad de tiempo
	// sum(1, maxN) N/i=> N*sum(1, maxN) 1/i=> N*logN
	// integral(1/X)=> logX
	// O(NlogN)
	FOR(i, 2, maxN) {
		// Recordar que si ponemos la condicion de si son primos se vuelve O(NloglogN)
		if(p[i]) for (int j = 2; i*j < maxN; j++) p[i*j] = false;
	}

	// Guardar los primos en un vector
	vi primes;
	FOR(i, 2, maxN) {
		if (p[i]) primes.push_back(i);
	}

	// Ejemplo de uso de inversos multiplicativos
	int constanteArbitraria = min((int) primes.size(), 1000); // Esta constante implica que revisaremos que el extendedGCD y el fastPow funcionan para los primeros 1000 primos o los que tengamos
	FOR(i, 0, constanteArbitraria) {
		FOR(j, i + 1, constanteArbitraria) {
			ll t1, t2;
			extendedGCD(primes[i], primes[j], t1, t2);
			// Notar que t1 y t2 pueden ser negativos, asi que nos aseguramos que sean positivos
			t1 = (t1 + primes[j]) % primes[j];
			t2 = (t2 + primes[i]) % primes[i];
			if (fastPow(primes[i], primes[j] - 2, primes[j]) != t1 || fastPow(primes[j], primes[i] - 2, primes[i]) != t2) {
				// No deberia entrar aqui nunca, solo es como para demostrar que ambos dan lo mismo
				cout << "Si el programa entra a este if significa que el inverso multiplicativo obtenido mediante fermat's little theorem da un valor diferente al inverso multiplicativo obtenido por el extended euclidean" << endl;
			}
		}
	}
	
	// Obtener f[t], el primo mas chico que divide a f[t]
	memset(f, -1, sizeof(f));
	FOR(i, 2, maxN) {
		if (f[i] == -1) {
			for (int j = 1; i*j < maxN; j++) if (f[i*j] == -1) f[i*j] = i;
		}
	}

	// Sera el numero a factorizar
	int N = 420;

	// Obtener factores de N (y los almacenamos de 2 maneras diferentes, usualmente se necesita solo 1, pero puse las 2 para que vean diferentes alternativas que tienen, tambien pueden crear la suya si lo creen conveniente)
	vi fac;
	vii fac2;
	int t = N;
	int last = -1;
	while (f[t] != -1) {
		fac.push_back(f[t]);
		if (f[t] == last) {
			fac2[fac2.size() - 1].second++;
		}
		else fac2.push_back(ii(f[t], 1));
		last = f[t];
		t /= f[t];
	}

	// Obtener divisores (dado que fac2 tiene primero el divisor y luego la cantidad de veces que aparece)
	vi divisors;
	divisors.push_back(1);
	FOR(i, 0, fac2.size()) {
		int s = divisors.size(), n = 1;
		FOR(j, 0, fac2[i].second) {
			n *= fac2[i].first;
			FOR(k, 0, s) divisors.push_back(divisors[k] * n);
		}
	}
	sort(divisors.begin(), divisors.end());

	// phi(N) dado fac, que son los factores sorteados, tambien podemos usar fac2 o la funcion unique y evitamos las condiciones adentro del for
	// Recordar que phi(N) es el euler totient de N, e indica cuantos numeros enteros positivos existen que son coprimos con N (no comparten ningun factor primo en comun)
	int phiN = N;
	FOR(i, 0, fac.size()) {
		if (!i || fac[i] != fac[i-1])
			phiN = phiN / fac[i] * (fac[i] - 1);
	}

	// Miller rabin Primality test
	// O(log^3(N))
	FOR(i, 0, maxN) {
		if (p[i] != isPrime(i)) {
			// Jamas deberiamos entrar aqui
			cout << "Esto es un error ya que sieve of Eratosthenes y miller rabin dieron resultados diferentes" << endl;
		}
	}

	// Pollard rho
	// O(N^1/4)
	pollardRho(N);
	sort(factorsPollardRho.begin(), factorsPollardRho.end());
	FOR(i, 0, fac.size()) {
		if (fac[i] != factorsPollardRho[i]) {
			cout << "Esto es un error ya que los factores siempre deberian ser iguales y estar ordenados" << endl;
		}
	}
	return 0;
}
