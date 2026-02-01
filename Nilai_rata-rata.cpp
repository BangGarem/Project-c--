#include <iostream>
#include <string>
#include <limits>
using namespace std;

int main() {
    int jumlahPelajaran;
    cout << "Masukkan jumlah pelajaran: ";
    while(!(cin >> jumlahPelajaran) || jumlahPelajaran <= 0) {
        cout << "Input salah! Masukkan angka positif: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string namaPelajaran;
    double nilai, total = 0;

    for(int i = 1; i <= jumlahPelajaran; i++) {
        cout << "\nMasukkan nama pelajaran ke-" << i << ": ";
        cin.ignore(); // membersihkan newline
        getline(cin, namaPelajaran);

        cout << "Masukkan nilai " << namaPelajaran << ": ";
        while(!(cin >> nilai) || nilai < 0 || nilai > 100) {
            cout << "Input salah! Masukkan nilai 0-100: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        total += nilai;
    }

    double rataRata = total / jumlahPelajaran;
    cout << "\n==============================\n";
    cout << "Nilai rata-rata dari semua pelajaran: " << rataRata << endl;
    cout << "==============================\n";

    system("pause"); // <-- ini bikin console menunggu sebelum menutup
    return 0;
}
