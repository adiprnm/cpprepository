/**********************************************************************
 * Nama			: Adi Purnama
 * NPM			: 140810150002
 * Kelas		: Teknik Informatika B
 * Mata Kuliah	: Kriptografi
 * Nama Program	: Enkripsi dan dekripsi menggunakan metode shift
 * Deskripsi	: Mengenkripsi dan mendekripsi pesan dengan metode
 * 				  shift menggunakan rumus Ex(t) = t + key mod 26 dan
 * 				  Dx(u) = u - key mod 26
 *********************************************************************/


#include <iostream>
#include <string.h>
using namespace std;

char shift_encrypt(char c, int key);
char shift_decrypt(char c, int key);

int main()
{
    string plaintext, ciphertext, decrypted;
	int key;
	
	cout << "=== Caesar Cipher ===" << endl;
    cout << "Ciphertext: ";
    getline(cin, plaintext);
    cout << "Key: ";
    cin >> key;
    
	cout << "\n=== Result ===" << endl; 
	ciphertext = "";
	
    for (unsigned int i = 0; i < plaintext.length(); i++)
        ciphertext += shift_encrypt(plaintext.at(i), key);
    cout << "Encrypted: " << ciphertext << endl;
    
	decrypted = "";
	
    for (unsigned int i = 0; i < ciphertext.length(); i++)
        decrypted += shift_decrypt(ciphertext.at(i), key);
    cout << "Decrypted: " << decrypted << endl;
	return 0;
}
 
char shift_encrypt(char c, int key)
{
    if (isalpha(c))
    {
		if (c >= 'a' && c <= 'z')
			c = (((c-97)+key) % 26) + 97;
        else if (c >= 'A' && c <= 'Z')
			c = (((c-65)+key) % 26) + 65;
    }
    return c;
}

char shift_decrypt(char c, int key)
{
    if( isalpha(c) )
    {
		if (c >= 'a' && c <= 'z')
		{
			c = (c - 97) - key;
			if (c < 'a')
				c += 26;
			c = (c % 26) + 97;
		}
			
        else if (c >= 'A' && c <= 'Z')
		{
			c = (c - 65) - key;
			if (c < 'a')
				c += 26;
			c = (c % 26) + 65;
		}
    }
    return c;
}

