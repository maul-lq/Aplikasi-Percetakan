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

#pragma region Login, Logout, Register, dan Konfigurasi Akun (Maulana Ibrahim)

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
vector<Akun> Database_Akun = {{1, "Admin", "084277744102", "admin", "admin123", Admin}};

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

#pragma region Informasi Pemesanan (Diandra)
// Fungsi untuk menampilkan katalog barang
void tampilkanKatalog()
{
    cout << "\n===== KATALOG BARANG =====\n";
    cout << "1. Pulpen - Rp 5000\n";
    cout << "2. Pensil - Rp 3000\n";
    cout << "3. Buku Tulis - Rp 10000\n";
    cout << "4. Penghapus - Rp 2000\n";
    cout << "5. Penggaris - Rp 4000\n";
    system("pause");    
}

// Fungsi untuk memproses pesanan
void prosesPesanan()
{
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
    do
    {
        tampilkanKatalog();
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
    int totalHarga = biayaCetak;
    cout << "\n===== DETAIL PESANAN =====\n";
    cout << "File Cetak: " << namaFile << endl;
    cout << "Biaya Cetak: Rp " << biayaCetak << endl;

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

#pragma region Menu Utama
void TampilanMenuUtamaAdmin()
{
    CetakJudulAplikasi();
    cout << "Selamat datang, " << session.nama << "!" << endl;
    cout << "1. Data Pelanggan" << endl;
    cout << "2. Katalog & Harga" << endl;
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
            }
            else if (session.role == User)
            {
                TampilanMenuUtamaUser();
                getline(cin, pilihan_pengguna);
                if (pilihan_pengguna == "4")
                {
                    LogoutLogic();
                }
                else if (pilihan_pengguna == "1")
                {
                    tampilkanKatalog();
                }
                else if (pilihan_pengguna == "2")
                {
                    prosesPesanan();
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