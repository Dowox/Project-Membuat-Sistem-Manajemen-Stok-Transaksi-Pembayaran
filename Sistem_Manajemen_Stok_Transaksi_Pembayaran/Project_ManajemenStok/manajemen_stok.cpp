#include "database.h"
#include <cstdlib>  // Untuk system()

// ==================== ALUR MANAJEMEN STOK ====================

// [P1/S2] - PROSES BARANG MASUK
void prosesBarangMasuk(vector<Barang>& data) {
    system("cls");
    cout << "\n+------------------------------------------------------------------+\n";
    cout << "¦                       BARANG MASUK                              ¦\n";
    cout << "+------------------------------------------------------------------+\n";
    
    Barang barang;
    
    // [S2] - Input data barang
    cout << "\n[INPUT DATA BARANG]\n";
    cout << "--------------------------------------------------------------------\n";
    cout << "Kode Barang    : ";
    cin >> barang.kode;
    cout << "Nama Barang    : ";
    clearInputBuffer();
    getline(cin, barang.nama);
    cout << "Jumlah Masuk   : ";
    cin >> barang.jumlah;
    cout << "Harga Satuan   : Rp ";
    cin >> barang.harga;
    cout << "Stok Minimum   : ";
    cin >> barang.stok_minimum;
    
    // [P4] - Tambah stok di database
    Barang* existing = cariBarang(data, barang.kode);
    if (existing != nullptr) {
        existing->jumlah += barang.jumlah;
        cout << "\n? Stok barang '" << existing->nama << "' berhasil ditambahkan!\n";
        cout << "  Stok lama: " << existing->jumlah - barang.jumlah << " ? Stok baru: " << existing->jumlah << endl;
    } else {
        data.push_back(barang);
        cout << "\n? Barang baru '" << barang.nama << "' berhasil ditambahkan!\n";
    }
    
    // [P5] - Cetak laporan masuk
    cout << "\n+------------------------------------------------------------------+\n";
    cout << "¦                    LAPORAN BARANG MASUK                         ¦\n";
    cout << "¦------------------------------------------------------------------¦\n";
    cout << "¦ Kode Barang  : " << left << setw(45) << barang.kode << " ¦\n";
    cout << "¦ Nama Barang  : " << setw(45) << barang.nama << " ¦\n";
    cout << "¦ Jumlah Masuk : " << setw(45) << barang.jumlah << " ¦\n";
    cout << "¦ Harga Satuan : Rp " << setw(42) << fixed << setprecision(2) << barang.harga << " ¦\n";
    if (existing != nullptr) {
        cout << "¦ Total Stok   : " << setw(45) << existing->jumlah << " ¦\n";
    }
    cout << "+------------------------------------------------------------------+\n";
    
    // Simpan ke database
    simpanDataBarang(data);
}

// [P2/S3] - PROSES BARANG KELUAR
void prosesBarangKeluar(vector<Barang>& data) {
    system("cls");
    cout << "\n+------------------------------------------------------------------+\n";
    cout << "¦                       BARANG KELUAR                             ¦\n";
    cout << "+------------------------------------------------------------------+\n";
    
    string kode, tujuan;
    int jumlah;
    
    // [S3] - Input data
    cout << "\n[INPUT DATA PENGELUARAN]\n";
    cout << "--------------------------------------------------------------------\n";
    cout << "Kode Barang    : ";
    cin >> kode;
    cout << "Jumlah Keluar  : ";
    cin >> jumlah;
    cout << "Tujuan         : ";
    clearInputBuffer();
    getline(cin, tujuan);
    
    Barang* barang = cariBarang(data, kode);
    
    if (barang == nullptr) {
        cout << "\n? ERROR: Barang dengan kode '" << kode << "' tidak ditemukan!\n";
        return;
    }
    
    // [IF2] - Cek stok cukup
    if (barang->jumlah >= jumlah) {
        // [P6] - Kurangi stok
        barang->jumlah -= jumlah;
        
        // [P7] - Cetak laporan
        cout << "\n+------------------------------------------------------------------+\n";
        cout << "¦                    LAPORAN BARANG KELUAR                        ¦\n";
        cout << "¦------------------------------------------------------------------¦\n";
        cout << "¦ Kode Barang  : " << left << setw(45) << kode << " ¦\n";
        cout << "¦ Nama Barang  : " << setw(45) << barang->nama << " ¦\n";
        cout << "¦ Jumlah Keluar: " << setw(45) << jumlah << " ¦\n";
        cout << "¦ Tujuan       : " << setw(45) << tujuan << " ¦\n";
        cout << "¦ Stok Sisa    : " << setw(45) << barang->jumlah << " ¦\n";
        cout << "+------------------------------------------------------------------+\n";
        
        cout << "\n? Barang berhasil dikeluarkan!\n";
    } else {
        // [P8] - Tampilkan "Stok tidak cukup"
        cout << "\n? ERROR: Stok tidak cukup!\n";
        cout << "  Stok tersedia: " << barang->jumlah << endl;
        cout << "  Jumlah diminta: " << jumlah << endl;
        return;
    }
    
    // Simpan ke database
    simpanDataBarang(data);
}

// [P3/P9/IF3] - PROSES CEK STOK
void prosesCekStok(vector<Barang>& data) {
    system("cls");
    
    // [P9] - Tampilkan data stok
    tampilkanDataStok(data);
    
    // [IF3] - Cek stok minimum
    cekDanTampilkanPeringatanStok(data);
}

// [IF4] - Tanya kembali ke menu
bool tanyaKembaliKeMenu() {
    cout << "\n--------------------------------------------------------------------\n";
    cout << "Kembali ke menu utama? (y/n): ";
    char pilihan;
    cin >> pilihan;
    clearInputBuffer();
    return (tolower(pilihan) == 'y');
}

// ==================== MAIN PROGRAM ====================
int main() {
    vector<Barang> data;
    int pilihan;
    
    do {
        // [START] - Sistem mulai
        system("cls");
        cout << "+------------------------------------------------------------------+\n";
        cout << "¦              SISTEM MANAJEMEN STOK - KELOMPOK 1                 ¦\n";
        cout << "¦------------------------------------------------------------------¦\n";
        cout << "¦                                                                  ¦\n";
        cout << "¦  1. BARANG MASUK                                                ¦\n";
        cout << "¦  2. BARANG KELUAR                                               ¦\n";
        cout << "¦  3. CEK STOK                                                    ¦\n";
        cout << "¦  4. KELUAR                                                      ¦\n";
        cout << "¦                                                                  ¦\n";
        cout << "¦------------------------------------------------------------------¦\n";
        cout << "¦                Kelompok 1 - 01TPLP001                           ¦\n";
        cout << "+------------------------------------------------------------------+\n";
        
        // [S1] - Pilih menu
        cout << "\nPilih menu (1-4): ";
        cin >> pilihan;
        
        // Baca data terbaru dari database
        data = bacaDataBarang();
        
        // [IF1] - Cek pilihan angka
        switch (pilihan) {
            case 1:  // [JIKA PILIH 1] - BARANG MASUK
                prosesBarangMasuk(data);
                break;
                
            case 2:  // [JIKA PILIH 2] - BARANG KELUAR
                prosesBarangKeluar(data);
                break;
                
            case 3:  // [JIKA PILIH 3] - CEK STOK
                prosesCekStok(data);
                break;
                
            case 4:  // [FINISH] - Keluar
                cout << "\n+------------------------------------------------------------------+\n";
                cout << "¦                      PROGRAM SELESAI                           ¦\n";
                cout << "+------------------------------------------------------------------+\n";
                return 0;
                
            default:
                cout << "\n? ERROR: Pilihan tidak valid! Harap pilih 1-4.\n";
                clearInputBuffer();
                cout << "\nTekan Enter untuk melanjutkan...";
                cin.get();
                continue;
        }
        
        // [IF4] - Tanya kembali ke menu (kecuali untuk pilihan 4)
        if (pilihan != 4) {
            if (!tanyaKembaliKeMenu()) {
                cout << "\n+------------------------------------------------------------------+\n";
                cout << "¦                      PROGRAM SELESAI                           ¦\n";
                cout << "+------------------------------------------------------------------+\n";
                break;
            }
        }
        
    } while (true);
    
    return 0;
}
