#include <iostream>
#include <limits> // untuk std::numeric_limits
using namespace std;

int main() {
    double a, b;
    char op;
    char lagi;

    cout << "=== Kalkulator Console Interaktif ===\n";

    do {
        cout << "\nMasukkan angka pertama: ";
        while(!(cin >> a)) { // validasi input
            cout << "Input salah! Masukkan angka: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Masukkan operator (+ - * /): ";
        cin >> op;

        cout << "Masukkan angka kedua: ";
        while(!(cin >> b)) { // validasi input
            cout << "Input salah! Masukkan angka: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "===========================\n";

        switch(op) {
            case '+': cout << a << " + " << b << " = " << a+b << endl; break;
            case '-': cout << a << " - " << b << " = " << a-b << endl; break;
            case '*': cout << a << " * " << b << " = " << a*b << endl; break;
            case '/': 
                if(b != 0) cout << a << " / " << b << " = " << a/b << endl;
                else cout << "Error: pembagian dengan nol!" << endl;
                break;
            default: cout << "Operator salah!" << endl;
        }

        cout << "===========================\n";
        cout << "Mau menghitung lagi? (y/n): ";
        cin >> lagi;

    } while(lagi == 'y' || lagi == 'Y');

    cout << "Terima kasih telah menggunakan kalkulator!\n";
    return 0;

}
