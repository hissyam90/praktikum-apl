#include <iostream>
#include <string>

using namespace std;

struct Akun {
    string nama_pengguna;
    string password_pengguna;
};

// nested struct 
struct Alamat {
    string kota;
    string jalan;
};

// main struct
struct Pegawai {
    string nama_pegawai;
    string jabatan;
    Alamat lokasi; 
};

int main() {
    Akun daftar_akun[100];
    int total_akun = 0;
    Pegawai daftar_pegawai[100];
    int total_pegawai = 0;

    int menu_awal;
    bool aplikasi_berjalan = true;

    cout << "=========================================\n";
    cout << "       SISTEM PEGAWAI KEBAB CENDANA      \n";
    cout << "=========================================\n";

    while (aplikasi_berjalan) {
        cout << "\n--- MENU AUTENTIKASI ---\n";
        cout << "1. Register Akun Baru\n";
        cout << "2. Login\n";
        cout << "3. Keluar Aplikasi\n";
        cout << "Pilihan: ";
        cin >> menu_awal;

        switch (menu_awal) {
            case 1: {
                cout << "\n--- REGISTER ---\n";
                cout << "Masukkan Nama (Tanpa Spasi) : ";
                cin >> daftar_akun[total_akun].nama_pengguna;
                cout << "Masukkan Password           : ";
                cin >> daftar_akun[total_akun].password_pengguna;
                total_akun++;
                cout << "[+] Akun berhasil didaftarkan! Silakan Login.\n";
                break;
            }
            case 2: {
                if (total_akun == 0) {
                    cout << "[!] Belum ada akun yang terdaftar. Silakan Register dulu.\n";
                } else {
                    int sisa_kesempatan = 3;
                    bool login_sukses = false;
                    string input_nama;
                    string input_password;

                    cout << "\n--- LOGIN ---\n";
                    while (sisa_kesempatan > 0 && !login_sukses) {
                        cout << "Masukkan Nama     : ";
                        cin >> input_nama;
                        cout << "Masukkan Password : ";
                        cin >> input_password;

                        for (int i = 0; i < total_akun; i++) {
                            if (input_nama == daftar_akun[i].nama_pengguna && input_password == daftar_akun[i].password_pengguna) {
                                login_sukses = true;
                            }
                        }

                        if (login_sukses) {
                            cout << "\n[+] Login Berhasil! Selamat datang, " << input_nama << ".\n";
                        } else {
                            sisa_kesempatan--;
                            if (sisa_kesempatan > 0) {
                                cout << "[!] Nama atau Password salah! Sisa percobaan: " << sisa_kesempatan << "\n\n";
                            }
                        }
                    }

                    if (!login_sukses) {
                        cout << "\n[X] Anda gagal login 3 kali. Program berhenti otomatis.\n";
                        return 0; 
                    }

                    int menu_crud;
                    int index_pegawai; 
                    bool sesi_login = true;

                    do {
                        cout << "\n=========================================\n";
                        cout << "          MENU MANAJEMEN PEGAWAI         \n";
                        cout << "=========================================\n";
                        cout << "1. Tambah Pegawai (Create)\n";
                        cout << "2. Lihat Daftar Pegawai (Read)\n";
                        cout << "3. Ubah Data Pegawai (Update)\n";
                        cout << "4. Hapus Pegawai (Delete)\n";
                        cout << "5. Logout\n";
                        cout << "Pilihan: ";
                        cin >> menu_crud;

                        switch (menu_crud) {
                            case 1: {
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
                                break;
                            }
                            case 2: {
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
                                        for (int s = nama.length(); s < 20; s++) {
                                            cout << " ";
                                        }
                                        cout << "| ";
                                        string jabatan = daftar_pegawai[i].jabatan;
                                        cout << jabatan;
                                        for (int s = jabatan.length(); s < 20; s++) {
                                            cout << " ";
                                        }
                                        cout << "| ";
                                        cout << daftar_pegawai[i].lokasi.kota << ", " 
                                             << daftar_pegawai[i].lokasi.jalan << "\n";
                                    }
                                    cout << "---------------------------------------------------------------------------------\n";
                                }
                                break;
                            }
                            case 3: {
                                cout << "\n--- UBAH DATA PEGAWAI ---\n";
                                if (total_pegawai == 0) {
                                    cout << "Belum ada pegawai untuk diubah.\n";
                                } else {
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
                                break;
                            }
                            case 4: {
                                cout << "\n--- HAPUS DATA PEGAWAI ---\n";
                                if (total_pegawai == 0) {
                                    cout << "Belum ada pegawai untuk dihapus.\n";
                                } else {
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
                                break;
                            }
                            case 5: {
                                cout << "Logout berhasil. Kembali ke menu autentikasi...\n";
                                sesi_login = false; 
                                break;
                            }
                            default: {
                                cout << "[!] Pilihan tidak valid!\n";
                                break;
                            }
                        }
                    } while (sesi_login);
                }
                break;
            }
            case 3: {
                cout << "Terima kasih telah menggunakan aplikasi Manajemen Pegawai Kebab Cendana!\n";
                aplikasi_berjalan = false;
                break;
            }
            default: {
                cout << "[!] Pilihan tidak valid!\n";
                break;
            }
        }
    }

    return 0;
}