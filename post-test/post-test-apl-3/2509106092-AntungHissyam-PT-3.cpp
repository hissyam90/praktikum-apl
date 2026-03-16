#include <iostream>
#include <string>

using namespace std;

// data
struct Akun {
    string nama_pengguna;
    string password_pengguna;
};

struct Alamat {
    string kota;
    string jalan;
};

struct Pegawai {
    string nama_pegawai;
    string jabatan;
    Alamat lokasi; 
};



// fungsi overloading
void tampilkanHeader();
void tampilkanHeader(string sub_judul);

// fungsi rekursif
void prosesKeluar(int detik);

// prosedul & fungsi CRUD
void registerAkun(Akun daftar_akun[], int &total_akun);
bool loginAkun(Akun daftar_akun[], int total_akun);
void tambahPegawai(Pegawai daftar_pegawai[], int &total_pegawai);
void lihatPegawai(Pegawai daftar_pegawai[], int total_pegawai);
void ubahPegawai(Pegawai daftar_pegawai[], int total_pegawai);
void hapusPegawai(Pegawai daftar_pegawai[], int &total_pegawai);


// program utama
int main() {
    Akun daftar_akun[100];
    int total_akun = 0;
    Pegawai daftar_pegawai[100];
    int total_pegawai = 0;

    int menu_awal;
    bool aplikasi_berjalan = true;

    while (aplikasi_berjalan) {
        tampilkanHeader();
        cout << "1. Register Akun Baru\n";
        cout << "2. Login\n";
        cout << "3. Keluar Aplikasi\n";
        cout << "Pilihan: ";
        cin >> menu_awal;

        switch (menu_awal) {
            case 1: 
                registerAkun(daftar_akun, total_akun);
                break;
            case 2: 
                if (loginAkun(daftar_akun, total_akun)) {
                    int menu_crud;
                    bool sesi_login = true;

                    do {
                        tampilkanHeader("MENU MANAJEMEN PEGAWAI");
                        cout << "1. Tambah Pegawai (Create)\n";
                        cout << "2. Lihat Daftar Pegawai (Read)\n";
                        cout << "3. Ubah Data Pegawai (Update)\n";
                        cout << "4. Hapus Pegawai (Delete)\n";
                        cout << "5. Logout\n";
                        cout << "Pilihan: ";
                        cin >> menu_crud;

                        switch (menu_crud) {
                            case 1: tambahPegawai(daftar_pegawai, total_pegawai); break;
                            case 2: lihatPegawai(daftar_pegawai, total_pegawai); break;
                            case 3: ubahPegawai(daftar_pegawai, total_pegawai); break;
                            case 4: hapusPegawai(daftar_pegawai, total_pegawai); break;
                            case 5: 
                                cout << "Logout berhasil. Kembali ke menu autentikasi...\n";
                                sesi_login = false; 
                                break;
                            default: cout << "[!] Pilihan tidak valid!\n";
                        }
                    } while (sesi_login);
                }
                break;
            case 3: 
                prosesKeluar(3); 
                aplikasi_berjalan = false;
                break;
            default: 
                cout << "[!] Pilihan tidak valid!\n";
        }
    }
    return 0;
}


// implementasi overloading
void tampilkanHeader() {
    cout << "\n=========================================\n";
    cout << "  SISTEM PEGAWAI KEBAB CENDANA (ADMIN)   \n";
    cout << "=========================================\n";
}

void tampilkanHeader(string sub_judul) {
    cout << "\n=========================================\n";
    cout << "        " << sub_judul << "        \n";
    cout << "=========================================\n";
}

// implementasi rekursif
void prosesKeluar(int detik) {
    if (detik == 0) {
        cout << "Terima kasih telah menggunakan aplikasi ini!\n";
        return; 
    }
    cout << "Aplikasi akan tertutup dalam " << detik << "...\n";
    prosesKeluar(detik - 1); 
}

// prosedur & fungsi CRUD
void registerAkun(Akun daftar_akun[], int &total_akun) {
    cout << "\n--- REGISTER ---\n";
    cout << "Masukkan Nama (Tanpa Spasi) : ";
    cin >> daftar_akun[total_akun].nama_pengguna;
    cout << "Masukkan Password           : ";
    cin >> daftar_akun[total_akun].password_pengguna;
    total_akun++;
    cout << "[+] Akun berhasil didaftarkan! Silakan Login.\n";
}

bool loginAkun(Akun daftar_akun[], int total_akun) {
    if (total_akun == 0) {
        cout << "[!] Belum ada akun yang terdaftar. Silakan Register dulu.\n";
        return false;
    }

    int sisa_kesempatan = 3;
    string input_nama, input_password;

    cout << "\n--- LOGIN ---\n";
    while (sisa_kesempatan > 0) {
        cout << "Masukkan Nama     : ";
        cin >> input_nama;
        cout << "Masukkan Password : ";
        cin >> input_password;

        for (int i = 0; i < total_akun; i++) {
            if (input_nama == daftar_akun[i].nama_pengguna && input_password == daftar_akun[i].password_pengguna) {
                cout << "\n[+] Login Berhasil! Selamat datang, " << input_nama << ".\n";
                return true; 
            }
        }

        sisa_kesempatan--;
        if (sisa_kesempatan > 0) {
            cout << "[!] Nama atau Password salah! Sisa percobaan: " << sisa_kesempatan << "\n\n";
        }
    }

    cout << "\n[X] Anda gagal login 3 kali. Kembali ke menu utama.\n";
    return false; 
}

// create
void tambahPegawai(Pegawai daftar_pegawai[], int &total_pegawai) {
    cout << "\n--- TAMBAH PEGAWAI ---\n";
    cout << "Nama Pegawai : ";
    cin.ignore(); 
    getline(cin, daftar_pegawai[total_pegawai].nama_pegawai);
    
    cout << "Jabatan      : ";
    getline(cin, daftar_pegawai[total_pegawai].jabatan);
    
    cout << "Kota         : ";
    getline(cin, daftar_pegawai[total_pegawai].lokasi.kota);
    
    cout << "Jalan        : ";
    getline(cin, daftar_pegawai[total_pegawai].lokasi.jalan);

    total_pegawai++;
    cout << "[+] Data pegawai berhasil ditambahkan!\n";
}

// read
void lihatPegawai(Pegawai daftar_pegawai[], int total_pegawai) {
    cout << "\n--- DAFTAR PEGAWAI KEBAB CENDANA ---\n";
    if (total_pegawai == 0) {
        cout << "Belum ada data pegawai.\n";
    } else {
        cout << "---------------------------------------------------------------------------------\n";
        cout << "No.\t| Nama                | Jabatan             | Alamat (Kota, Jalan)\n";
        cout << "---------------------------------------------------------------------------------\n";
        
        for (int i = 0; i < total_pegawai; i++) {
            cout << i + 1 << "\t| ";
            
            string nama = daftar_pegawai[i].nama_pegawai;
            cout << nama;
            for (int s = nama.length(); s < 20; s++) { cout << " "; }
            cout << "| ";

            string jabatan = daftar_pegawai[i].jabatan;
            cout << jabatan;
            for (int s = jabatan.length(); s < 20; s++) { cout << " "; }
            cout << "| ";

            cout << daftar_pegawai[i].lokasi.kota << ", " 
                 << daftar_pegawai[i].lokasi.jalan << "\n";
        }
        cout << "---------------------------------------------------------------------------------\n";
    }
}

// update
void ubahPegawai(Pegawai daftar_pegawai[], int total_pegawai) {
    cout << "\n--- UBAH DATA PEGAWAI ---\n";
    if (total_pegawai == 0) {
        cout << "Belum ada pegawai untuk diubah.\n";
    } else {
        int index_pegawai;
        cout << "Masukkan nomor pegawai yang akan diubah: ";
        cin >> index_pegawai;

        if (index_pegawai > 0 && index_pegawai <= total_pegawai) {
            cout << "Masukkan nama baru   : ";
            cin.ignore();
            getline(cin, daftar_pegawai[index_pegawai - 1].nama_pegawai);
            
            cout << "Masukkan jabatan baru: ";
            getline(cin, daftar_pegawai[index_pegawai - 1].jabatan);
            
            cout << "Masukkan kota baru   : ";
            getline(cin, daftar_pegawai[index_pegawai - 1].lokasi.kota);
            
            cout << "Masukkan jalan baru  : ";
            getline(cin, daftar_pegawai[index_pegawai - 1].lokasi.jalan);
            
            cout << "[+] Data berhasil diubah.\n";
        } else {
            cout << "[!] Nomor pegawai tidak valid.\n";
        }
    }
}

// delete
void hapusPegawai(Pegawai daftar_pegawai[], int &total_pegawai) {
    cout << "\n--- HAPUS DATA PEGAWAI ---\n";
    if (total_pegawai == 0) {
        cout << "Belum ada pegawai untuk dihapus.\n";
    } else {
        int index_pegawai;
        cout << "Masukkan nomor pegawai yang akan dihapus: ";
        cin >> index_pegawai;

        if (index_pegawai > 0 && index_pegawai <= total_pegawai) {
            for (int i = index_pegawai - 1; i < total_pegawai - 1; i++) {
                daftar_pegawai[i] = daftar_pegawai[i + 1];
            }
            total_pegawai--;
            cout << "[+] Pegawai berhasil dihapus.\n";
        } else {
            cout << "[!] Nomor pegawai tidak valid.\n";
        }
    }
}