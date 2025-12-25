#include "database.h"
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

// ==================== STRUKTUR TRANSAKSI ====================
struct Transaksi {
    string kode_barang;
    string nama_barang;
    int jumlah;
    double harga_satuan;
    double total_harga;
    string metode_bayar;
    string waktu_transaksi;
    double uang_dibayar;
    double kembalian;
};

// [P13] - Catat transaksi ke file log
void catatTransaksiKeLog(const Transaksi& t) {
    ofstream file("../transaksi_log.txt", ios::app);
    
    if (file.is_open()) {
        file << t.waktu_transaksi << " | "
             << t.kode_barang << " | "
             << t.nama_barang << " | "
             << t.jumlah << " | "
             << fixed << setprecision(2) << t.harga_satuan << " | "
             << t.total_harga << " | "
             << t.metode_bayar << " | "
             << t.uang_dibayar << " | "
             << t.kembalian << endl;
        file.close();
    }
}

// [P14] - Cetak struk transaksi
void cetakStrukTransaksi(const Transaksi& t) {
    system("cls");
    cout << "\n+------------------------------------------------------------------+\n";
    cout << "¦                      STRUK TRANSAKSI                           ¦\n";
    cout << "¦------------------------------------------------------------------¦\n";
    cout << "¦ Waktu        : " << left << setw(45) << t.waktu_transaksi << " ¦\n";
    cout << "¦ Kode Barang  : " << setw(45) << t.kode_barang << " ¦\n";
    cout << "¦ Nama Barang  : " << setw(45) << t.nama_barang << " ¦\n";
    cout << "¦ Jumlah Beli  : " << setw(45) << t.jumlah << " ¦\n";
    cout << "¦ Harga Satuan : Rp " << setw(42) << fixed << setprecision(2) << t.harga_satuan << " ¦\n";
    cout << "¦ Total Harga  : Rp " << setw(42) << t.total_harga << " ¦\n";
    cout << "¦ Metode Bayar : " << setw(45) << t.metode_bayar << " ¦\n";
    
    if (t.metode_bayar == "TUNAI") {
        cout << "¦ Uang Dibayar : Rp " << setw(42) << t.uang_dibayar << " ¦\n";
        cout << "¦ Kembalian    : Rp " << setw(42) << t.kembalian << " ¦\n";
    }
    
    cout << "¦------------------------------------------------------------------¦\n";
    cout << "¦           TERIMA KASIH TELAH BERBELANJA                         ¦\n";
    cout << "+------------------------------------------------------------------+\n";
}

// Mendapatkan waktu saat ini untuk transaksi
string getWaktuSekarang() {
    time_t now = time(0);
    tm* waktu = localtime(&now);
    
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", waktu);
    return string(buffer);
}

// [P4] - Proses pembayaran tunai
bool prosesPembayaranTunai(Transaksi& t) {
    cout << "\n[PROSES PEMBAYARAN TUNAI]\n";
    cout << "--------------------------------------------------------------------\n";
    
    // [S4] - Input uang dibayar
    cout << "Total yang harus dibayar: Rp " << fixed << setprecision(2) << t.total_harga << endl;
    cout << "Masukkan uang dibayar   : Rp ";
    cin >> t.uang_dibayar;
    
    // Validasi uang
    if (t.uang_dibayar < t.total_harga) {
        cout << "\n? ERROR: Uang tidak cukup! Kurang: Rp " 
             << fixed << setprecision(2) << (t.total_harga - t.uang_dibayar) << endl;
        return false;
    }
    
    // [P6] - Hitung kembalian
    t.kembalian = t.uang_dibayar - t.total_harga;
    
    // [P7] - Tampilkan kembalian
    cout << "\n? Pembayaran berhasil!\n";
    cout << "  Kembalian: Rp " << fixed << setprecision(2) << t.kembalian << endl;
    
    t.metode_bayar = "TUNAI";
    return true;
}

// [P5] - Proses pembayaran non-tunai
bool prosesPembayaranNonTunai(Transaksi& t) {
    system("cls");
    cout << "\n+------------------------------------------------------------------+\n";
    cout << "¦                  PEMBAYARAN NON-TUNAI                          ¦\n";
    cout << "¦------------------------------------------------------------------¦\n";
    cout << "¦                                                                  ¦\n";
    cout << "¦  Total yang harus dibayar: Rp " << left << setw(37) 
         << fixed << setprecision(2) << t.total_harga << " ¦\n";
    cout << "¦                                                                  ¦\n";
    
    // [P8] - Tampilkan kode QRIS/no rek
    cout << "¦  SILAKAN SCAN QRIS BERIKUT:                                     ¦\n";
    cout << "¦  +-----------------------------+                                ¦\n";
    cout << "¦  ¦ ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦ ¦                                ¦\n";
    cout << "¦  ¦ ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦ ¦                                ¦\n";
    cout << "¦  ¦ ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦ ¦                                ¦\n";
    cout << "¦  ¦ ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦ ¦                                ¦\n";
    cout << "¦  +-----------------------------+                                ¦\n";
    cout << "¦                                                                  ¦\n";
    cout << "¦  ATAU TRANSFER KE:                                               ¦\n";
    cout << "¦  Bank: BCA                                                       ¦\n";
    cout << "¦  No. Rek: 1234-5678-9012-3456                                   ¦\n";
    cout << "¦  Atas Nama: TOKO ABC                                            ¦\n";
    cout << "¦                                                                  ¦\n";
    cout << "+------------------------------------------------------------------+\n";
    
    // [IF4] - Tanya konfirmasi bayar
    char konfirmasi;
    cout << "\nSudah melakukan pembayaran? (y/n): ";
    cin >> konfirmasi;
    clearInputBuffer();
    
    if (tolower(konfirmasi) == 'y') {
        t.metode_bayar = "NON-TUNAI";
        t.uang_dibayar = t.total_harga;
        t.kembalian = 0.0;
        cout << "\n? Pembayaran berhasil dikonfirmasi!\n";
        return true;
    } else {
        // [P9] - Tunggu konfirmasi
        cout << "\n? Menunggu konfirmasi pembayaran...\n";
        cout << "Tekan Enter setelah melakukan pembayaran...";
        cin.get();
        
        // Kembali ke IF4
        cout << "\nKonfirmasi pembayaran? (y/n): ";
        cin >> konfirmasi;
        clearInputBuffer();
        
        if (tolower(konfirmasi) == 'y') {
            t.metode_bayar = "NON-TUNAI";
            t.uang_dibayar = t.total_harga;
            t.kembalian = 0.0;
            cout << "\n? Pembayaran berhasil dikonfirmasi!\n";
            return true;
        } else {
            cout << "\n? Pembayaran dibatalkan.\n";
            return false;
        }
    }
}

// ==================== MAIN PROGRAM ====================
int main() {
    // [START] - Transaksi mulai
    system("cls");
    cout << "+------------------------------------------------------------------+\n";
    cout << "¦          SISTEM TRANSAKSI PEMBAYARAN - KELOMPOK 1              ¦\n";
    cout << "¦------------------------------------------------------------------¦\n";
    cout << "¦                Kelompok 1 - 01TPLP001                           ¦\n";
    cout << "+------------------------------------------------------------------+\n\n";
    
    // [S1] - Input kode barang
    string kode_barang;
    cout << "[INPUT DATA TRANSAKSI]\n";
    cout << "--------------------------------------------------------------------\n";
    cout << "Masukkan Kode Barang: ";
    cin >> kode_barang;
    
    // [S2] - Input jumlah beli
    int jumlah_beli;
    cout << "Masukkan Jumlah Beli : ";
    cin >> jumlah_beli;
    
    // [P1] - Cek stok & harga
    vector<Barang> data = bacaDataBarang();
    Barang* barang = cariBarang(data, kode_barang);
    
    // Cek barang ditemukan
    if (barang == nullptr) {
        cout << "\n? ERROR: Barang dengan kode '" << kode_barang << "' tidak ditemukan!\n";
        cout << "Transaksi dibatalkan.\n";
        cout << "\nTekan Enter untuk keluar...";
        cin.get();
        cin.get();
        return 0;
    }
    
    // [IF1] - Cek stok cukup
    if (barang->jumlah < jumlah_beli) {
        // [P2] - Tampilkan "Stok tidak cukup"
        cout << "\n? ERROR: Stok tidak cukup!\n";
        cout << "  Stok tersedia: " << barang->jumlah << endl;
        cout << "  Jumlah diminta: " << jumlah_beli << endl;
        
        // [IF2] - Tanya kembali ke input
        char kembali;
        cout << "\nKembali ke input? (y/n): ";
        cin >> kembali;
        clearInputBuffer();
        
        if (tolower(kembali) == 'y') {
            // Kembali ke S1 (restart program)
            cout << "\n";
            main(); // Restart transaksi
            return 0;
        } else {
            // [FINISH1] - Transaksi batal
            cout << "\n? Transaksi dibatalkan.\n";
            cout << "\nTekan Enter untuk keluar...";
            cin.get();
            return 0;
        }
    }
    
    // [P3] - Hitung total harga (jika stok cukup)
    double total_harga = jumlah_beli * barang->harga;
    
    // Tampilkan detail transaksi
    cout << "\n+------------------------------------------------------------------+\n";
    cout << "¦                   DETAIL TRANSAKSI                            ¦\n";
    cout << "¦------------------------------------------------------------------¦\n";
    cout << "¦ Kode Barang  : " << left << setw(45) << barang->kode << " ¦\n";
    cout << "¦ Nama Barang  : " << setw(45) << barang->nama << " ¦\n";
    cout << "¦ Harga Satuan : Rp " << setw(42) << fixed << setprecision(2) << barang->harga << " ¦\n";
    cout << "¦ Jumlah Beli  : " << setw(45) << jumlah_beli << " ¦\n";
    cout << "¦ Total Harga  : Rp " << setw(42) << total_harga << " ¦\n";
    cout << "+------------------------------------------------------------------+\n";
    
    // [S3] - Pilih metode bayar
    int metode;
    cout << "\n[PILIH METODE PEMBAYARAN]\n";
    cout << "--------------------------------------------------------------------\n";
    cout << "1. TUNAI\n";
    cout << "2. NON-TUNAI (QRIS/Transfer)\n";
    cout << "Pilih metode (1-2): ";
    cin >> metode;
    
    // Buat objek transaksi
    Transaksi transaksi;
    transaksi.kode_barang = barang->kode;
    transaksi.nama_barang = barang->nama;
    transaksi.jumlah = jumlah_beli;
    transaksi.harga_satuan = barang->harga;
    transaksi.total_harga = total_harga;
    transaksi.waktu_transaksi = getWaktuSekarang();
    
    bool pembayaranBerhasil = false;
    
    // [IF3] - Cek pilihan angka
    switch (metode) {
        case 1:  // [JIKA PILIH 1] - TUNAI
            pembayaranBerhasil = prosesPembayaranTunai(transaksi);
            break;
            
        case 2:  // [JIKA PILIH 2] - NON-TUNAI
            pembayaranBerhasil = prosesPembayaranNonTunai(transaksi);
            break;
            
        default:
            cout << "\n? ERROR: Metode pembayaran tidak valid!\n";
            cout << "Transaksi dibatalkan.\n";
            cout << "\nTekan Enter untuk keluar...";
            cin.get();
            cin.get();
            return 0;
    }
    
    if (!pembayaranBerhasil) {
        cout << "\n? Transaksi dibatalkan.\n";
        cout << "\nTekan Enter untuk keluar...";
        cin.get();
        cin.get();
        return 0;
    }
    
    // [P11] - Update sistem (setelah pembayaran berhasil)
    cout << "\n[UPDATE SISTEM]\n";
    cout << "--------------------------------------------------------------------\n";
    
    // [P12] - Kurangi stok barang
    barang->jumlah -= jumlah_beli;
    simpanDataBarang(data);
    cout << "? Stok barang diperbarui\n";
    
    // [P13] - Catat transaksi
    catatTransaksiKeLog(transaksi);
    cout << "? Transaksi dicatat ke log\n";
    
    // [P14] - Cetak struk
    cetakStrukTransaksi(transaksi);
    
    // [FINISH2] - Transaksi selesai
    cout << "\n? TRANSAKSI BERHASIL!\n";
    cout << "\nTekan Enter untuk keluar...";
    cin.get();
    cin.get();
    
    return 0;
}
