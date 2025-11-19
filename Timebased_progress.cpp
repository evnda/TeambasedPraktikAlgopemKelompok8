#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

struct Menu {
    string nama;
    int harga;
    int jumlahTerjual;
    float rating;
};

// ====== Daftar menu kosong, admin isi manual ======
vector<Menu> daftarMenu;

// ===== PROTOTYPE =====
void pause();
bool loginAdmin();
void tampilkanDaftarMenu();
void tampilkanMenuUrutRating();
void lihatDaftarMenuDanUpdateRating();
void tambahMenu();
void editMenu();
void kelolaTambahAtauEditMenu();
void tampilkanMenuAdmin();
void tampilkanMenuPelanggan();

// ===== Fungsi utilitas =====
void pause() {
    cout << "\nTekan ENTER untuk lanjut...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// ===== Login Admin =====
bool loginAdmin() {
    string user, pass;
    cout << "\n===== LOGIN ADMIN =====\n";
    cout << "Username : ";
    cin >> user;
    cout << "Password : ";
    cin >> pass;

    if (user == "admin" && pass == "123") {
        cout << "Login berhasil!\n";
        pause();
        return true;
    } else {
        cout << "Username atau password salah!\n";
        pause();
        return false;
    }
}

// ===== TAMPILKAN DAFTAR MENU (URUT PENAMBAHAN) =====
void tampilkanDaftarMenu() {
    cout << "\n===== DAFTAR MENU (URUT PENAMBAHAN) =====\n";
    if (daftarMenu.empty()) {
        cout << "Belum ada menu.\n";
        return;
    }

    cout << left << setw(5) << "No" 
         << setw(20) << "Nama Menu"
         << setw(12) << "Harga"
         << setw(12) << "Terjual"
         << setw(8) << "Rating" << endl;
    cout << string(60, '-') << endl;

    for (int i = 0; i < daftarMenu.size(); ++i) {
        cout << left << setw(5) << i + 1
             << setw(20) << daftarMenu[i].nama
             << setw(12) << ("Rp" + to_string(daftarMenu[i].harga))
             << setw(12) << daftarMenu[i].jumlahTerjual
             << setw(8) << daftarMenu[i].rating << endl;
    }
}

// ===== TAMPILKAN MENU URUT RATING =====
void tampilkanMenuUrutRating() {
    cout << "\n===== DAFTAR MENU (URUT RATING TERTINGGI) =====\n";
    if (daftarMenu.empty()) {
        cout << "Belum ada menu.\n";
        return;
    }

    vector<Menu> temp = daftarMenu;

    sort(temp.begin(), temp.end(),
        [](Menu &a, Menu &b){ return a.rating > b.rating; });

    cout << left << setw(5) << "No"
         << setw(20) << "Nama Menu"
         << setw(12) << "Harga"
         << setw(12) << "Terjual"
         << setw(8) << "Rating" << endl;

    cout << string(60, '-') << endl;

    for (int i = 0; i < temp.size(); i++) {
        cout << left << setw(5) << i + 1
             << setw(20) << temp[i].nama
             << setw(12) << ("Rp" + to_string(temp[i].harga))
             << setw(12) << temp[i].jumlahTerjual
             << setw(8) << temp[i].rating << endl;
    }
}

// ===== LIHAT DAFTAR MENU + UPDATE RATING =====
void lihatDaftarMenuDanUpdateRating() {
    if (daftarMenu.empty()) {
        cout << "\nBelum ada menu.\n";
        pause();
        return;
    }

    tampilkanMenuUrutRating();

    char jawab;
    cout << "\nUpdate rating menu? (y/n): ";
    cin >> jawab;

    if (jawab == 'y' || jawab == 'Y') {
        tampilkanDaftarMenu();

        int idx;
        cout << "Pilih No menu: ";
        cin >> idx;

        if (idx >= 1 && idx <= daftarMenu.size()) {
            float r;
            cout << "Rating baru: ";
            cin >> r;
            daftarMenu[idx - 1].rating = r;

            cout << "Rating berhasil diperbarui!\n";
            tampilkanMenuUrutRating();
        }
        pause();
        return;
    }

    kelolaTambahAtauEditMenu();
}

// ===== TAMBAH MENU =====
void tambahMenu() {
    Menu m;
    cout << "\n===== TAMBAH MENU =====\n";
    cin.ignore();

    cout << "Nama Menu : ";
    getline(cin, m.nama);
    cout << "Harga     : ";
    cin >> m.harga;
    cout << "Terjual   : ";
    cin >> m.jumlahTerjual;
    cout << "Rating    : ";
    cin >> m.rating;

    daftarMenu.push_back(m);

    cout << "\nMenu berhasil ditambahkan!\n";
    tampilkanDaftarMenu();
    pause();
}

// ===== EDIT MENU =====
void editMenu() {
    if (daftarMenu.empty()) {
        cout << "\nBelum ada menu.\n";
        pause();
        return;
    }

    tampilkanDaftarMenu();
    int idx;
    cout << "Pilih menu yang ingin diedit: ";
    cin >> idx;

    if (idx < 1 || idx > daftarMenu.size()) {
        cout << "Nomor tidak valid.\n";
        pause();
        return;
    }

    Menu &m = daftarMenu[idx - 1];
    cin.ignore();

    cout << "\nNama baru   : ";
    getline(cin, m.nama);
    cout << "Harga baru  : ";
    cin >> m.harga;
    cout << "Terjual baru: ";
    cin >> m.jumlahTerjual;
    cout << "Rating baru : ";
    cin >> m.rating;

    cout << "Menu berhasil diedit!\n";
    pause();
}

// ===== Tambah/Edit Menu =====
void kelolaTambahAtauEditMenu() {
    char jawab;
    cout << "\nTambah menu? (y/n): ";
    cin >> jawab;

    if (jawab == 'y' || jawab == 'Y')
        tambahMenu();
    else
        editMenu();
}

// ===== MENU ADMIN =====
void tampilkanMenuAdmin() {
    int pilih;
    do {
        cout << "\n===== MENU ADMIN =====\n";
        cout << "1. Lihat daftar menu\n";
        cout << "2. Tambah/Edit menu\n";
        cout << "0. Logout\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1)
            lihatDaftarMenuDanUpdateRating();
        else if (pilih == 2)
            kelolaTambahAtauEditMenu();

    } while (pilih != 0);
}

// ===== MENU PELANGGAN (LIHAT MENU SAJA) =====
void tampilkanMenuPelanggan() {
    cout << "\n===== MENU PELANGGAN =====\n";
    tampilkanMenuUrutRating();
    pause();
}

// ===== MAIN =====
int main() {
    int pilihan;
    bool logged = false;

    do {
        cout << "\n===== SISTEM REKOMENDASI MENU =====\n";
        cout << "1. Login Admin\n";
        cout << "2. Menu Pelanggan (lihat menu saja)\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        if (pilihan == 1) {
            if (loginAdmin())
                tampilkanMenuAdmin();
        }
        else if (pilihan == 2) {
            tampilkanMenuPelanggan();
        }

    } while (pilihan != 0);

    cout << "\nTerima kasih!\n";
    return 0;
}