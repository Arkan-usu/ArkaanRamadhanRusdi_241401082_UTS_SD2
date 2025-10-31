#include <iostream>
#include <vector>
using namespace std;

struct Pesanan {
    string nama;
    string menu;
    int statusVIP;
    int waktuDatang;
};

int main() {
    int n;
    cout << "Masukkan jumlah pesanan: ";
    cin >> n;
    cin.ignore(); // bersihkan newline

    vector<Pesanan> daftarPesanan;

    // Input data pesanan
    for (int i = 0; i < n; i++) {
        Pesanan p;
        cout << "\nPesanan " << i + 1 << ":\n";
        cout << "Nama hewan: ";
        getline(cin, p.nama);
        cout << "Menu pesanan: ";
        getline(cin, p.menu);
        cout << "Status VIP (1=biasa, 2=VIP): ";
        cin >> p.statusVIP;
        cin.ignore();
        p.waktuDatang = i; // urutan datang
        daftarPesanan.push_back(p);
    }

    // Urutkan secara manual (bubble sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            bool tukar = false;

            // Jika status VIP lebih tinggi, geser ke depan
            if (daftarPesanan[j].statusVIP < daftarPesanan[j + 1].statusVIP) {
                tukar = true;
            }
            // Jika status sama, bandingkan waktu datang
            else if (daftarPesanan[j].statusVIP == daftarPesanan[j + 1].statusVIP &&
                     daftarPesanan[j].waktuDatang > daftarPesanan[j + 1].waktuDatang) {
                tukar = true;
            }

            if (tukar) {
                Pesanan temp = daftarPesanan[j];
                daftarPesanan[j] = daftarPesanan[j + 1];
                daftarPesanan[j + 1] = temp;
            }
        }
    }

    // Tampilkan hasil
    cout << "\n=== Urutan Pelayanan ===\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << daftarPesanan[i].nama << " - " << daftarPesanan[i].menu;
        if (daftarPesanan[i].statusVIP == 2)
            cout << " [VIP]";
        cout << endl;
    }

    return 0;
}
