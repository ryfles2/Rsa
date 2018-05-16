#include <iostream>
#include <string>
#include <vector>

using namespace std;

long operation(long p, long g, long a) { // q - modulo, g - podstawa, a - potega(wykładnik)//szybkie potegowanie modulo
	long result = 1;
	long x = g % p;
	for (long i = 1; i <= a; i <<= 1) {//tak jak by razy 2
		if ((a&i) != 0) {//jeżźlei a na i-tej pozycji jest różne od zera to
			result *= x;
			result %= p;
		}
		x *= x;
		x %= p;
	}
	return  result;
}

long NWD(long a, long b) { // a liczba której odwrotnosc modulo szukamy, b to modulo
	long u, w, x, z, q;			//a * x mod ileś =1
	u = 1L;
	w = a;
	x = 0;
	z = b;
	while (w != 0) {
		if (w < z) {
			q = u;
			u = x;
			x = q;
			q = w;
			w = z;
			z = q;
		}
		q = w / z;
		u -= q * x;
		w -= q * z;
	}
	if (z == 1)
	{
		if (x < 0)
			x += b;
		return x;
	}
	return 0;
}

long algorythmEkulides(long a, long b) {//NWD
	long a1, b1;
	a1 = a;
	b1 = b;
	while (a1 != b1) {
		if (a1 < b1)
			b1 -= a1;
		else
			a1 -= b1;
	}
	return a1;
}

void RSA() {////////////////////////////////////////////////////Algorytm do szyfrowania deszyfrowania
	int p, q, n, e, fi;
	long e1, d, currentchar;
	string message, encryptMessage;
	vector<long> encryptArray;
	vector<long> decryptArray;
	
	cout << "p: " << endl;//liczba pierwsza
	cin >> p;
	cout << "q: " << endl;//liczba pierwsza
	cin >> q;
	n = p*q;
	cout << "n: " << n << endl;
	fi = (p - 1)*(q - 1);
	cout << "e: " << endl;
	cin >> e;//e musi mieć wspólny dzielnik z fi większy od 1 i powinna być niepażysta
	while (algorythmEkulides(e, fi) != 1 && e<fi)
	{
		cin >> e;
	}
	d = NWD(e, fi);//rozwiązywanie równania =1 
	cout << "D: " << d << endl;
	cout << "Please enter your message: " << endl;
	cin >> message;

	//rzutowanie na liczbę i kodowanie kluczem publicznym
	for (int i = 0; i < message.length(); i++)
	{
		currentchar = (long)message[i];//aktualna litera do potęgi e modulo n
		currentchar = operation(n, currentchar, e);
		encryptArray.push_back(currentchar);
	}

	for (int i = 0; i < encryptArray.size(); i++) 
	{
		cout << encryptArray[i] << " ";//wyświetla zaszyfrowaną wiadomość
	}
	cout << endl;

	for (int i = 0; i < encryptArray.size(); i++) 
	{//odszyfrowawyanie klucz prywatny
		currentchar = encryptArray[i];//zaszyfrowana litera modulo d do potęgi n
		currentchar = operation(n, currentchar, d);
		decryptArray.push_back(currentchar);
	}

	for (int i = 0; i < decryptArray.size(); i++)
	{
		char temp = (char)(decryptArray[i]);
		cout << temp;
	}
	cout << endl;
}







void main()
{
	RSA();
	system("pause");
}