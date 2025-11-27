#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

// =============================
//        DATA STRUCT
// =============================
struct Menu {
    string nama;
    int harga;
    int jumlahTerjual;
    float rating;
};

struct KeranjangItem {
    string nama;
    int harga;
    int jumlah;
};

// =============================
//     VARIABEL GLOBAL
// =============================
vector<Menu> daftarMenu;          
vector<KeranjangItem> keranjang;

// =============================
//    PROTOTYPE FUNGSI
// =============================

// Utilitas
void pause();

// ADMIN
bool loginAdmin();
void tampilkanMenuAdmin();
void tampilkanDaftarMenu();
void tampilkanMenuUrutRating();
void lihatDaftarMenuDanUpdateRating();
void tambahMenu();
void editMenu();
void kelolaTambahAtauEditMenu();

// PELANGGAN
void tampilkanMenuPelanggan();
void lihatKeranjang();
void editKeranjang();

// =============================
//       FUNGSI UTILITAS
// =============================
void pause() {
    cout << "\nTekan ENTER untuk lanjut...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// =============================
//       LOGIN ADMIN
// =============================
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
    }
    cout << "Username atau password salah!\n";
    pause();
    return false;
}

// =============================
//       ADMIN – TAMPIL MENU
// =============================
void tampilkanDaftarMenu() {
    cout << "\n===== DAFTAR MENU (URUT PENAMBAHAN) =====\n";
    if (daftarMenu.empty()) {
        cout << "Belum ada menu.\n";
        return;
    }

    cout << left << setw(5) << "No" << setw(20) << "Nama Menu"
         << setw(12) << "Harga" << setw(12) << "Terjual"
         << setw(8) << "Rating" << endl;
    cout << string(60, '-') << endl;

    for (int i = 0; i < daftarMenu.size(); i++) {
        cout << left << setw(5) << i + 1
             << setw(20) << daftarMenu[i].nama
             << setw(12) << ("Rp" + to_string(daftarMenu[i].harga))
             << setw(12) << daftarMenu[i].jumlahTerjual
             << setw(8) << daftarMenu[i].rating << endl;
    }
}

// =============================
//    ADMIN – URUT RATING
// =============================
void tampilkanMenuUrutRating() {
    cout << "\n===== DAFTAR MENU (URUT RATING TERTINGGI) =====\n";
    if (daftarMenu.empty()) {
        cout << "Belum ada menu.\n";
        return;
    }

    vector<Menu> temp = daftarMenu;
    sort(temp.begin(), temp.end(),
        [](const Menu &a, const Menu &b) {
            return a.rating > b.rating;
        }
    );

    cout << left << setw(5) << "No" << setw(20) << "Nama Menu"
         << setw(12) << "Harga" << setw(12) << "Terjual"
         << setw(8) << "Rating" << endl;
    cout << string(60, '-') << endl;

    for (int i = 0; i < temp.size(); i++) {
        cout << left << setw(5) << i + 1
             << setw(20) << temp[i].nama
             << setw(12) << ("Rp" + to_string(temp[i].harga))
             << setw(12) << temp[i].jumlahTerjual
             << setw(8) << temp[i].rating << endl;
    }

    cout << "\nMenu rating tertinggi: " 
         << temp[0].nama << " (Rating: " << temp[0].rating << ")\n";
}

// =============================
//     ADMIN – UPDATE RATING
// =============================
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

        if (idx > 0 && idx <= daftarMenu.size()) {
            float ratingBaru;
            cout << "Rating baru: ";
            cin >> ratingBaru;

            daftarMenu[idx - 1].rating = ratingBaru;

            cout << "\nNotifikasi: rating berhasil diupdate.\n";
            tampilkanMenuUrutRating();
        } 
        else {
            cout << "Nomor menu tidak valid.\n";
        }

        pause();
        return;
    }

    kelolaTambahAtauEditMenu();
}

// =============================
//       ADMIN – TAMBAH MENU
// =============================
void tambahMenu() {
    Menu m;
    cout << "\n===== TAMBAH MENU =====\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Nama Menu: ";
    getline(cin, m.nama);
    cout << "Harga: ";
    cin >> m.harga;
    cout << "Jumlah terjual: ";
    cin >> m.jumlahTerjual;
    cout << "Rating: ";
    cin >> m.rating;

    daftarMenu.push_back(m);

    cout << "Notifikasi: menu baru berhasil ditambahkan!\n";
    tampilkanDaftarMenu();
    pause();
}

// =============================
//        ADMIN – EDIT MENU
// =============================
void editMenu() {
    if (daftarMenu.empty()) {
        cout << "\nBelum ada menu.\n";
        pause();
        return;
    }

    cout << "\n===== EDIT MENU =====\n";
    tampilkanDaftarMenu();

    int idx;
    cout << "Pilih menu (No): ";
    cin >> idx;

    if (idx > 0 && idx <= daftarMenu.size()) {
        Menu &m = daftarMenu[idx - 1];

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nData lama:\n";
        cout << "Nama: " << m.nama << endl;
        cout << "Harga: " << m.harga << endl;
        cout << "Terjual: " << m.jumlahTerjual << endl;
        cout << "Rating: " << m.rating << endl;

        cout << "\nData baru:\n";
        cout << "Nama Menu baru: ";
        getline(cin, m.nama);
        cout << "Harga baru: ";
        cin >> m.harga;
        cout << "Jumlah terjual baru: ";
        cin >> m.jumlahTerjual;
        cout << "Rating baru: ";
        cin >> m.rating;

        cout << "Notifikasi: menu berhasil diedit!\n";
    } 
    else {
        cout << "Nomor tidak valid.\n";
    }

    pause();
}

// =============================
// ADMIN – PILIH TAMBAH/EDIT
// =============================
void kelolaTambahAtauEditMenu() {
    char jawab;
    cout << "\nTambah menu? (y/n): ";
    cin >> jawab;

    if (jawab == 'y' || jawab == 'Y')
        tambahMenu();
    else
        editMenu();
}

// =============================
//        MENU ADMIN
// =============================
void tampilkanMenuAdmin() {
    int pilih;
    do {
        cout << "\n===== MENU ADMIN =====\n";
        cout << "1. Lihat daftar menu (+ update rating)\n";
        cout << "2. Tambah / Edit menu\n";
        cout << "0. Logout\nPilih: ";
        cin >> pilih;

        if (pilih == 1)
            lihatDaftarMenuDanUpdateRating();
        else if (pilih == 2)
            kelolaTambahAtauEditMenu();

    } while (pilih != 0);
}

// =============================
//    PELANGGAN – LIHAT KERANJANG
// =============================
void lihatKeranjang() {
    if (keranjang.empty()) {
        cout << "\nKeranjang kosong.\n";
        return;
    }

    int total = 0;
    cout << "\n===== KERANJANG =====\n";

    for (int i = 0; i < keranjang.size(); i++) {
        cout << i + 1 << ". " << keranjang[i].nama
             << " x" << keranjang[i].jumlah
             << " = Rp" << keranjang[i].harga * keranjang[i].jumlah << endl;

        total += keranjang[i].harga * keranjang[i].jumlah;
    }
    cout << "Total: Rp" << total << endl;
}

// =============================
//   PELANGGAN – EDIT KERANJANG
// =============================
void editKeranjang() {
    int pilih;

    do {
        lihatKeranjang();

        cout << "\n1. Ubah jumlah item\n";
        cout << "2. Hapus item\n";
        cout << "3. Pesan sekarang\n";
        cout << "0. Kembali\nPilih: ";
        cin >> pilih;

        if (pilih == 1) {
            int idx, jumlahBaru;
            cout << "Nomor item: ";
            cin >> idx;

            if (idx > 0 && idx <= keranjang.size()) {
                cout << "Jumlah baru: ";
                cin >> jumlahBaru;

                if (jumlahBaru <= 0) {
                    keranjang.erase(keranjang.begin() + idx - 1);
                    cout << "Item dihapus.\n";
                } else {
                    keranjang[idx - 1].jumlah = jumlahBaru;
                }
            }
        }
        else if (pilih == 2) {
            int idx;
            cout << "Nomor item: ";
            cin >> idx;

            if (idx > 0 && idx <= keranjang.size()) {
                keranjang.erase(keranjang.begin() + idx - 1);
                cout << "Item dihapus.\n";
            }
        }
        else if (pilih == 3) {
            if (keranjang.empty()) {
                cout << "Keranjang kosong.\n";
                continue;
            }

            int total = 0;
            for (auto &k : keranjang)
                total += k.harga * k.jumlah;

            cout << "\nTotal bayar: Rp" << total << endl;
            cout << "Pesanan berhasil dibuat!\n";
            keranjang.clear();
            break;
        }

    } while (pilih != 0);
}

// =============================
//       PELANGGAN – MENU
// =============================
void tampilkanMenuPelanggan() {
    int pilih;

    do {
        cout << "\n===== MENU PELANGGAN =====\n";
        cout << "1. Lihat Rekomendasi & Tambah ke Keranjang\n";
        cout << "2. Lihat / Edit Keranjang\n";
        cout << "0. Kembali\nPilih: ";
        cin >> pilih;

        if (pilih == 1) {
            if (daftarMenu.empty()) {
                cout << "Belum ada menu.\n";
                pause();
                continue;
            }

            vector<Menu> temp = daftarMenu;
            sort(temp.begin(), temp.end(),
                [](Menu &a, Menu &b) { return a.rating > b.rating; });

            cout << "\n===== REKOMENDASI =====\n";

            cout << left << setw(5) << "No" << setw(20) << "Nama Menu"
                 << setw(12) << "Harga" << setw(12) << "Terjual"
                 << setw(8) << "Rating" << endl;
            cout << string(60, '-') << endl;

            for (int i = 0; i < temp.size(); i++) {
                cout << left << setw(5) << i + 1
                     << setw(20) << temp[i].nama
                     << setw(12) << ("Rp" + to_string(temp[i].harga))
                     << setw(12) << temp[i].jumlahTerjual
                     << setw(8) << temp[i].rating << endl;
            }

            cout << "\nMasukkan nomor menu (pisahkan spasi): ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string input;
            getline(cin, input);

            stringstream ss(input);
            int idx;

            while (ss >> idx) {
                if (idx > 0 && idx <= temp.size()) {
                    int jumlah;
                    cout << "Jumlah " << temp[idx - 1].nama << ": ";
                    cin >> jumlah;

                    keranjang.push_back({
                        temp[idx - 1].nama,
                        temp[idx - 1].harga,
                        jumlah
                    });
                }
            }

            cout << "Item berhasil ditambahkan.\n";
            pause();
        }

        else if (pilih == 2) {
            editKeranjang();
        }

    } while (pilih != 0);
}

// =============================
//           MAIN
// =============================
int main() {
    int pilihan;
    bool isLogin = false;

    do {
        cout << "\n===== SISTEM REKOMENDASI MENU RESTORAN =====\n";
        cout << "1. Login Admin\n";
        cout << "2. Menu Pelanggan\n";
        cout << "0. Keluar\nPilih: ";
        cin >> pilihan;

        if (pilihan == 1) {
            isLogin = loginAdmin();
            if (isLogin) tampilkanMenuAdmin();
        }
        else if (pilihan == 2) {
            tampilkanMenuPelanggan();
        }

    } while (pilihan != 0);

    cout << "\nTerima kasih telah menggunakan sistem ini!\n";
    return 0;
}
