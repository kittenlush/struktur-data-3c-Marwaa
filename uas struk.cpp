#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

struct item {
    string menu;
    int jumlah;
    int harga;
};

struct pesanan {
    string nama_pelanggan;
    item items[5];
    int jumlah_item;
    int total_bayar;
    int bayar;
    int kembali;
};

const int MAX_PESANAN = 50;
pesanan antrian[MAX_PESANAN];
int jumlah_pesanan = 0;

void clearScreen() {
    system("CLS"); // Note: Works only on Windows.
}

void tambahPesanan() {
    if (jumlah_pesanan >= MAX_PESANAN) {
        cout << "Antrean penuh. Tidak bisa menambahkan pesanan lagi.\n";
        return;
    }

    pesanan p;
    p.jumlah_item = 0;
    p.total_bayar = 0;
    int pilihan;

    cout << "----------------------------------------------------------------------------------------\n";
    cout << "Masukkan nama pelanggan: ";
    cin >> ws;
    getline(cin, p.nama_pelanggan);

    while (true) {
        cout << "1. Nasi Goreng		(Rp.15.000)\n";
        cout << "2. Mie Goreng		(Rp.10.000)\n";
        cout << "3. Tempe Mendoan	(Rp.9.000)\n";
        cout << "4. Es Jeruk		(Rp.8.000)\n";
        cout << "5. Teh Hangat		(Rp.5.000)\n";
        cout << "Pilihan 1 - 5 (ketik 0 untuk selesai): ";
        cin >> pilihan;

        if (pilihan == 0) {
            break;
        }

        if (p.jumlah_item >= 5) {
            cout << "Maksimal item per pesanan adalah 5.\n";
            break;
        }

        item item;
        switch (pilihan) {
            case 1:
                item.menu = "Nasi Goreng";
                item.harga = 15000;
                break;
            case 2:
                item.menu = "Mie Goreng";
                item.harga = 10000;
                break;
            case 3:
                item.menu = "Tempe Mendoan";
                item.harga = 9000;
                break;
            case 4:
                item.menu = "Es Jeruk";
                item.harga = 8000;
                break;
            case 5:
                item.menu = "Teh Hangat";
                item.harga = 5000;
                break;
            default:
                cout << "Menu tidak valid.\n";
                continue;
        }

        cout << "Jumlah yang dipesan: ";
        cin >> item.jumlah;
        cout << "----------------------------------------------------------------------------------------\n";

        int total_harga_item = item.harga * item.jumlah;
        item.harga = total_harga_item;
        p.items[p.jumlah_item++] = item;
        p.total_bayar += total_harga_item;
    }

    if (p.jumlah_item == 0) {
        cout << "Tidak ada menu yang dipilih.\n";
        return;
    }

    cout << "----------------------------------------------------------------------------------------\n";
    cout << "Total yang harus dibayar\t: Rp " << p.total_bayar << endl;
    cout << "Masukkan jumlah bayar\t\t: Rp ";
    cin >> p.bayar;

    if (p.bayar < p.total_bayar) {
        cout << "Uang yang diberikan tidak cukup untuk membayar pesanan.\n";
        return;
    }
    p.kembali = p.bayar - p.total_bayar;
    antrian[jumlah_pesanan++] = p;
    cout << "Kembali : Rp " << p.kembali << endl;
    cout << "Pesanan berhasil ditambahkan!\n";

    cout << "Tekan enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
    clearScreen();
}

void urutkanPesanan() {
    for (int i = 0; i < jumlah_pesanan - 1; ++i) {
        for (int j = 0; j < jumlah_pesanan - i - 1; ++j) {
            if (antrian[j].total_bayar > antrian[j + 1].total_bayar) {
                pesanan temp = antrian[j];
                antrian[j] = antrian[j + 1];
                antrian[j + 1] = temp;
            }
        }
    }
    cout << "----------------------------------------------------------------------------------------\n";
    cout << "Antrian berhasil diurutkan berdasarkan total bayar\n";
    cout << "----------------------------------------------------------------------------------------\n";

    cout << "\n---Daftar Antrian Pesanan Setelah Diurutkan---\n";
    cout << "----------------------------------------------------------------------------------------\n";

    for (int i = 0; i < jumlah_pesanan; ++i) {
        cout << "Antrian " << i + 1 << ":\n";
        cout << "Nama Pelanggan: " << antrian[i].nama_pelanggan << endl;
        cout << "Items:\n";
        for (int j = 0; j < antrian[i].jumlah_item; ++j) {
            cout << "- " << antrian[i].items[j].menu
                 << " x" << antrian[i].items[j].jumlah
                 << " = Rp " << antrian[i].items[j].harga << endl;
        }
        cout << "Total bayar : Rp " << antrian[i].total_bayar << endl;
        cout << "----------------------------------------------------------------------------------------\n";
    }

    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
    clearScreen();
}

void cariPesanan() {
    if (jumlah_pesanan == 0) {
        cout << "Tidak ada antrian pesanan saat ini.\n";
        return;
    }

    string nama;
    cout << "Masukkan nama pelanggan yang ingin dicari: ";
    cin >> ws;
    getline(cin, nama);

    bool ditemukan = false;
    cout << "\n---Hasil Pencarian Pesanan---\n";
    cout << "----------------------------------------------------------------------------------------\n";
    for (int i = 0; i < jumlah_pesanan; ++i) {
        if (antrian[i].nama_pelanggan == nama) {
            cout << "Antrian " << i + 1 << ":\n";
            cout << "Nama Pelanggan: " << antrian[i].nama_pelanggan << endl;
            cout << "Items:\n";
            for (int j = 0; j < antrian[i].jumlah_item; ++j) {
                cout << "- " << antrian[i].items[j].menu
                     << " x" << antrian[i].items[j].jumlah
                     << " = Rp " << antrian[i].items[j].harga << endl;
            }
            cout << "Total bayar: Rp " << antrian[i].total_bayar << endl;
            cout << "Bayar: Rp " << antrian[i].bayar << endl;
            cout << "Kembali: Rp " << antrian[i].kembali << endl;
            cout << "----------------------------------------------------------------------------------------\n";
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "Pesanan dengan nama " << nama << " tidak ditemukan.\n";
    }

    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
    clearScreen();
}

void lihatAntrian() {
    if (jumlah_pesanan == 0) {
        cout << "Tidak ada antrian pesanan saat ini.\n";
        return;
    }

    cout << "\n---Daftar Antrian Pesanan---\n";
    cout << "----------------------------------------------------------------------------------------\n";
    for (int i = 0; i < jumlah_pesanan; ++i) {
        cout << "Antrian " << i + 1 << ":\n";
        cout << "Nama Pelanggan: " << antrian[i].nama_pelanggan << endl;

        cout << "Items:\n";
        for (int j = 0; j < antrian[i].jumlah_item; ++j) {
            cout << "- " << antrian[i].items[j].menu
                 << " x" << antrian[i].items[j].jumlah
                 << " = Rp " << antrian[i].items[j].harga << endl;
        }

        cout << "Total Bayar: Rp " << antrian[i].total_bayar << endl;
        cout << "Bayar: Rp " << antrian[i].bayar << endl;
        cout << "Kembali: Rp " << antrian[i].kembali << endl;
        cout << "----------------------------------------------------------------------------------------\n";
    }

    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
    clearScreen();
}

int main() {
    int pilihan;
    do {
        cout << "----------------------------------------------------------------------------------------\n";
        cout << "		SELAMAT DATANG DI RESTORAN SKY TERRACE\n";
        cout << "----------------------------------------------------------------------------------------\n";
        cout << "	Nama	: Marwaa Fauziah Afandy\n";
        cout << "	NIM		: 2305101043\n";
        cout << "	Kelas	: 3C\n";
        cout << "----------------------------------------------------------------------------------------\n";
        cout << "------------------------------MENU------------------------------\n";
        cout << "1. Tambah Pesanan\n";
        cout << "2. Lihat Antrian\n";
        cout << "3. Urutkan Antrian Berdasarkan Total Bayar\n";
        cout << "4. Cari Pesanan Berdasarkan Nama Pelanggan\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahPesanan();
                break;
            case 2:
                lihatAntrian();
                break;
            case 3:
                urutkanPesanan();
                break;
            case 4:
                cariPesanan();
                break;
            case 0:
                cout << "Terima kasih telah mengunjungi restoran sky terrace!\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 0);

    return 0;
}

