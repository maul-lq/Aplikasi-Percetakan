#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>

using namespace std;

#pragma region Super
/**
 * @brief Fungsi untuk mencetak judul aplikasi.
 *
 * Fungsi ini membersihkan konsol, membersihkan isi varibel pilihan_pengguna dan buffer input, sekaligus mencetak judul aplikasi.
 * Ini juga mencetak garis pemisah untuk visualisasi yang lebih baik.
 *
 * @return void
 */
void CetakJudulAplikasi()
{
    system("cls");
    cin.clear();
    cout << "Aplikasi Percetakan Online" << endl;
    cout << "---------------------------" << endl;
    cout << endl;
}

bool keluar = false;
string pilihan_pengguna;
bool isLogin = false;
#pragma endregion

#pragma region Login, Logout, Register, dan Konfigurasi Akun (Baim)

#pragma region Properti Akun
// Struktur data yang disebut 'Akun' didefinisikan dalam C++.
// Ini digunakan untuk mewakili akun pengguna dalam aplikasi Aplikasi Percetakan.
// Struktur ini berisi berbagai bidang:
//
// - 'id': Variabel integer yang menyimapn id pengguna.
// - 'nama': Variabel string yang menyimpan nama pengguna.
// - 'nomor_hp': Variabel string yang menyimpan nomor telepon pengguna.
// - 'username': Variabel string yang menyimpan nama pengguna yang unik.
// - 'password': Variabel string yang menyimpan kata sandi pengguna.
// - 'role': Variabel enum dari tipe 'Role' yang menunjukkan peran pengguna dalam aplikasi.
// Enum 'Role' didefinisikan dalam kode sebagai 'Admin' dan 'User'.
//
// Struktur ini digunakan untuk membuat objek pengguna yang dapat disimpan dalam vektor,
// seperti yang ditunjukkan dalam variabel 'Database_Akun'. Variabel 'Database_Akun' adalah koleksi pasangan,
// di mana setiap pasangan terdiri dari integer (sebagai id) dan objek 'Akun'.
// Hal ini memungkinkan penyimpanan dan pengambilan data akun pengguna dalam aplikasi secara efisien.

// Digunakan untuk membuat level / role tiap akun
enum Role
{
    Admin = 0x1A1,
    User = 0x1A2,
    Null = 0x100
};
struct Akun
{
    int id;
    string nama;
    string nomor_hp;
    string username;
    string password;
    Role role;
};

// Variabel Database_Akun adalah vektor of Akun yang digunakan untuk menyimpan data akun pengguna.
// Variabel ini diinisialisasi dengan satu objek Akun yang berisi data admin.
vector<Akun> Database_Akun = {
    {1, "Admin", "084277744102", "admin", "admin123", Admin},
    {1, "User", "084277744102", "user", "user123", User},
};

Akun session; // Digunakan untuk menyimpan data akun saat sudah login

#pragma endregion

#pragma region Login Regiser Logout
/**
 * @brief Fungsi ini bertanggung jawab atas logika logout aplikasi.
 *
 * Fungsi ini mengatur status login, menghapus data session, dan mengeset peran ke Null.
 * Ini dipanggil ketika pengguna memilih untuk logout.
 *
 * @return void
 */
void LogoutLogic()
{
    isLogin = false;
    session.nama = "";
    session.nomor_hp = "";
    session.username = "";
    session.password = "";
    session.role = Null;
}

/**
 * @brief Fungsi yang bertanggung jawab atas logika login aplikasi.
 *
 * Fungsi ini mencari username dan password yang sesuai di dalam database.
 * Jika username dan password cocok, fungsi ini akan menyimpan data akun ke dalam variabel 'session' dan mengembalikan nilai true.
 * Jika username dan password tidak cocok, fungsi ini akan mengembalikan nilai false.
 *
 * @param username Username yang dimasukkan pengguna.
 * @param password Password yang dimasukkan pengguna.
 *
 * @return bool Nilai true jika username dan password cocok, false jika tidak cocok.
 */
bool LoginLogic(string username, string password)
{
    // Cek username dan password di database
    for (Akun akun : Database_Akun)
    {
        if (akun.username == username && akun.password == password)
        {
            session = akun;
            return true;
        }
    }
    return false;
}

/**
 * @brief Fungsi untuk menangani logika pendaftaran pengguna.
 *
 * Fungsi ini memeriksa apakah username yang diberikan sudah ada di database.
 * Jika username unik, fungsi ini akan membuat akun baru dengan detail yang diberikan dan menyimpannya ke database.
 *
 * @param nama Nama lengkap pengguna.
 * @param nomor_hp Nomor telepon pengguna.
 * @param username Username unik untuk pengguna.
 * @param password Kata sandi untuk pengguna.
 *
 * @return bool Mengembalikan true jika pendaftaran berhasil (username unik dan akun disimpan), false jika tidak.
 */
bool RegisterLogic(string nama, string nomor_hp, string username, string password)
{
    bool isUsernameExist = false;
    for (Akun akun : Database_Akun)
    {
        if (akun.username == username)
        {
            isUsernameExist = true;
            break;
        }
    }

    if (isUsernameExist)
    {
        return false;
    }
    else
    {
        // Buat id baru
        int id = Database_Akun.size() + 1;
        // Simpan akun ke database
        Database_Akun.push_back({id, nama, nomor_hp, username, password, User});
        return true;
    }
}

void Tampilan_Login()
{
    string username, password;

    // Tampilan Login
    CetakJudulAplikasi();
    cout << "Silahkan masukan username dan password untuk login" << endl;
    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);

    if (LoginLogic(username, password))
    {
        isLogin = true;
        // cout << "Login berhasil!" << endl;
        // system("pause");
        // system("cls");
    }
    else
    {
        cout << "Username/Password salah! Silahkan coba lagi." << endl;
        system("pause");
        system("cls");
    }
}

void Tampilan_Register()
{
    string nama, nomor_hp, username, password;

    // Tampilan Regiser
    CetakJudulAplikasi();
    cout << "Halo, untuk membuat akun baru.\n"
         << "Silahkan masukan Nama, Nomor Hp, Username, dan Password!" << endl;
    cout << "Nama Lengkap\t: ";
    getline(cin, nama);
    cout << "Nomor Hp\t: ";
    getline(cin, nomor_hp);
    cout << "Username\t: ";
    getline(cin, username);
    cout << "Password\t: ";
    getline(cin, password);

    if (!RegisterLogic(nama, nomor_hp, username, password))
    {
        cout << "Username telah tersedia!" << endl;
        system("pause");
        system("cls");
    }
}

void Tampilan_LoginRegister()
{
    while (!isLogin)
    {
        CetakJudulAplikasi();
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Keluar" << endl;
        cout << "Masukkan pilihan anda: \n>> ";
        getline(cin, pilihan_pengguna);
        if (pilihan_pengguna == "1")
        {
            Tampilan_Login();
        }
        else if (pilihan_pengguna == "2")
        {
            Tampilan_Register();
        }
        else if (pilihan_pengguna == "3")
        {
            keluar = true;

            break;
        }
        else
        {
            cout << "Pilihan yang anda pilih tidak valid! Coba ulangi." << endl;
            system("pause");
            system("cls");
        }
    }
}
#pragma endregion

#pragma endregion

#pragma region Pemesanan (Yusuf)

struct Pemesanan
{
    string jenisCetak;
    int jumlahCetak;
    string finishing;
    string lokasi;
    string keterangan;
    string fileCetak;
};

// Data pelanggan
vector<vector<Pemesanan>> dataPemesanan;

// Fungsi untuk menampilkan menu dan mengambil pilihan (main menu, sesuaikan saja)
string pilihDariMenu(const vector<string> &opsi, const string &prompt)
{
    int pilihan;
    cout << prompt << endl;
    for (size_t i = 0; i < opsi.size(); ++i)
    {
        cout << i + 1 << ". " << opsi[i] << endl;
    }

    do
    {
        cout << "Pilih (1-" << opsi.size() << "): ";
        cin >> pilihan;
        if (pilihan < 1 || pilihan > static_cast<int>(opsi.size()))
        {
            cout << "Pilihan tidak valid, coba lagi." << endl;
        }
    } while (pilihan < 1 || pilihan > static_cast<int>(opsi.size()));

    return opsi[pilihan - 1];
}

// Fungsi untuk menambah data pemesanan
void tambahPemesanan()
{
    vector<Pemesanan> pemesananBaru;
    char tambahLagi;

    // Pilihan untuk jenis cetak
    vector<string> jenisCetakOpsi = {"Printcopy", "Fotocopy", "Poster"};
    vector<string> finishingOpsi = {"None", "Laminating", "Staples", "Jilid"};
    vector<string> lokasiOpsi = {"Tanah Baru, Beji", "Pondok Cina, Beji", "Depok Jaya, Pancoran Mas"};

    cout << "=== Formulir Pemesanan ===\n";
    do
    {
        Pemesanan p;

        // Pilih jenis cetak
        p.jenisCetak = pilihDariMenu(jenisCetakOpsi, "Pilih Jenis Cetak:");

        // Jumlah cetak
        cout << "Jumlah Cetak: ";
        cin >> p.jumlahCetak;
        cin.ignore();

        // Pilih finishing
        p.finishing = pilihDariMenu(finishingOpsi, "Pilih Finishing:");

        // Pilih lokasi
        p.lokasi = pilihDariMenu(lokasiOpsi, "Pilih Lokasi Pengambilan:");

        // Keterangan tambahan
        cout << "Keterangan (opsional): "; // Bagian sini masalah, selalu ke skip (tolong fix :( )
        getline(cin, p.keterangan);

        // Input file cetak
        cout << "Nama atau Path File yang ingin dicetak: ";
        getline(cin, p.fileCetak);

        pemesananBaru.push_back(p);

        cout << "Apakah Anda ingin menambahkan lagi pemesanan untuk pelanggan ini? (y/n): ";
        cin >> tambahLagi;
        cin.ignore();

    } while (tolower(tambahLagi) == 'y');

    // Tambahkan pemesanan pelanggan ke data utama
    dataPemesanan.push_back(pemesananBaru);
}

// Fungsi untuk menampilkan semua data pemesanan (sesuaikan untuk bagian admin buat admin konfirmasi pemesanan dan juga infromasi pemesanan andra)
void tampilkanData()
{
    if (dataPemesanan.empty())
    {
        cout << "Belum ada data pemesanan.\n";
        return;
    }

    cout << "=== Data Pemesanan ===\n";
    int pelangganIndex = 1;
    for (const auto &pelanggan : dataPemesanan)
    {
        cout << "Pelanggan #" << pelangganIndex++ << ":\n";
        int pemesananIndex = 1;
        for (const auto &p : pelanggan)
        {
            cout << "  Pemesanan #" << pemesananIndex++ << ":\n";
            cout << "    Jenis Cetak: " << p.jenisCetak << "\n";
            cout << "    Jumlah Cetak: " << p.jumlahCetak << "\n";
            cout << "    Finishing: " << p.finishing << "\n";
            cout << "    Lokasi: " << p.lokasi << "\n";
            cout << "    Keterangan: " << (p.keterangan.empty() ? "Tidak ada" : p.keterangan) << "\n";
            cout << "    File Cetak: " << p.fileCetak << "\n";
            cout << "-------------------------\n";
        }
    }
}

#pragma endregion

#pragma region Harga dan Katalog (Akmal)

struct Item
{
    string name;
    int price;
    int stock;
};

vector<Item> catalog = {
    {"Pulpen", 5000, 10},
    {"Pensil", 3000, 5},
    {"Buku Tulis", 10000, 8},
    {"Penghapus", 2000, 7},
    {"Penggaris", 4000, 15},
    {"Rambutan", 6000, 0}
};

void displayCatalog(const vector<Item> &catalog)
{
    CetakJudulAplikasi();
    cout << "\n===== KATALOG BARANG =====\n";
    int nomor = 1;
    for (const auto &item : catalog)
    {
        cout << nomor << ". " << item.name << " - Harga Rp" << item.price << " - Stok = " << item.stock << endl;
    }
    system("pause");
}

int findItemIndex(const vector<Item> catalog, const string itemName)
{
    int i = 0;
    for (Item item : catalog)
    {
        if (catalog[i].name == itemName)
        {
            return i;
        }
        i++;
    }
    return -1; // Item not found
}

void manageCatalog(vector<Item> &catalog)
{
    while (true)
    {
        CetakJudulAplikasi();
        cout << "1. Cek Ketersediaan Barang" << endl;
        cout << "2. Input Harga Barang" << endl;
        cout << "3. Tampilkan Harga Barang" << endl;
        cout << "4. Keluar" << endl;

        string adminChoice;
        cout << "Pilih menu: ";
        getline(cin, adminChoice);

        if (adminChoice == "1")
        {
            displayCatalog(catalog);
            string item;
            cout << "Masukkan nama barang: ";
            cin >> item;

            int index = findItemIndex(catalog, item);
            if (index != -1)
            {
                cout << "Barang " << item << " tersedia dengan stok " << catalog[index].stock << "." << endl;
                if (catalog[index].stock == 0)
                {
                    cout << "Ingin restock barang ini? (1 untuk ya / 0 untuk tidak): ";
                    string restock;
                    cin.clear();
                    cin.ignore();
                    getline(cin, restock);
                    if (restock == "1")
                    {
                        int stock;
                        cout << "Masukkan jumlah stok: ";
                        cin >> stock;
                        catalog[index].stock += stock;
                    }   
                }
            }
            else
            {
                cout << "Barang " << item << " tidak ditemukan." << endl;
                system("pause");
            }
        }
        else if (adminChoice == "2")
        {
            string item;
            cout << "Masukkan nama barang: ";
            cin.clear();
            cin.ignore();
            getline(cin, item);

            int index = findItemIndex(catalog, item);
            if (index != -1)
            {
                int price;
                cout << "Masukkan harga baru untuk " << item << ": ";
                cin >> price;
                catalog[index].price = price;
            }
            else
            {
                cout << "Barang " << item << " tidak ditemukan. Tambahkan barang terlebih dahulu." << endl;
                system("pause");
            }
        }
        else if (adminChoice == "3")
        {
            string item;
            cout << "Masukkan nama barang: ";
            cin.clear();
            cin.ignore();
            getline(cin, item);

            int index = findItemIndex(catalog, item);
            if (index != -1)
            {
                cout << "Harga " << item << ": " << catalog[index].price << endl;
            }
            else
            {
                cout << "Barang " << item << " tidak ditemukan." << endl;
                system("pause");
            }
        }
        else if (adminChoice == "4")
        {
            break;
        }
        else
        {
            cout << "Pilihan tidak valid, coba lagi." << endl;
            system("pause");
        }
    }
}

// int main() {

//     while (true) {
//         cout << "\nSelamat Datang di Sistem Katalog" << endl;
//         cout << "1. Pelanggan" << endl;
//         cout << "2. Admin" << endl;
//         cout << "3. Keluar" << endl;

//         int userChoice;
//         cout << "Masukkan pilihan: ";
//         cin >> userChoice;

//         if (userChoice == 1) {
//             displayCatalog(catalog);
//         } else if (userChoice == 2) {
//             manageCatalog(catalog);
//         } else if (userChoice == 3) {
//             cout << "Terima kasih, sampai jumpa!" << endl;
//             break;
//         } else {
//             cout << "Pilihan tidak valid, coba lagi." << endl;
//         }
//     }

//     return 0;
// }
#pragma endregion

#pragma region Informasi Pemesanan (Diandra)
// Fungsi untuk memproses pesanan
void prosesPesanan()
{
    string namaFile;
    int jumlahKertas, totalBiaya;
    vector<string> keranjangBarang;
    vector<int> hargaBarang;

    // Biaya cetak
    const int biayaCetak = 5000;

    // Input nama file
    cout << "Masukkan nama file yang ingin dicetak: ";
    cin >> namaFile;
    cout << "Masukkan jumlah kertas yang ingin dicetak: ";
    cin >> jumlahKertas;

    totalBiaya = biayaCetak * jumlahKertas;

    // Pilih barang tambahan
    char pilih;
    do
    {
        displayCatalog(catalog);
        int nomorBarang;

        cout << "Pilih nomor barang (0 untuk selesai): ";
        cin >> nomorBarang;

        switch (nomorBarang)
        {
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
    int totalHarga = totalBiaya;
    cout << "\n===== DETAIL PESANAN =====\n";
    cout << "File Cetak: " << namaFile << endl;
    cout << "Biaya Cetak: Rp " << totalBiaya << endl;

    cout << "Barang Tambahan:\n";
    for (int i = 0; i < keranjangBarang.size(); i++)
    {
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

    if (konfirmasi == 'y' || konfirmasi == 'Y')
    {
        cout << "Pesanan Sedang Diproses...\n";
    }
    else
    {
        cout << "Pesanan Dibatalkan\n";
    }
}
#pragma endregion

#pragma region Status Pesanan (Reza)

void statusPesanan()
{
    string status = "  ";
}

#pragma endregion

#pragma region Informasi Pelanggan (Rian)

struct Pelanggan
{
    string nama;
    string nomorTelepon;
    string username;
    string password;
};

void inputDataAwal(vector<Pelanggan> &dataPelanggan, int &idPelanggan)
{
    int jumlah;
    cout << "Masukkan jumlah data pelanggan awal: ";
    cin >> jumlah;
    cin.ignore(); // Mengabaikan newline setelah input jumlah

    for (int i = 0; i < jumlah; ++i)
    {
        Pelanggan pelangganBaru;
        cout << "\nData pelanggan ke-" << (i + 1) << ":" << endl;
        cout << "Masukkan Nama: ";
        getline(cin, pelangganBaru.nama);
        cout << "Masukkan Nomor Telepon: ";
        getline(cin, pelangganBaru.nomorTelepon);
        cout << "Masukkan Username: ";
        getline(cin, pelangganBaru.username);
        cout << "Masukkan Password: ";
        getline(cin, pelangganBaru.password);

        dataPelanggan.push_back(pelangganBaru);
        idPelanggan++;
    }
}

void tampilkanMenu()
{
    cout << "\n=== Menu Utama ===" << endl;
    cout << "1. Tambah Data Pelanggan" << endl;
    cout << "2. Hapus Data Pelanggan" << endl;
    cout << "3. Keluar" << endl;
    cout << "Pilih opsi: ";
}

void tambahPelanggan(vector<Pelanggan> &dataPelanggan, int &idPelanggan)
{
    Pelanggan pelangganBaru;
    cout << "Masukkan Nama: ";
    cin.ignore();
    getline(cin, pelangganBaru.nama);
    cout << "Masukkan Nomor Telepon: ";
    getline(cin, pelangganBaru.nomorTelepon);
    cout << "Masukkan Username: ";
    getline(cin, pelangganBaru.username);
    cout << "Masukkan Password: ";
    getline(cin, pelangganBaru.password);

    dataPelanggan.push_back(pelangganBaru);
    cout << "Data berhasil ditambahkan!" << endl;
}

void hapusPelanggan(vector<Pelanggan> &dataPelanggan)
{
    if (dataPelanggan.empty())
    {
        cout << "Tidak ada data pelanggan untuk dihapus." << endl;
        return;
    }

    string namaHapus;
    cout << "Masukkan Nama pelanggan yang ingin dihapus: ";
    cin.ignore();
    getline(cin, namaHapus);

    for (auto it = dataPelanggan.begin(); it != dataPelanggan.end(); ++it)
    {
        if (it->nama == namaHapus)
        {
            dataPelanggan.erase(it);
            cout << "Data berhasil dihapus!" << endl;
            return;
        }
    }

    cout << "Nama pelanggan tidak ditemukan!" << endl;
}

void lihatSemuaPelanggan(const vector<Pelanggan> &dataPelanggan)
{
    if (dataPelanggan.empty())
    {
        cout << "Tidak ada data pelanggan." << endl;
        return;
    }

    cout << "\nDaftar Pelanggan:" << endl;
    for (const auto &pelanggan : dataPelanggan)
    {
        cout << "Nama: " << pelanggan.nama
             << ", Nomor Telepon: " << pelanggan.nomorTelepon
             << ", Username: " << pelanggan.username
             << ", Password: " << pelanggan.password << endl;
    }
}

// int main() {
//     vector<Pelanggan> dataPelanggan;
//     int idPelanggan = 1;
//     int pilihan;

//     inputDataAwal(dataPelanggan, idPelanggan);

//     do {
//         lihatSemuaPelanggan(dataPelanggan);
//         tampilkanMenu();
//         cin >> pilihan;

//         switch (pilihan) {
//             case 1:
//                 tambahPelanggan(dataPelanggan, idPelanggan);
//                 break;
//             case 2:
//                 hapusPelanggan(dataPelanggan);
//                 break;
//             case 3:
//                 cout << "Keluar dari program. Terima kasih!" << endl;
//                 break;
//             default:
//                 cout << "Pilihan tidak valid. Coba lagi." << endl;
//         }
//     } while (pilihan != 3);

//     return 0;
// }
#pragma endregion

#pragma region Laporan Keuangan dan Konfirmasi Pemesanan (Dendy)
struct Laporan_Kuangan
{
    string username;
    string judul;
    int harga;
    string jenis;
};

vector<Laporan_Kuangan> Kumpulan_Laporan_Keuangan = {
    {"admin", "Beli Barang", 7000, "Barang"},
    {"admin", "Cetakan", 7000, "Katalog"},
};

void TampilanLaporanKeuangan()
{
    cout << "\n===== LAPORAN KEUANGAN =====\n";
    for (Laporan_Kuangan laporan : Kumpulan_Laporan_Keuangan)
    {
        cout << "Username\t: " << laporan.username << endl;
        cout << "Nama Barang\t: " << laporan.username << endl;
        cout << "Harga\t\t: " << laporan.harga << endl;
        cout << "Jenis Laporan\t: " << laporan.jenis << endl;
        cout << "===========================================" << endl;
    }
    system("pause");
}

// Status
#pragma endregion

#pragma region Menu Utama
void TampilanMenuUtamaAdmin()
{
    CetakJudulAplikasi();
    cout << "Selamat datang, " << session.nama << "!" << endl;
    cout << "1. Data Pelanggan" << endl;
    cout << "2. Manage Katalog" << endl;
    cout << "3. Laporan Keuangan" << endl;
    cout << "4. Konfirmasi Pemesanan" << endl;
    cout << "5. Logout" << endl;
    cout << "Masukkan pilihan anda: \n>> ";
}

void TampilanMenuUtamaUser()
{
    CetakJudulAplikasi();
    cout << "Selamat datang, " << session.nama << "!" << endl;
    cout << "1. Lihat Katalog" << endl;
    cout << "2. Buat Pemesanan" << endl;
    cout << "3. Status Pemesanan" << endl;
    cout << "4. Logout" << endl;
    cout << "Masukkan pilihan anda: \n>> ";
}
#pragma endregion

#pragma region Main Program
int main()
{
    while (!keluar)
    {
        if (!isLogin)
        {
            Tampilan_LoginRegister();
        }
        else
        {
            if (session.role == Admin)
            {
                TampilanMenuUtamaAdmin();
                getline(cin, pilihan_pengguna);
                if (pilihan_pengguna == "5")
                {
                    LogoutLogic();
                }
                else if (pilihan_pengguna == "3")
                {
                    TampilanLaporanKeuangan();
                }
                else if (pilihan_pengguna == "2")
                {
                    manageCatalog(catalog);
                }
            }
            else if (session.role == User)
            {
                TampilanMenuUtamaUser();
                getline(cin, pilihan_pengguna);
                if (pilihan_pengguna == "1")
                {
                    displayCatalog(catalog);
                }
                else if (pilihan_pengguna == "2")
                {
                    prosesPesanan();
                }
                else if (pilihan_pengguna == "3")
                {
                    statusPesanan();
                }
                else if (pilihan_pengguna == "4")
                {
                    LogoutLogic();
                }
                else
                {
                }
            }
            else
            {
                cout << "Invalid user role: " << session.role << endl;
                system("pause");
                system("cls");
                break;
            }
        }
    }

    cout << endl;
    return 0;
}
#pragma endregion