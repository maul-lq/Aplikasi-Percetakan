#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Fungsi untuk menampilkan katalog barang
void tampilkanKatalog() {
    cout << "\n===== KATALOG BARANG =====\n";
    cout << "1. Pulpen - Rp 5000\n";
    cout << "2. Pensil - Rp 3000\n";
    cout << "3. Buku Tulis - Rp 10000\n";
    cout << "4. Penghapus - Rp 2000\n";
    cout << "5. Penggaris - Rp 4000\n";
}

// Fungsi untuk memproses pesanan
void prosesPesanan() {
    string namaFile;
    vector<string> keranjangBarang;
    vector<int> hargaBarang;
    
    // Biaya cetak
    const int biayaCetak = 5000;
    
    // Input nama file
    cout << "Masukkan nama file yang ingin dicetak: ";
    cin >> namaFile;

    // Pilih barang tambahan
    char pilih;
    do {
        tampilkanKatalog();
        int nomorBarang;
        
        cout << "Pilih nomor barang (0 untuk selesai): ";
        cin >> nomorBarang;

        switch(nomorBarang) {
            case 1:
                keranjangBarang.push_back("Pulpen");
                hargaBarang.push_back(5000);
                break;
            case 2:
                keranjangBarang.push_back("Pensil");
                hargaBarang.push_back(3000);
                break;
            case 3:
                keranjangBarang.push_back("Buku Tulis");
                hargaBarang.push_back(10000);
                break;
            case 4:
                keranjangBarang.push_back("Penghapus");
                hargaBarang.push_back(2000);
                break;
            case 5:
                keranjangBarang.push_back("Penggaris");
                hargaBarang.push_back(4000);
                break;
        }

        cout << "Ingin tambah barang lagi? (y/n): ";
        cin >> pilih;
    } while (pilih == 'y' || pilih == 'Y');

    // Hitung total harga
    int totalHarga = biayaCetak;
    cout << "\n===== DETAIL PESANAN =====\n";
    cout << "File Cetak: " << namaFile << endl;
    cout << "Biaya Cetak: Rp " << biayaCetak << endl;
    
    cout << "Barang Tambahan:\n";
    for (int i = 0; i < keranjangBarang.size(); i++) {
        totalHarga += hargaBarang[i];
        cout << "- " << keranjangBarang[i] << " (Rp " << hargaBarang[i] << ")\n";
    }

    // Metode pembayaran
    int metodeBayar;
    cout << "\nPilih Metode Pembayaran:\n";
    cout << "1. Transfer Bank\n";
    cout << "2. E-Wallet\n";
    cout << "Pilih metode (1/2): ";
    cin >> metodeBayar;

    // Metode pengiriman
    int metodePengiriman;
    cout << "\nPilih Metode Pengiriman:\n";
    cout << "1. Kurir\n";
    cout << "2. Ambil Ditempat\n";
    cout << "Pilih metode (1/2): ";
    cin >> metodePengiriman;

    // Total harga
    cout << "\n===== PEMBAYARAN =====\n";
    cout << "Total Harga: Rp " << totalHarga << endl;

    // Konfirmasi
    char konfirmasi;
    cout << "Lanjutkan pembayaran? (y/n): ";
    cin >> konfirmasi;

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        cout << "Pesanan Sedang Diproses...\n";
    } else {
        cout << "Pesanan Dibatalkan\n";
    }
}

// Fungsi utama
int main() {
    int pilihan;
    do {
        cout << "\n===== APLIKASI PERCETAKAN =====\n";
        cout << "1. Buat Pesanan\n";
        cout << "2. Lihat Katalog\n";
        cout << "3. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch(pilihan) {
            case 1:
                prosesPesanan();
                break;
            case 2:
                tampilkanKatalog();
                break;
            case 3:
                cout << "Terima Kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 3);

    return 0;
}