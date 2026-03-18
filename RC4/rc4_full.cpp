#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {

    int S[256];
    int K_arr[256];
    int temp_K[256];
    string plaintext;
    int k_len;

    cout << "=== THUAT TOAN RC4 CHUAN (FIXED RESULT) ===" << endl;
    
   
    cout << "1. Nhap chuoi plaintext m(t): ";
    getline(cin, plaintext);

   
    cout << "2. Nhap so luong phan tu cua hat mam K: ";
    cin >> k_len;
    cout << "   Nhap " << k_len << " so cua K (vi du: 2 4 1 7): ";
    for (int i = 0; i < k_len; i++) {
        cin >> temp_K[i];
    }

    int n = 256;
    
    for (int i = 0; i < n; i++) {
        S[i] = i;
        K_arr[i] = temp_K[i % k_len];
    }

    int j = 0; 
    for (int i = 0; i < n; i++) {
        j = (j + S[i] + K_arr[i]) % n;
        // Swap
        int temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }

    
    cout << "\n[ Mang trang thai S sau KSA ]" << endl;
    cout << string(70, '-') << endl;
    for (int i = 0; i < n; i++) {
        cout << setw(4) << S[i];
        if ((i + 1) % 16 == 0) cout << endl;
    }
    cout << string(70, '-') << endl;

   
    int i_p = 0; 
    int j_p = 0;
    int m_len = plaintext.length();
    unsigned char cipher_text[1000]; 

    cout << "\n[ Bang ket qua ma hoa ]" << endl;
    cout << left << setw(8)  << "Ky tu" 
         << setw(12) << "m(t) ASCII" 
         << setw(12) << "KeyStream" 
         << setw(12) << "C(t) ASCII" 
         << "C(t) Char" << endl;
    cout << string(60, '-') << endl;

    for (int k = 0; k < m_len; k++) {
        i_p = (i_p + 1) % n;
        j_p = (j_p + S[i_p]) % n;
        
        // Hoan vi trong PRGA
        int temp = S[i_p];
        S[i_p] = S[j_p];
        S[j_p] = temp;

        int t = (S[i_p] + S[j_p]) % n;
        int keystream = S[t];

        // XOR bitwise
        unsigned char c_t = (unsigned char)plaintext[k] ^ (unsigned char)keystream;
        cipher_text[k] = c_t;

       
        cout << left << setw(8)  << plaintext[k]
             << setw(12) << (int)(unsigned char)plaintext[k]
             << setw(12) << keystream
             << setw(12) << (int)c_t;
        
        // In ky tu: neu la ky tu dieu khien (<32) thi hien dau '.'
        if (c_t >= 32) cout << (char)c_t;
        else cout << ".";
        
        cout << endl;
    }

    // 4. In chuoi ket qua cuoi cung
    cout << string(60, '-') << endl;
    cout << "=> Ban ma C(t): ";
    for (int k = 0; k < m_len; k++) {
        cout << (char)cipher_text[k];
    }
    cout << "\n============================================" << endl;

    return 0;
}