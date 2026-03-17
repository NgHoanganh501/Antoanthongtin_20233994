#include<iostream>
#include<string>
#include<limits>

using namespace std;

class Playfair {
    char key[5][5];
private:
    void generateKey(string keyword) {
        bool used[26] = { false };
        int row = 0, col = 0;

        for (char c : keyword) {
            if (c == 'J') c = 'I'; // 'I' và 'J' coi là 1 chữ cái
            if (!used[c - 'A']) {
                key[row][col] = c;
                used[c - 'A'] = true;
                col++;
                if (col == 5) {
                    col = 0;
                    row++;
                }
            }
        }

        for (char c = 'A'; c <= 'Z'; c++) {
            if (c == 'J') continue; // Bỏ qua 'J'
            if (!used[c - 'A']) {
                key[row][col] = c;
                used[c - 'A'] = true;
                col++;
                if (col == 5) {
                    col = 0;
                    row++;
                }
            }
        }
    }

    void prepareText(string &text) {
        string prepared;
        for (char c : text) {
            if (isalpha(c)) {
                c = toupper(c);
                if (c == 'J') c = 'I'; // 'J' và 'I' coi là 1 chữ cái
                prepared += c;
            }
        }
        text = prepared;
    }
public:
    Playfair(string keyword) {
        generateKey(keyword);
    }

    string encrypt(string plaintext) {
        prepareText(plaintext);
        string ciphertext;

        for (size_t i = 0; i < plaintext.length(); i += 2) {
            char a = plaintext[i];
            char b = (i + 1 < plaintext.length()) ? plaintext[i + 1] : 'X'; // Phụ thêm 'X' nếu là ký tự cuối cùng và không có cặp

            int rowA, colA, rowB, colB;
            for (int r = 0; r < 5; r++) {
                for (int c = 0; c < 5; c++) {
                    if (key[r][c] == a) {
                        rowA = r;
                        colA = c;
                    }
                    if (key[r][c] == b) {
                        rowB = r;
                        colB = c;
                    }
                }
            }

            if (rowA == rowB) { // Cùng hàng
                ciphertext += key[rowA][(colA + 1) % 5];
                ciphertext += key[rowB][(colB + 1) % 5];
            } else if (colA == colB) { // Cùng cột
                ciphertext += key[(rowA + 1) % 5][colA];
                ciphertext += key[(rowB + 1) % 5][colB];
            } else { // Khác hàng và cột
                ciphertext += key[rowA][colB];
                ciphertext += key[rowB][colA];
            }
        }

        return ciphertext;
    }
};

int main() {
    string keyword, plaintext;
    cout << "Enter the keyword: ";
    cin >> keyword;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter the plaintext: ";
    getline(cin, plaintext);

    Playfair cipher(keyword);
    string ciphertext = cipher.encrypt(plaintext);
    cout << "Ciphertext: " << ciphertext << endl;

    return 0;
}