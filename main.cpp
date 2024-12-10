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
 * Fungsi ini membersihkan konsol, membersihkan buffer input, dan mencetak judul aplikasi.
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



string pilihan_pengguna;
#pragma endregion

#pragma region Properti Akun
// Struktur data yang disebut 'Akun' didefinisikan dalam C++.
// Ini digunakan untuk mewakili akun pengguna dalam aplikasi Aplikasi Percetakan.
// Struktur ini berisi berbagai bidang:
//
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
    User = 0x1A2
};
struct Akun
{
    string nama;
    string nomor_hp;
    string username;
    string password;
    Role role;
};
// agar bisa membedakan mana yang akun Admin dna User.
// Buat variabel array berupa vector yang fungsinya untuk menyimpan akun pengguna aplikasi.
vector<pair<int, Akun>> Database_Akun = {
    {1, {"Admin", "081585893549", "admin", "admin123", Admin}},
};

Akun session; // Digunakan untuk menyimpan data akun saat sudah login
#pragma endregion

int main()
{
    while (true)
    {
        CetakJudulAplikasi();
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Keluar" << endl;
        cout << "Masukkan pilihan anda: \n>> ";
        getline(cin, pilihan_pengguna);
        if (pilihan_pengguna == "1")
        {
            // Tampilan Login
        }
        else if (pilihan_pengguna == "2")
        {
            // Tampilan  Register
        }
        else if (pilihan_pengguna == "3")
        {
            break;
        }else
        {
            cout << "Pilihan yang anda pilih tidak valid! Coba ulangi." << endl;
            system("pause");
            system("cls");
        }
    }

    cout << endl;
    return 0;
}