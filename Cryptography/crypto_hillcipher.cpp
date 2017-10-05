#include <iostream>
#include <cmath>

#define MAX_SIZE 2

using namespace std;

string removeSpace(string str) {
	string result = "";
	for ( int i = 0; i < str.length(); i++ ) {
		if ( str.at(i) != ' ')
			result += str.at(i);
	}
	return result;
}

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

int mod(int a, int b)
{
	if (a < 0)
		return mod(b+a, b);
	return a % b;
}

int modPecahan(int a, int b)
{
	int q, c, d;
	int y = 1;
	int j = 0;
	c = a;
	d = b;
	int t[20];
	while (y != 0)
	{
		if ( j <= 1 )
		{
			t[j] = j;
		}
		else
		{
			q = d / c;
			y = d - q * c;
			d = c;
			c = y;
			t[j] = t[j-2] - (q * t[j-1]);
		}
		j++;
	}
	return mod(t[j-2], b);
}



int main() {
	string str;
	string plaintext;
	string ciphertext = "";
	int str_len;
	
	int matriks[MAX_SIZE][MAX_SIZE] ;
	int determinan;
	int invers[MAX_SIZE][MAX_SIZE];
	int temp[MAX_SIZE][MAX_SIZE];
	
	cout << "Hill Cipher 2 x 2 Matrix\n\n";
	
	cout << "String to be encrypted: ";
	getline(cin, str);
	
	plaintext = removeSpace(str);
	
	if ((plaintext.length()) % 2 != 0) {
		cout << "String cannot be encrypted";
		return 1;
	} else {
		for ( int i = 0; i < MAX_SIZE; i++ ) {
			for ( int j = 0; j < MAX_SIZE; j++ ) {
				cout << "Matrix [" << i+1 << "][" << j+1 << "]: ";
				cin >> matriks[i][j];
			}
		}
		
		char c[2];
		int temp[2];
		int adjoint[MAX_SIZE][MAX_SIZE];
		int plaintext_len = plaintext.length();
		
		// buat lowercase doang ah
		int i = 0;
		for ( int i = 0; i < plaintext_len; i += MAX_SIZE ) {
			c[0] = plaintext.at(i) - 97;
			c[1] = plaintext.at(i+1) - 97;
			temp[0] = (c[0] * matriks[0][0]) + (c[1] * matriks[1][0]);
			temp[1] = (c[0] * matriks[0][1]) + (c[1] * matriks[1][1]);
			ciphertext = ciphertext + (char)((temp[0] % 26) + 97);
			ciphertext = ciphertext + (char)((temp[1] % 26) + 97);
		}
		
		cout << "\nCiphertext: " << ciphertext << endl;
		
		adjoint[0][0] = matriks[1][1];
		adjoint[0][1] = -matriks[0][1];
		adjoint[1][0] = -matriks[1][0];
		adjoint[1][1] = matriks[0][0];
		
		determinan = (matriks[1][1]*matriks[0][0]) - (matriks[0][1]*matriks[1][0]);
				
		if (gcd(determinan, 26) != 1)
		{
			cout << "Error";
			return 2;
		}
		
		cout << determinan << endl;
		
		for ( int i = 0; i < MAX_SIZE; i++ ) {
			for ( int j = 0; j < MAX_SIZE; j++ ) {
				cout << modPecahan(determinan, 26) << endl;
				invers[i][j] = mod(modPecahan(determinan, 26) * adjoint[i][j], 26);
			}
		}
		
		for ( int i = 0; i < MAX_SIZE; i++ ) {
			for ( int j = 0; j < MAX_SIZE; j++ ) {
				cout << invers[i][j] << " ";
			}
			cout << endl;
		}
		
		string decrypted = "";
		
		for ( int i = 0; i < plaintext_len; i += MAX_SIZE ) {
			c[0] = ciphertext.at(i) - 97;
			c[1] = ciphertext.at(i+1) - 97;
			
			temp[0] = (c[0] * invers[0][0]) + (c[1] * invers[1][0]);
			while ( temp[0] < 0 )
				temp[0] += 26;
			
			temp[1] = (c[0] * invers[0][1]) + (c[1] * invers[1][1]);
			while ( temp[1] < 0 )
				temp[1] += 26;
		//	cout << temp[0] << " " << temp[1] << endl;
			decrypted = decrypted + (char)((temp[0] % 26) + 97);
			decrypted = decrypted + (char)((temp[1] % 26) + 97);
		}
		
		cout << "Decrypted: " << decrypted << endl;
	}
	return 0;
}
