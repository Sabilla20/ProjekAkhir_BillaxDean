#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct Produk {
    string kode, nama, kategori;
    int stok;
    double harga;
    Produk* next;
};

Produk* head = nullptr;

void tambahproduk(string kode, string nama, string kategori, int stok, double harga) {
    Produk* baru = new Produk{kode, nama, kategori, stok, harga, nullptr};

    if (!head) {
        head = baru;
    } else {
        Produk* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = baru;
    }

    cout << "Data Produk Berhasil Ditambahkan" << endl;
}

void tampilkanproduk() {
    Produk* temp = head;
    cout << left << setw(10) << "Kode" << setw(20) << "Nama" << setw(15) << "Kategori" << setw(10) << "Stok" << setw(10) << "Harga" << endl;
    while (temp) {
        cout << setw(10) << temp->kode << setw(20) << temp->nama << setw(15)
             << temp->kategori << setw(10) << temp->stok << setw(10) << temp->harga << endl;
        temp = temp->next;
    }
}

void cariproduk(string kode) {
    Produk* temp = head;
    while (temp) {
        if (temp->kode == kode) {
            cout << "Produk ditemukan: " << endl;
            cout << "Kode: " << temp->kode << ", Nama: " << temp->nama << ", Kategori: " << temp->kategori
                 << ", Stok: " << temp->stok << ", Harga: " << temp->harga << endl;
            return;
        }

        temp = temp->next;
    }

    cout << "Produk Tidak Ditemukan" << endl;
}

void editproduk(string kode) {
    Produk* temp = head;
    while (temp) {
        if (temp->kode == kode) {
            cout << "Masukkan Nama Produk: ";
            cin.ignore(); getline(cin, temp->nama);
            cout << "Masukkan Kategori Produk: ";
            getline(cin, temp->kategori);
            cout << "Masukkan Stok Produk: ";
            cin >> temp->stok;
            cout << "Masukkan Harga Produk: ";
            cin >> temp->harga;
            cout << "Data Produk Berhasil diubah." << endl;
            return;
        }

        temp = temp->next;
    }

    cout << "Produk Tidak Ditemukan" << endl;
}

void hapusproduk(string kode) {
    Produk *temp = head, *prev = nullptr;
    while (temp && temp->kode != kode) {
        prev = temp;
        temp = temp->next;
    }
        if (!temp) {
        cout << "Produk tidak ditemukan.\n";
        return;
    }
    if (!prev) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    
    delete temp;
    cout << "Data Produk Berhasil dihapus." << endl;
}