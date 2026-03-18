#include <iostream>
#include <string>
#include <iomanip>

using namespace std;


// Truyền mảng K và chiều dài mảng K vào hàm
void mini_RC4(const int K[], int key_len, const string& plaintext) {
    int S[10];
    int N = 10;
    int data_len = plaintext.length();
    
    // Khởi tạo mảng trạng thái S
    for (int i = 0; i < N; i++) {
        S[i] = i;
    }
    
    // Lập lịch khóa
   
    int j = 0;
    for (int i = 0; i < N; i++) {
        j = (j + S[i] + K[i % key_len]) % N;
        
        // Swap S[i] và S[j] bằng biến tạm
        int temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }
    
    // In mảng S sau KSA
    cout << "Mang S sau KSA: [";
    for(int i = 0; i < N; i++) {
        cout << S[i] << (i == N - 1 ? "" : ", ");
    }
    cout << "]\n";
    
   
    // Cấp phát mảng động chứa dòng khóa và bản mã dựa trên chiều dài bản rõ
    int* keystream = new int[data_len];
    unsigned char* ciphertext = new unsigned char[data_len];
    
    int x = 0, y = 0;
    for (int k = 0; k < data_len; k++) {
        x = (x + 1) % N;
        y = (y + S[x]) % N;
        
        // Swap S[x] và S[y]
        int temp = S[x];
        S[x] = S[y];
        S[y] = temp;
        
        int t = (S[x] + S[y]) % N;
        int key_byte = S[t];
        
        // Lưu giá trị vào mảng
        keystream[k] = key_byte;
        ciphertext[k] = plaintext[k] ^ key_byte; // Phép XOR-bitwise
    }
    
    // In dòng khóa Keystream
    cout << "Dong khoa Key(t): [";
    for(int i = 0; i < data_len; i++) {
        cout << keystream[i] << (i == data_len - 1 ? "" : ", ");
    }
    cout << "]\n";
    
    // In bản mã C(t) dưới dạng ký tự 
    cout << "Ban ma C(t) (Text): ";
    for (int i = 0; i < data_len; i++) {
        cout << ciphertext[i];
    }
    cout << "\n";
    
    // Giải phóng bộ nhớ mảng động 
    delete[] keystream;
    delete[] ciphertext;
}

int main() {
    int K[] = {2, 4, 1, 7};
    int key_len = 4; 
    string plaintext = "cybersecurity";
    
    cout << "--- Thuat toan RC4 ---" << endl;
    cout << "Ban ro (m): " << plaintext << endl;

    mini_RC4(K, key_len, plaintext);
    
    return 0;
}