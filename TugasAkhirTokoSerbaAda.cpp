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

bool kodeProdukAda (string kode) {
    Produk* temp = head;
    while (temp) {
        if (temp->kode == kode) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void tambahproduk(string kode, string nama, string kategori, int stok, double harga) {
    if (kode.empty() || nama.empty() || kategori.empty() || stok < 0 || harga < 0) {
        cout << "Data yang Anda inputkan tidak boleh kosong." << endl;
        return;
    }

    if (stok < 0 || harga < 0) {
        cout << "Stok dan Harga itu harus bernilai positif." << endl;
        return;
    }
    if (kodeProdukAda(kode)) {
        cout << "Kode produk sudah digunakan. Masukkan kode yang lain." << endl;
        return;
    }

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

void editproduk(string kode) {
    Produk* temp = head;
    while (temp) {
        if (temp->kode == kode) {
            cout << "Masukkan Nama Produk: ";
            cin.ignore(); getline(cin, temp->nama);
            cout << "Masukkan Kategori Produk: ";
            getline(cin, temp->kategori);
            cout << "Masukkan Stok Produk: ";
            while (!(cin >> temp->stok) || temp->stok< 0) {
                cout<< "Input tidak valid! Masukkan stok dengan angka positif: ";
                cin.ignore(1000, '\n');
            }

            cout << "Masukkan Harga Produk: ";
            while (!(cin >> temp->harga) || temp->harga < 0) {
                cout << "Input tidak valid. Masukkan harga dengan angka positif: ";
                cin.clear(); cin.ignore(1000, '\n');
            }

            cout << "Data Produk Berhasil Diubah." << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Produk Tidak Ditemukan" << endl;
}

void tampilkanproduk() {
    if (!head) {
        cout << "Produk tidak ada dalam data atau kosong." << endl;
        return;
    }
    cout << "\n=== Daftar Produk ===\n";
    cout << "Kode\t Nama \t\t Kategori \t Stok \t Harga \n";
    cout << "-----------------------------------------------\n";

    Produk* temp = head;
    while (temp) {
        cout << temp->kode << "\t"
            << temp->nama << "\t" 
            << temp->kategori << "\t"
            << temp->stok << "\t"
            << temp->harga << "\n";
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

void urutkanProduk(int pilihan) {
    if (!head || !head->next) return;

    bool swapped;
    do {
        swapped = false;
        Produk* current = head;

        while (current && current->next) {
            Produk* next = current->next;
            bool harusTukar = false;

            if (pilihan == 1 && current->nama > next->nama) {
                harusTukar = true;
            } else if (pilihan == 2 && current->harga > next->harga) {
                harusTukar = true;
            }

            if (harusTukar) {
                // Tukar semua data
                swap(current->kode, next->kode);
                swap(current->nama, next->nama);
                swap(current->kategori, next->kategori);
                swap(current->stok, next->stok);
                swap(current->harga, next->harga);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);

    if (pilihan == 1)
        cout << "Produk berhasil diurutkan berdasarkan nama (A-Z).\n";
    else if (pilihan == 2)
        cout << "Produk berhasil diurutkan berdasarkan harga (terendah-tertinggi).\n";
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

void simpankeFile(){
    ofstream file ("data_produk.txt");
    if (!file) {
        cout << "Gagal membuka file untuk menyimpan data." << endl;
        return;
    } 
    Produk* temp = head;
    while (temp) {
        file << temp->kode << ";" << temp->nama << ";" << temp->kategori << ";" << temp->stok << ";" << temp->harga << endl;
        temp = temp->next;
    }
    file.close();
    cout << "Data produk berhasil disimpan ke file. \n" << endl;
}

void bacafile(){
    ifstream file("data_produk.txt");
    if (!file.is_open()) {
        cout << "Gagal membuka file untuk membaca data." << endl;
        return;
    }

    string kode, nama, kategori;
    int stok;
    double harga;

    while (getline (file, kode, ';' )){
        getline (file, nama, ';');
        getline (file, kategori, ';');
        if (!(file >> stok)) {
            cout << "Gagal membaca stok produk." << endl;
            break;
        }
        file.ignore(1);
        if (!(file >> harga)) {
            cout << "Gagal membaca harga produk." << endl;
            break;
        }
        file.ignore(1);

        if (!kode.empty() && !nama.empty() && !kategori.empty() && stok >= 0 && harga >= 0) {
        tambahproduk(kode, nama, kategori, stok, harga);
        }
    }
    file.close();
    cout << "Data produk berhasil dibaca dari file. \n" << endl;
}

void menu() {
        int opsi;
        do{
            cout << "\n ====================================\n";
            cout << "|  SISTEM INVENTARIS TOKO SERBA ADA  |\n";
            cout << "\n ====================================\n";
            cout << "| 1. Tambah Produk                  |\n";
            cout << "| 2. Tampilkan Produk               |\n";
            cout << "| 3. Urutkan Produk                 |\n";
            cout << "| 4. Cari Produk                    |\n";
            cout << "| 5. Edit Produk                    |\n";
            cout << "| 6. Hapus Produk                   |\n";
            cout << "| 7. Simpan ke File                 |\n";
            cout << "| 8. Baca dari File                 |\n";
            cout << "| 9. Keluar                         |\n";
            cout << "\n ====================================\n";
            cout << "Masukkan pilihan (1-9): ";
            
            if (!(cin >> opsi)) {
                cout<< "Error! Masukkan angka 1-9 saja." << endl;
                cin.clear(); cin.ignore(1000, '\n');
                continue; 
            };
            cin.ignore();

            switch (opsi) {
                case 1: {
                        int jumlah;
                        cout << "Masukkan Jumlah Produk Yang Ingin ditambahkan:  ";
                        while (!(cin >> jumlah) || jumlah <= 0) {
                            cout << "Input tidak valid. Masukkan Jumlah Produk Kembali: ";
                            cin.clear(); cin.ignore(1000, '\n');
                        }
                        cin.ignore();

                        for (int i = 1; i <= jumlah; ++i) {
                            string kode, nama, kategori;
                            int stok;
                            double harga;

                            cout << "\n=== Input Produk ke-" << i << " ===\n";

                            cout << "Masukkan Kode Produk: ";
                            getline(cin, kode);
                            cout << "Masukkan Nama Produk: ";
                            getline(cin, nama);
                            cout << "Masukkan Kategori Produk: ";
                        getline(cin, kategori);

                        cout << "Masukkan Stok Produk: ";
                        while (!(cin >> stok) || stok < 0) {
                            cout << "Input tidak valid. Masukkan stok dengan angka positif: ";
                            cin.clear(); cin.ignore(1000, '\n');
                        }

                        cout << "Masukkan Harga Produk: ";
                        while (!(cin >> harga) || harga < 0) {
                            cout << "Input tidak valid. Masukkan harga dengan angka positif: ";
                            cin.clear(); cin.ignore(1000, '\n');
                        }

                        cin.ignore();
                        tambahproduk(kode, nama, kategori, stok, harga);
                    }
                    break;
                }


                case 2:
                    tampilkanproduk();
                    break;

                case 3: {
                    int sortPilihan;
                    cout << "\n=== Urutkan Produk ===\n";
                    cout << "1. Berdasarkan Nama (A-Z)\n";
                    cout << "2. Berdasarkan Harga (Termurah-Termahal)\n";
                    cout << "Masukkan pilihan: ";
                    while (!(cin >> sortPilihan) || (sortPilihan !=1 && sortPilihan != 2)) {
                        cout << "Input tidak valid. Masukkan 1 atau 2: ";
                        cin.clear(); cin.ignore(1000, '\n');
                    }
                    urutkanProduk(sortPilihan);
                    break;
                }

                case 4: {
                    string kode;
                    cout << "Masukkan Kode Produk yang dicari: ";
                    cin.ignore(); getline(cin, kode);
                    cariproduk(kode);
                    break;
                }
                case 5: {
                    string kode;
                    cout << "Masukkan Kode Produk yang ingin diedit: ";
                    cin.ignore(); getline(cin, kode);
                    editproduk(kode);
                    break;
                }
                case 6: {
                    string kode;
                    cout << "Masukkan Kode Produk yang ingin dihapus: ";
                    cin.ignore(); getline(cin, kode);
                    hapusproduk(kode);
                    break;
                }
                case 7:
                   simpankeFile();
                   break;
                case 8:
                   bacafile();
                   break;
                case 9:
                   cout << "Terima kasih telah menggunakan sistem ini." << endl;
                   break;
                default:
                   cout << "Pilihan tidak valid. Silakan coba lagi. \n" << endl;
            }
        } while (opsi !=9);
            }
        int main(){
        menu(); 
        return 0;
}