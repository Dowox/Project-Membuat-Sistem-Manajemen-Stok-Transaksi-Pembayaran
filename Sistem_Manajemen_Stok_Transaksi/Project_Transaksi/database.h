#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cctype>

using namespace std;

// STRUKTUR DATA BARANG
struct Barang {
    string kode;
    string nama;
    int jumlah;
    double harga;
    int stok_minimum;
};

// ==================== FUNGSI DATABASE ====================

// [P4/P6/P12] - Baca data dari file database
vector<Barang> bacaDataBarang() {
    vector<Barang> data;
    ifstream file("../database_barang.txt");
    
    if (file.is_open()) {
        Barang b;
        while (file >> b.kode >> b.nama >> b.jumlah >> b.harga >> b.stok_minimum) {
            data.push_back(b);
        }
        file.close();
    }
    return data;
}

// [P4/P6/P12] - Simpan data ke file database
void simpanDataBarang(vector<Barang> data) {
    ofstream file("../database_barang.txt");
    
    if (file.is_open()) {
        for (const auto& b : data) {
            file << b.kode << " " << b.nama << " " 
                 << b.jumlah << " " << b.harga << " " 
                 << b.stok_minimum << endl;
        }
        file.close();
    }
}

// [P1/P2] - Cari barang berdasarkan kode
Barang* cariBarang(vector<Barang>& data, string kode) {
    for (auto& b : data) {
        if (b.kode == kode) {
            return &b;
        }
    }
    return nullptr;
}

// [P9] - Tampilkan semua data stok
void tampilkanDataStok(vector<Barang> data) {
    cout << "\n+------------------------------------------------------------------+\n";
    cout << "¦                      DATA STOK BARANG                           ¦\n";
    cout << "¦------------------------------------------------------------------¦\n";
    cout << left << setw(10) << "KODE" 
         << setw(20) << "NAMA BARANG" 
         << setw(10) << "STOK" 
         << setw(15) << "HARGA" 
         << setw(15) << "STOK MIN" << endl;
    cout << "¦------------------------------------------------------------------¦\n";
    
    for (const auto& b : data) {
        cout << left << setw(10) << b.kode 
             << setw(20) << b.nama 
             << setw(10) << b.jumlah 
             << setw(15) << fixed << setprecision(2) << b.harga 
             << setw(15) << b.stok_minimum << endl;
    }
    cout << "+------------------------------------------------------------------+\n";
}

// [IF3] - Cek stok minimum dan tampilkan peringatan
void cekDanTampilkanPeringatanStok(vector<Barang> data) {
    bool adaPeringatan = false;
    
    for (const auto& b : data) {
        if (b.jumlah <= b.stok_minimum) {
            if (!adaPeringatan) {
                cout << "\n+------------------------------------------------------------------+\n";
                cout << "¦                   PERINGATAN STOK MINIMUM!                       ¦\n";
                cout << "¦------------------------------------------------------------------¦\n";
                adaPeringatan = true;
            }
            cout << "¦ • " << left << setw(15) << b.kode 
                 << setw(20) << b.nama 
                 << "Stok: " << setw(3) << b.jumlah 
                 << " (Min: " << b.stok_minimum << ")" 
                 << right << setw(10) << " ¦" << endl;
        }
    }
    
    if (adaPeringatan) {
        cout << "+------------------------------------------------------------------+\n";
    } else {
        cout << "\n? Tidak ada barang dengan stok minimum\n";
    }
}

// Membersihkan buffer input
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

#endif
