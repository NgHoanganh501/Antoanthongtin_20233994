
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MODPOLY = 1033; // m(x) = x^10 + x^3 + 1

// Chuyển số nguyên sang dạng biểu thức đa thức x^n
string to_poly_str(int n) {
    if (n == 0) return "0";
    if (n == 1) return "1";
    string res = "";
    bool first = true;
    for (int i = 10; i >= 0; i--) {
        if ((n >> i) & 1) {
            if (!first) res += " + ";
            if (i == 0) res += "1";
            else if (i == 1) res += "x";
            else res += "x^" + to_string(i);
            first = false;
        }
    }
    return res;
}

int get_degree(int n) {
    if (n == 0) return -1;
    int deg = 0;
    while (n >>= 1) deg++;
    return deg;
}

int poly_mul(int a, int b) {
    int res = 0;
    while (b > 0) {
        if (b & 1) res ^= a;
        a <<= 1;
        b >>= 1;
    }
    return res;
}

void poly_divmod(int a, int b, int &q, int &r) {
    q = 0; r = a;
    int deg_b = get_degree(b);
    if (deg_b <= -1) return;
    while (get_degree(r) >= deg_b) {
        int shift = get_degree(r) - deg_b;
        q ^= (1 << shift);
        r ^= (b << shift);
    }
}

void solve_full_table(int target, int m_poly) {
    int r_p2 = m_poly, r_p1 = target;
    int v_p2 = 1,      v_p1 = 0;
    int w_p2 = 0,      w_p1 = 1;

    cout << "\nTIM NGHICH DAO TRONG GF(2^10)" << endl;
    cout << "Dau vao: " << to_poly_str(target) << endl;
    cout << "Modulo: " << to_poly_str(m_poly) << endl;
    
    int w1 = 45, w2 = 45, w3 = 45;
    string line(w1 + w2 + w3 + 6, '=');
    string sep(w1 + w2 + w3 + 6, '-');

    cout << line << endl;
    cout << left << setw(w1) << "Calculate r_i and q_i" 
         << " | " << setw(w2) << "Calculate v_i" 
         << " | " << "Calculate w_i" << endl;
    cout << line << endl;
    
    // --- Tách hàng r_{-1} ---
    cout << left << setw(w1) << ("r_{-1} = " + to_poly_str(r_p2)) 
         << " | " << setw(w2) << "v_{-1} = 1" 
         << " | " << "w_{-1} = 0" << endl;
    cout << sep << endl;

    // --- Tách hàng r_{0} ---
    cout << left << setw(w1) << ("r_{0}  = " + to_poly_str(r_p1)) 
         << " | " << setw(w2) << "v_{0}  = 0" 
         << " | " << "w_{0}  = 1" << endl;
    cout << sep << endl;

    int i = 1;
    while (r_p1 != 0) {
        int q, r_curr;
        poly_divmod(r_p2, r_p1, q, r_curr);
        
        int v_curr = v_p2 ^ poly_mul(q, v_p1);
        int w_curr = w_p2 ^ poly_mul(q, w_p1);

        // Hiển thị dạng biểu thức trong bảng
        string r_text = "r_{" + to_string(i) + "} = " + to_poly_str(r_curr);
        string q_text = "q_{" + to_string(i) + "} = " + to_poly_str(q);
        string v_text = "v_{" + to_string(i) + "} = " + to_poly_str(v_curr);
        string w_text = "w_{" + to_string(i) + "} = " + to_poly_str(w_curr);

        cout << left << setw(w1) << r_text << " | " << setw(w2) << v_text << " | " << w_text << endl;
        cout << left << setw(w1) << q_text << " | " << setw(w2) << "" << " | " << endl;
        cout << sep << endl;

        r_p2 = r_p1; r_p1 = r_curr;
        v_p2 = v_p1; v_p1 = v_curr;
        w_p2 = w_p1; w_p1 = w_curr;
        i++;
    }

    // Bước kết luận mới thêm chuyển sang số 
    if (r_p2 == 1) {
        cout << "=> KET LUAN:" << endl;
        cout << "   - Dang bieu thuc: " << to_poly_str(w_p2) << endl;
        cout << "   - Dang so (Decimal): " << w_p2 << endl;
    }
}

int main() {
    int a, b;
    cout << "Nhap a: ";
    cin >> a;
    cout << "Nhap b: ";
    cin >> b;
    solve_full_table(a, MODPOLY);
    solve_full_table(b, MODPOLY);
    return 0;
}
