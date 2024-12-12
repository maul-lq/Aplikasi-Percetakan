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
vector<Akun> Database_Akun = {{1,"Admin", "084277744102", "admin", "admin123", Admin}};

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
    cout << "1. Katalog & Harga" << endl;
    cout << "2. Form Pemesanan" << endl;
    cout << "3. Informasi Pemesanan" << endl;
    cout << "4. Status Pemesanan" << endl;
    cout << "5. Booking" << endl;
    cout << "6. Logout" << endl;
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
                if (pilihan_pengguna == "6")
                {
                    LogoutLogic();
                }
            }
            else
            {
            }
        }
    }

    cout << endl;
    return 0;
}
#pragma endregion