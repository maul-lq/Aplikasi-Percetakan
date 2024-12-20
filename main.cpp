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

const int biayaCetak = 5000;

bool keluar = false;
string pilihan_pengguna;
bool isLogin = false;
bool isWithBooking = false;

struct PemesananCetak
{
    int id;
    string username;
    string jenisCetak;
    int jumlahCetak;
    string finishing;
    string lokasi;
    string keterangan;
    string fileCetak;
};

// Data pelanggan
vector<PemesananCetak> dataPemesananCetak;

struct Pesanan
{
    int id;
    string username;
    int hargaTotal;
    string status;
    string keterangan;
};

vector<Pesanan> dataPesanan;

struct Laporan_Kuangan
{
    string username;
    string judul;
    int harga;
    string jenis;
};

vector<Laporan_Kuangan> Kumpulan_Laporan_Keuangan;

#pragma endregion

#pragma region

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
    None = 0x100
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
 * Fungsi ini mengatur status login, menghapus data session, dan mengeset peran ke None.
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
    session.role = None;
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
    {"Penggaris", 4000, 15}};

void displayCatalog(const vector<Item> &catalog)
{
    CetakJudulAplikasi();
    cout << "\n===== KATALOG BARANG =====\n";
    int nomor = 1;
    for (const auto &item : catalog)
    {
        string stok = (item.stock != 0) ? to_string(item.stock) : "HABIS";
        cout << nomor << ". " << item.name << " - Harga Rp." << item.price << " - Stok = " << stok << endl;
        nomor++;
    }
    system("pause");
}

void displayCatalog()
{
    CetakJudulAplikasi();
    cout << "\n===== KATALOG BARANG =====\n";
    int nomor = 1;
    for (const auto &item : catalog)
    {
        string stok = (item.stock != 0) ? to_string(item.stock) : "HABIS";
        cout << nomor << ". " << item.name << " - Harga Rp" << item.price << " - Stok = " << stok << endl;
        nomor++;
    }
}

int findItemIndex(vector<Item> catalog, string itemName)
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
            CetakJudulAplikasi();
            displayCatalog();
            string item;
            cout << "Masukkan nama barang: ";
            getline(cin, item);

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
                        string stock;
                        cout << "Masukkan jumlah stok: ";
                        getline(cin, stock);
                        catalog[index].stock += stoi(stock);
                    }
                }
                system("pause");
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
            getline(cin, item);

            int index = findItemIndex(catalog, item);
            if (index != -1)
            {
                cout << "Masukkan harga baru untuk " << item << ": ";
                string price;
                getline(cin, price);
                catalog[index].price = stoi(price);
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
            getline(cin, item);

            int index = findItemIndex(catalog, item);
            if (index != -1)
            {
                cout << "Harga " << item << ": " << catalog[index].price << endl;
                system("pause");
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

#pragma endregion

#pragma region Informasi Pemesanan & Booking (Mahfud & Diandra)

/**
 * @brief Menghitung total biaya pesanan cetak untuk pengguna tertentu.
 *
 * @param dataPemesananCetak Vektor yang berisi semua data pesanan cetak.
 *
 * @return Total biaya pesanan cetak untuk pengguna.
 *
 * @note Fungsi ini mengulangi data pesanan cetak, memeriksa apakah pesanan tersebut milik pengguna,
 * dan menghitung total biaya dengan mengalikan jumlah setiap pesanan cetak dengan harga per cetak.
 */
int hitungHargaPesanan(vector<PemesananCetak> dataPemesananCetak)
{
    int totalBiaya = 0;
    // Hitung total harga cetak
    vector<int> tempPaperPriceVar;
    for (auto pemesanan_percetakan : dataPemesananCetak)
    {
        if (pemesanan_percetakan.username == session.username)
        {
            tempPaperPriceVar.push_back(pemesanan_percetakan.jumlahCetak);
        }
    }
    for (int jumplahCetak : tempPaperPriceVar)
    {
        totalBiaya += jumplahCetak * biayaCetak;
    }
    return totalBiaya;
}

void booking(int hargaCetakan)
{
    int jumlahKertas;

    vector<string> keranjangBarang;
    vector<int> hargaBarang;
    int indexItem = None;

    // // Input nama file
    // cout << "Masukkan nama file yang ingin dicetak: ";
    // getline(cin, namaFile);
    // cout << "Masukkan jumlah kertas yang ingin dicetak: ";
    // cin.clear();
    // cin >> jumlahKertas;

    // Pilih barang tambahan
    char pilih;
    do
    {
        displayCatalog();
        int nomorBarang;
        string namaBarang;

        cout << "Pilih nomor barang (0 untuk selesai): ";
        cin.ignore();
        cin >> nomorBarang;

        switch (nomorBarang)
        {
        case 1:
            namaBarang = "Pulpen";
            indexItem = findItemIndex(catalog, namaBarang);
            if (catalog.at(indexItem).stock > 0)
            {
                keranjangBarang.push_back(namaBarang);
                hargaBarang.push_back(catalog[indexItem].price);
                catalog.at(indexItem).stock -= 1;
            }
            else
            {
                cout << "Maaf stok telah habis!" << endl;
                system("pause");
            }
            break;
        case 2:
            namaBarang = "Pensil";
            indexItem = findItemIndex(catalog, namaBarang);
            if (catalog.at(indexItem).stock > 0)
            {
                keranjangBarang.push_back(namaBarang);
                hargaBarang.push_back(catalog[indexItem].price);
                catalog.at(indexItem).stock -= 1;
            }
            else
            {
                cout << "Maaf stok telah habis!" << endl;
                system("pause");
            }
            break;
        case 3:
            namaBarang = "Buku Tulis";
            indexItem = findItemIndex(catalog, namaBarang);
            if (catalog.at(indexItem).stock > 0)
            {
                keranjangBarang.push_back(namaBarang);
                hargaBarang.push_back(catalog[indexItem].price);
                catalog.at(indexItem).stock -= 1;
            }
            else
            {
                cout << "Maaf stok telah habis!" << endl;
                system("pause");
            }
            break;
        case 4:
            namaBarang = "Penghapus";
            indexItem = findItemIndex(catalog, namaBarang);
            if (catalog.at(indexItem).stock > 0)
            {
                keranjangBarang.push_back(namaBarang);
                hargaBarang.push_back(catalog[indexItem].price);
                catalog.at(indexItem).stock -= 1;
            }
            else
            {
                cout << "Maaf stok telah habis!" << endl;
                system("pause");
            }
            break;
        case 5:
            namaBarang = "Penggaris";
            indexItem = findItemIndex(catalog, namaBarang);
            if (catalog.at(indexItem).stock > 0)
            {
                keranjangBarang.push_back(namaBarang);
                hargaBarang.push_back(catalog[indexItem].price);
                catalog.at(indexItem).stock -= 1;
            }
            else
            {
                cout << "Maaf stok telah habis!" << endl;
                system("pause");
            }
            break;
        }

        cout << "Ingin tambah barang lagi? (y/n): ";
        cin >> pilih;
    } while (pilih == 'y' || pilih == 'Y');

    // Hitung total harga
    int totalHarga = 0;

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
    cout << "Total Harga: Rp " << totalHarga + hargaCetakan << endl;

    Pesanan p;
    p.id = dataPesanan.size() + 1;
    p.username = session.username;
    p.status = "pbk"; // ah iya yang ini di copy aja sama yg diatas biar langsung bayar juga
    if (isWithBooking)
    {

        p.hargaTotal = totalHarga + hargaCetakan;
        isWithBooking = false;
    }
    else
    {
        p.hargaTotal = totalHarga;
    }
    Laporan_Kuangan lk;
    lk.harga = p.hargaTotal;
    lk.judul = "Cetak Dengan Booking";
    lk.username = session.username;
    lk.jenis = "Cetak + Booking";
    dataPesanan.push_back(p);
    Kumpulan_Laporan_Keuangan.push_back(lk);

    // Konfirmasi
    // REVIEW: Baim ubah langsung di proses aja.
    cout << "Pesanan Sedang Diproses...\n";
    system("pause");
}
#pragma endregion

#pragma region Pemesanan (Yusuf)
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
    char tambahLagi;

    // Pilihan untuk jenis cetak
    vector<string> jenisCetakOpsi = {"Printcopy", "Fotocopy"};
    vector<string> finishingOpsi = {"None", "Laminating", "Staples", "Jilid"};

    CetakJudulAplikasi();
    cout << "=== Formulir Pemesanan ===\n";
    do
    {
        PemesananCetak p;

        // Pilih jenis cetak
        p.jenisCetak = pilihDariMenu(jenisCetakOpsi, "Pilih Jenis Cetak:");

        // Jumlah cetak
        cout << "Jumlah Cetak: ";
        cin >> p.jumlahCetak;
        cin.ignore();

        // Pilih finishing
        p.finishing = pilihDariMenu(finishingOpsi, "Pilih Finishing:");

        // Pilih lokasi
        // p.lokasi = pilihDariMenu(lokasiOpsi, "Pilih Lokasi Pengambilan:");

        // Keterangan tambahan
        cout << "Keterangan (opsional): "; // Bagian sini masalah, selalu ke skip (tolong fix :( )
        cin.clear();
        cin.ignore();
        getline(cin, p.keterangan);

        // Input file cetak
        cout << "Nama atau Path File yang ingin dicetak: ";
        getline(cin, p.fileCetak);

        p.username = session.username;
        p.id = dataPemesananCetak.size() + 1;

        dataPemesananCetak.push_back(p);

        cout << "Apakah Anda ingin menambahkan lagi pemesanan untuk pelanggan ini? (y/n): ";
        cin >> tambahLagi;
        cin.ignore();

    } while (tolower(tambahLagi) == 'y');

    int harganya = hitungHargaPesanan(dataPemesananCetak);
    do
    {
        CetakJudulAplikasi();
        cout << "Apakah mau booking sekalian? (y/n)" << endl;
        getline(cin, pilihan_pengguna);
        if (pilihan_pengguna == "y")
        { // jadi satu ny ada di sini
            isWithBooking = true;
            booking(harganya);
            return;
        }
    } while (pilihan_pengguna != "n");

    if (!isWithBooking)
    {
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
        cout << "Total Harga: Rp " << harganya << endl;

        Pesanan p;
        p.id = dataPesanan.size() + 1;
        p.username = session.username;
        p.status = "pbk"; // default value status
        p.hargaTotal = harganya;
        Laporan_Kuangan lk;
        lk.harga = p.hargaTotal;
        lk.judul = "Cetak Tanpa Booking";
        lk.username = session.username;
        lk.jenis = "Cetak";
        dataPemesananCetak.clear();
        dataPesanan.push_back(p);
        Kumpulan_Laporan_Keuangan.push_back(lk);

        cout << "Pesanan Sedang Diproses...\n";
        system("pause");
    }
}

// Fungsi untuk menampilkan semua data pemesanan (sesuaikan untuk bagian admin buat admin konfirmasi pemesanan dan juga infromasi pemesanan andra)
void tampilkanData()
{
    if (dataPemesananCetak.empty())
    {
        cout << "Belum ada data pemesanan.\n";
        return;
    }

    cout << "=== Data Pemesanan ===\n";
    int pelangganIndex = 1;
    for (const auto &pelanggan : dataPemesananCetak)
    {
        cout << "Pelanggan #" << pelanggan.username << ":\n";
        cout << "  Pemesanan #" << pelangganIndex++ << ":\n";
        cout << "    Jenis Cetak: " << pelanggan.jenisCetak << "\n";
        cout << "    Jumlah Cetak: " << pelanggan.jumlahCetak << "\n";
        cout << "    Finishing: " << pelanggan.finishing << "\n";
        cout << "    Lokasi: " << pelanggan.lokasi << "\n";
        cout << "    Keterangan: " << (pelanggan.keterangan.empty() ? "Tidak ada" : pelanggan.keterangan) << "\n";
        cout << "    File Cetak: " << pelanggan.fileCetak << "\n";
        cout << "-------------------------\n";
    }
}

#pragma endregion

#pragma region Status Pesanan (Reza)
void statusPesanan()
{
    CetakJudulAplikasi();
    if (dataPesanan.empty())
    {
        cout << "Belum ada pesanan yang dibuat" << endl;
        system("pause");
        return;
    }

    cout << "=== Status Pemesanan ===" << endl;
    for (const auto &pesanan : dataPesanan)
    {
        if (session.username == pesanan.username)
        {
            string status = "";
            if (pesanan.status == "pbk")
            {
                status = "Belum Di Konfirmasi";
            }
            else if (pesanan.status == "ptlk")
            {

                status = "Pesanan Ditolak";
            }
            else
            {
                status = "Sudah Di Konfirmasi";
            }
            cout << "ID Pesanan: " << pesanan.id << endl;
            cout << "Nama Pemesan: " << pesanan.username << endl;
            cout << "Total Harga: Rp" << pesanan.hargaTotal << endl;
            cout << "Status Pesanan: " << status << endl;
            cout << "Keterangan: " << pesanan.keterangan << endl;
            cout << "\n";
        }
    }
    system("pause");
}

void konfirmasiPesanan()
{
    if (dataPesanan.empty())
    {
        cout << "Tidak ada pesanan untuk dikonfirmasi.\n";
        return;
    }

    cout << "\n=== Konfirmasi Pesanan ===\n";
    for (const auto &pesanan : dataPesanan)
    {
        string status = (pesanan.status == "pbk") ? "Belum Di Konfirmasi" : "Sudah Di Konfirmasi";
        cout << "ID Pesanan: " << pesanan.id << endl;
        cout << "Nama Pemesan: " << pesanan.username << endl;
        cout << "Total Harga: Rp" << pesanan.hargaTotal << endl;
        cout << "Status Pesanan: " << status << endl;
        cout << "\n";
    }

    string idPesanan;
    cout << "Masukkan ID pesanan yang ingin dikonfirmasi: ";
    getline(cin, idPesanan);

    bool ditemukan = false;
    for (auto &pesanan : dataPesanan)
    {
        if (pesanan.id == stoi(idPesanan))
        {
            ditemukan = true;
            if (pesanan.status == "pbk" || pesanan.status == "ptlk") // yang tanpa bo
            {
                string maukonfirmgak = "";
                cout << "Apakah pesanan ini mau di konfirmasi? (y/n)";
                getline(cin, maukonfirmgak);
                if (maukonfirmgak == "y")
                {
                    pesanan.status = "pb";
                    cout << "Pesanan berhasil di konfirmasi!" << endl;
                    system("pause");
                }
                else
                {
                    string alasannye_mas = "";
                    cout << "Alasan ditolak: ";
                    getline(cin, alasannye_mas);
                    pesanan.status = "ptlk";
                    pesanan.keterangan = alasannye_mas;
                    cout << "Konfirmasi batal.\n";
                }
                system("pause");
            }
            else
            {
                cout << "Pesanan dengan ID " << idPesanan << " tidak dalam status 'Menunggu Konfirmasi'.\n";
                system("pause");
            }
            break;
        }
    }

    if (!ditemukan)
    {
        cout << "Pesanan dengan ID " << idPesanan << " tidak ditemukan.\n";
        system("pause");
    }
}

#pragma endregion

#pragma region Informasi Pelanggan (Rian)

// void inputDataAwal(vector<Akun> &dataPelanggan, int &idPelanggan)
// {
//     int jumlah;
//     cout << "Masukkan jumlah data pelanggan awal: ";
//     cin >> jumlah;
//     cin.ignore(); // Mengabaikan newline setelah input jumlah

//     for (int i = 0; i < jumlah; ++i)
//     {
//         Akun akunBarun;
//         cout << "\nData pelanggan ke-" << (i + 1) << ":" << endl;
//         cout << "Masukkan Nama: ";
//         getline(cin, pelangganBaru.nama);
//         cout << "Masukkan Nomor Telepon: ";
//         getline(cin, pelangganBaru.nomorTelepon);
//         cout << "Masukkan Username: ";
//         getline(cin, pelangganBaru.username);
//         cout << "Masukkan Password: ";
//         getline(cin, pelangganBaru.password);

//         dataPelanggan.push_back(pelangganBaru);
//         idPelanggan++;
//     }
// }

void tampilkanMenu()
{
    cout << "\n=== Menu Utama ===" << endl;
    cout << "1. Tambah Data Pelanggan" << endl;
    cout << "2. Hapus Data Pelanggan" << endl;
    cout << "3. Keluar" << endl;
    cout << "Pilih opsi: ";
}

void tambahAkunAdmin(vector<Akun> &database_akun)
{
    Akun adminBaru;
    cout << "Masukkan Nama: ";
    cin.ignore();
    getline(cin, adminBaru.nama);
    cout << "Masukkan Nomor Telepon: ";
    getline(cin, adminBaru.nomor_hp);
    cout << "Masukkan Username: ";
    getline(cin, adminBaru.username);
    cout << "Masukkan Password: ";
    getline(cin, adminBaru.password);
    adminBaru.role = Admin;
    adminBaru.id = database_akun.size() + 1;
    database_akun.push_back(adminBaru);
    cout << "Data berhasil ditambahkan!" << endl;
    system("pause");
}

void hapusAkun(vector<Akun> &dataPelanggan)
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
            system("pause");
            return;
        }
    }

    cout << "Nama pelanggan tidak ditemukan!" << endl;
    system("pause");
}

void lihatSemuaAkunPengguna(const vector<Akun> &dataPelanggan)
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
             << ", Nomor Telepon: " << pelanggan.nomor_hp
             << ", Username: " << pelanggan.username
             << ", Password: " << pelanggan.password << endl;
    }
}

// int main() {
//     vector<Akun> dataPelanggan;
//     int idPelanggan = 1;
//     int pilihan;

//     inputDataAwal(dataPelanggan, idPelanggan);

//     do {
//         lihatSemuaAkunPelanggan(dataPelanggan);
//         tampilkanMenu();
//         cin >> pilihan;

//         switch (pilihan) {
//             case 1:
//                 tambahAkunAdmin(dataPelanggan, idPelanggan);
//                 break;
//             case 2:
//                 hapusAkun(dataPelanggan);
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
/**
 * @brief Tampilkan laporan keuangan.
 *
 * Fungsi ini melakukan iterasi ke array / koleksi laporan keuangan, kemudian
 * mencetak hasil detilnya setiap laporan tersebut. Data laporannya yaitu username,
 * nama produk, harga total pembelian, dan jenis laporannya.
 *
 *  @return void
 */
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
} // ok

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
    cout << "3. Informasi Pemesanan" << endl;
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
                else if (pilihan_pengguna == "4")
                {
                    konfirmasiPesanan();
                }
                else if (pilihan_pengguna == "1")
                {
                    CetakJudulAplikasi();
                    lihatSemuaAkunPengguna(Database_Akun);
                    tampilkanMenu();
                    cin.clear();
                    cin >> pilihan_pengguna;

                    switch (stoi(pilihan_pengguna))
                    {
                    case 1:
                        tambahAkunAdmin(Database_Akun);
                        break;
                    case 2:
                        hapusAkun(Database_Akun);
                        break;
                    case 3:
                        break;
                    default:
                        cout << "Pilihan tidak valid. Coba lagi." << endl;
                        system("pause");
                    }
                }
                else
                {
                    cout << "Pilihan tidak valid. Coba lagi." << endl;
                    system("pause");
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
                    tambahPemesanan();
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
                    cout << "Pilihan tidak valid. Coba lagi." << endl;
                    system("pause");
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
#pragma endregion // mantap ya line nya