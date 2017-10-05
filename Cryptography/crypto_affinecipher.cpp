/**********************************************************************
 * Nama		: - Adi Purnama (140810150002)
 * 			  - M. Rifky Suryantono (140810150015)
 * 			  - Cipto Tri Utomo (140810150024)
 *			  - Ahmad Jihan Atqia (140810150045)
 *			  - Fatan Aufa Ahdiy (140810150064)
 * Kelas		: Teknik Informatika A dan B
 * Mata Kuliah	: Kriptografi
 * Nama Program	: Enkripsi dan dekripsi menggunakan affine cipher
 * Deskripsi	: Mengenkripsi dan mendekripsi pesan dengan affine
 * 			  cipher menggunakan rumus Ek(x) = ax + b mod 26 dan
 * 			  Dk(y) = a^(-1)*(y-b) mod 26.
 *********************************************************************/

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

int gcd(int a, int b)
{
    while(a != b)
    {
        if(a > b)
            a = a - b;
        else
            b = b - a;
    }
    return a;
}

int modInverse(int a, int b){
    int b0 = b, t, q;
    int x0 = 0, x1 = 1;
    if (b == 1) return 1;
    while (a > 1) {
        q = a / b;
        t = b, b = a % b, a = t;
        t = x0, x0 = x1 - q * x0, x1 = t;
    }
    if (x1 < 0) x1 += b0;
    return x1;
}

char enkripsiPesan(char c, int a, int b)
{
	if (isalpha(c))
    {
		if (c >= 'a' && c <= 'z')
			c = ((a*(c-97)+b) % 26) + 97;
        else if (c >= 'A' && c <= 'Z')
			c = ((a*(c-65)+b) % 26) + 65;
    }
    return c;
}
 
char dekripsiPesan(char c, int a, int b)
{
if( isalpha(c) )
    {
		if (c >= 'a' && c <= 'z')
			c = (modInverse(a, 26) * (26 + c - 97 - b) % 26) + 97;
        else if (c >= 'A' && c <= 'Z')			
			c = (modInverse(a, 26) * (26 + c - 65 - b) % 26) + 65;
    }
    return c;
}
string kontenPesan (char namaFile[])
{
	string retval = "";
	string msg = "";
	ifstream infile;
	infile.open (namaFile);
	while (!infile.eof())
    {
	    getline(infile, msg);
		retval = retval + msg + "\n";
    }
	infile.close();
	return retval;
}


int main()
{
	string pesanTeks;
	string ciphertext, decryptedtext;
	char namaFile[100];
	int a, b, gcd_val;
	
	cout << "*** Affine Cipher ***" << endl;
	cout << "a = "; cin >> a;
	gcd_val = gcd(a, 26);
	while (gcd_val != 1) {
		cout << "a is not coprime of 26!" << endl;
		cout << "a = "; cin >> a;
		gcd_val = gcd(a, 26);
	}
	cout << "b = "; cin >> b;
	cout << "File name: "; cin >> namaFile;
	ifstream ifile(namaFile);
	if (!ifile) {
		cout << "File not found!" << endl;
	}
	else {
		pesanTeks = kontenPesan (namaFile);
		cout << "\nPlaintext:\n" << pesanTeks;
		for (int i = 0; i < pesanTeks.length(); ++i) {
			ciphertext += enkripsiPesan(pesanTeks.at(i), a, b);
		}
		cout << "\nE(Plaintext):\n" << ciphertext;
		for (int i = 0; i < ciphertext.length(); ++i) {
			decryptedtext += dekripsiPesan(ciphertext.at(i), a, b);
		}
		cout << "\nD(E(Plaintext)):\n" << decryptedtext << endl;
		return 0;
	}
}
