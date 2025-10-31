#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Struktur Node untuk Linked List
struct Node {
    string nama;
    int harga;
    int jumlah;
    Node* next;
};

// Fungsi untuk menambah barang di depan
void tambahDepan(Node** head, string nama, int harga, int jumlah) {
    Node* newNode = new Node();
    newNode->nama = nama;
    newNode->harga = harga;
    newNode->jumlah = jumlah;
    newNode->next = *head;
    *head = newNode;
}

// Fungsi untuk menambah barang di belakang
void tambahBelakang(Node** head, string nama, int harga, int jumlah) {
    Node* newNode = new Node();
    newNode->nama = nama;
    newNode->harga = harga;
    newNode->jumlah = jumlah;
    newNode->next = nullptr;

    if (*head == nullptr) {
        *head = newNode;
        return;
    }

    Node* temp = *head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Fungsi untuk menambah barang setelah barang tertentu
void tambahSetelah(Node* head, string namaSebelum, string nama, int harga, int jumlah) {
    Node* temp = head;
    while (temp != nullptr && temp->nama != namaSebelum) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Barang '" << namaSebelum << "' tidak ditemukan. Tidak dapat menambah setelahnya." << endl;
        return;
    }

    Node* newNode = new Node();
    newNode->nama = nama;
    newNode->harga = harga;
    newNode->jumlah = jumlah;
    newNode->next = temp->next;
    temp->next = newNode;
}

// Fungsi untuk menghapus barang berdasarkan nama
void hapus(Node** head, string nama) {
    if (*head == nullptr) {
        cout << "Keranjang kosong. Tidak ada barang yang bisa dihapus." << endl;
        return;
    }

    // Jika barang yang dihapus adalah head
    if ((*head)->nama == nama) {
        Node* temp = *head;
        *head = (*head)->next;
        delete temp;
        cout << "Barang '" << nama << "' berhasil dihapus." << endl;
        return;
    }

    // Cari barang di tengah atau belakang
    Node* temp = *head;
    while (temp->next != nullptr && temp->next->nama != nama) {
        temp = temp->next;
    }

    if (temp->next == nullptr) {
        cout << "Barang '" << nama << "' tidak ditemukan." << endl;
        return;
    }

    Node* nodeToDelete = temp->next;
    temp->next = temp->next->next;
    delete nodeToDelete;
    cout << "Barang '" << nama << "' berhasil dihapus." << endl;
}

// Fungsi untuk menampilkan keranjang belanja
void tampilkanKeranjang(Node* head) {
    if (head == nullptr) {
        cout << "Keranjang kosong." << endl;
        return;
    }

    Node* temp = head;
    int totalBarang = 0;
    long long totalHarga = 0;

    while (temp != nullptr) {
        cout << temp->nama << " - Rp" << temp->harga << " x" << temp->jumlah << endl;
        totalBarang += temp->jumlah;
        totalHarga += (long long)temp->harga * temp->jumlah;
        temp = temp->next;
    }

    cout << "Total barang: " << totalBarang << endl;
    cout << "Total harga: Rp" << fixed << setprecision(0) << totalHarga << endl;
}

// Fungsi untuk membersihkan memori
void bersihkanMemori(Node** head) {
    Node* temp;
    while (*head != nullptr) {
        temp = *head;
        *head = (*head)->next;
        delete temp;
    }
}

int main() {
    Node* head = nullptr;

    int jumlahBarang;
    cout << "Masukkan jumlah barang awal: ";
    cin >> jumlahBarang;
    cin.ignore(); // Untuk mengabaikan newline setelah cin

    for (int i = 1; i <= jumlahBarang; i++) {
        string nama;
        int harga, jumlah;

        cout << "Barang " << i << ":" << endl;
        cout << "Nama: ";
        getline(cin, nama);
        cout << "Harga: ";
        cin >> harga;
        cout << "Jumlah: ";
        cin >> jumlah;
        cin.ignore(); // Untuk mengabaikan newline

        tambahBelakang(&head, nama, harga, jumlah);
    }

    

    char pil;
    do{
    string nama, setelah;
    int harga, jumlah;
    
    cout << "Apakah ingin menambah barang barang? (y/n): ";
    cin >> pil;

     if (pil == 'y' || pil == 'Y') {
        cout << " 1. Tambah di depan " << endl;
        cout << " 2. Tambah di antara/ di tengah " << endl;
        cout << " 3. Tambah di belakang " << endl;

        int no;
        cout << "Pilihan : ";
        cin >> no;
        system("cls");

        if (no == 1){
                cout << "Nama: ";
                cin >> nama;
                cout << "Harga: ";
                cin >> harga;
                cout << "Jumlah: ";
                cin >> jumlah;
                cin.ignore(); // Untuk mengabaikan newline
                tambahDepan(&head, nama, harga, jumlah);
        }
         else if (no == 2){
                cout << "Nama: ";
                getline(cin, nama);
                cout << "Harga: ";
                cin >> harga;
                cout << "Jumlah: ";
                cin >> jumlah;
                cout << " Diletakkan setelah : ";
                cin >> setelah;
                cin.ignore(); // Untuk mengabaikan newline
                tambahSetelah(head, nama,setelah, harga, jumlah);
        }
         else if (no == 3){
                cout << "Nama: ";
                getline(cin, nama);
                cout << "Harga: ";
                cin >> harga;
                cout << "Jumlah: ";
                cin >> jumlah;
                cin.ignore(); // Untuk mengabaikan newline
                tambahBelakang(&head, nama, harga, jumlah);
        }
    }
}while( pil == 'y' || pil == 'Y');

    char pilihan;
    cout << "Apakah ingin menghapus barang? (y/n): ";
    cin >> pilihan;
    cin.ignore(); // Untuk mengabaikan newline

    if (pilihan == 'y' || pilihan == 'Y') {
        string namaHapus;
        cout << "Masukkan nama barang yang ingin dihapus: ";
        getline(cin, namaHapus);
        hapus(&head, namaHapus);
    }

    // Tampilkan keranjang setelah operasi
    tampilkanKeranjang(head);

    // Bersihkan memori
    bersihkanMemori(&head);

    return 0;
}
