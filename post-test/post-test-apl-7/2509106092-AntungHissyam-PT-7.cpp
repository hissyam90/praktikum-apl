#include <iostream>
#include <string>
#include <iomanip>    // buat manipulasi output tabel
#include <stdlib.h>   // buat cls
#include <stdexcept>  // libary untuk exception handling
#include <limits>
#include "kebab.h"   

using namespace std;

void bersihkanLayar() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void prosesKeluar(int detik) {
    if (detik == 0) {
        cout << "Terima kasih telah menggunakan aplikasi ini!\n";
        return;
    }
    cout << "Aplikasi akan tertutup dalam " << detik << "...\n";
    prosesKeluar(detik - 1);
}

// autentikasi
void registerAkun(Akun daftar_akun[], int &total_akun) {
    bersihkanLayar();
    cout << "--- Register ---\n";
    cout << "Masukkan Nama (Tanpa Spasi) : ";
    cin >> daftar_akun[total_akun].nama_pengguna;
    cout << "Masukkan Password           : ";
    cin >> daftar_akun[total_akun].password_pengguna;
    
    total_akun++; 
    cout << "[+] Akun berhasil didaftarkan! Silakan Login.\n";
}

bool loginAkun(Akun daftar_akun[], int total_akun) {
    bersihkanLayar();
    if (total_akun == 0) {
        cout << "[!] Belum ada akun. Silakan Register dulu.\n";
        return false;
    }

    int sisa_kesempatan = 3;
    string input_nama, input_password;

    cout << "--- Login ---\n";
    while (sisa_kesempatan > 0) {
        cout << "Masukkan Nama     : ";
        cin >> input_nama;
        cout << "Masukkan Password : ";
        cin >> input_password;

        for (int i = 0; i < total_akun; i++) {
            if (input_nama == daftar_akun[i].nama_pengguna && input_password == daftar_akun[i].password_pengguna) {
                bersihkanLayar();
                cout << "[+] Login Berhasil! Selamat datang, " << input_nama << ".\n";
                return true; 
            }
        }
        sisa_kesempatan--;
        if (sisa_kesempatan > 0) cout << "[!] Nama atau Password salah! Sisa: " << sisa_kesempatan << "\n\n";
    }
    cout << "\n[X] Gagal login 3 kali. Kembali ke menu utama.\n";
    return false; 
}

// crud
void tambahPegawai(Pegawai daftar_pegawai[], int *total_pegawai) {
    int indeks = *total_pegawai;
    bersihkanLayar();
    cout << "--- Tambah Pegawai ---\n";
    
    try {
        cout << "Nama Pegawai : ";
        cin.ignore(); 
        getline(cin, daftar_pegawai[indeks].nama_pegawai);
        
        cout << "Umur         : ";
        if (!(cin >> daftar_pegawai[indeks].umur)) {
            throw runtime_error("Input umur harus berupa angka bulat!");
        }
        if (daftar_pegawai[indeks].umur <= 0) {
            throw invalid_argument("Umur tidak valid (tidak boleh nol atau minus)!");
        }
        
        cout << "Jabatan      : ";
        cin.ignore();
        getline(cin, daftar_pegawai[indeks].jabatan);
        
        daftar_pegawai[indeks].jabatan_ptr = &daftar_pegawai[indeks].jabatan;
        
        cout << "Kota         : ";
        getline(cin, daftar_pegawai[indeks].lokasi.kota);
        
        cout << "Jalan        : ";
        getline(cin, daftar_pegawai[indeks].lokasi.jalan);

        (*total_pegawai)++; 
        cout << "[+] Data pegawai berhasil ditambahkan!\n";

    } catch (const exception& e) {
        cout << "\n[!] Gagal menambahkan pegawai: " << e.what() << "\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void lihatPegawai(Pegawai daftar_pegawai[], int *total_pegawai) {
    bersihkanLayar();
    cout << "--- Daftar Pegawai Kebab Cendana ---\n";
    if (*total_pegawai == 0) {
        cout << "Belum ada data pegawai.\n";
    } else {
        cout << setfill('-') << setw(85) << "-" << endl;
        cout << setfill(' ');
        cout << left << setw(5) << "No." 
             << left << setw(20) << "Nama" 
             << left << setw(8) << "Umur" 
             << left << setw(20) << "Jabatan" 
             << "Alamat (Kota, Jalan)\n";
        cout << setfill('-') << setw(85) << "-" << endl;
        cout << setfill(' ');
        
        for (int i = 0; i < *total_pegawai; i++) {
            cout << left << setw(5) << i + 1
                 << left << setw(20) << daftar_pegawai[i].nama_pegawai
                 << left << setw(8) << daftar_pegawai[i].umur
                 << left << setw(20) << *(daftar_pegawai[i].jabatan_ptr)
                 << daftar_pegawai[i].lokasi.kota << ", " 
                 << daftar_pegawai[i].lokasi.jalan << "\n";
        }
        cout << setfill('-') << setw(85) << "-" << endl;
    }
}

void ubahPegawai(Pegawai daftar_pegawai[], int *total_pegawai) {
    int batas = *total_pegawai;
    bersihkanLayar();
    lihatPegawai(daftar_pegawai, total_pegawai);
    cout << "\n--- Ubah Data Pegawai ---\n";
    
    if (batas == 0) return;

    try {
        int index_pegawai;
        cout << "Masukkan nomor pegawai yang akan diubah: ";
        if (!(cin >> index_pegawai)) {
            throw runtime_error("Format nomor pegawai salah (harus angka)!");
        }
        if (index_pegawai < 1 || index_pegawai > batas) {
            throw out_of_range("Nomor pegawai tidak ditemukan di dalam tabel!");
        }

        int idx = index_pegawai - 1;
        cout << "Masukkan nama baru   : ";
        cin.ignore();
        getline(cin, daftar_pegawai[idx].nama_pegawai);
        
        cout << "Masukkan umur baru   : ";
        if (!(cin >> daftar_pegawai[idx].umur) || daftar_pegawai[idx].umur <= 0) {
            throw runtime_error("Input umur tidak valid!");
        }
        
        cout << "Masukkan jabatan baru: ";
        cin.ignore();
        getline(cin, daftar_pegawai[idx].jabatan);
        
        daftar_pegawai[idx].jabatan_ptr = &daftar_pegawai[idx].jabatan;
        
        cout << "Masukkan kota baru   : ";
        getline(cin, daftar_pegawai[idx].lokasi.kota);
        
        cout << "Masukkan jalan baru  : ";
        getline(cin, daftar_pegawai[idx].lokasi.jalan);
        
        cout << "[+] Data berhasil diubah.\n";

    } catch (const exception& e) {
        cout << "\n[!] Gagal mengubah data: " << e.what() << "\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void hapusPegawai(Pegawai daftar_pegawai[], int *total_pegawai) {
    int batas = *total_pegawai;
    bersihkanLayar();
    lihatPegawai(daftar_pegawai, total_pegawai);
    cout << "\n--- Hapus Data Pegawai ---\n";
    
    if (batas == 0) return;

    try {
        int index_pegawai;
        cout << "Masukkan nomor pegawai yang akan dihapus: ";
        if (!(cin >> index_pegawai)) {
            throw runtime_error("Format nomor pegawai salah (harus angka)!");
        }
        if (index_pegawai < 1 || index_pegawai > batas) {
            throw out_of_range("Nomor pegawai tidak ada di tabel!");
        }

        for (int i = index_pegawai - 1; i < batas - 1; i++) {
            daftar_pegawai[i] = daftar_pegawai[i + 1];
        }
        (*total_pegawai)--; 
        perbaikiPointer(daftar_pegawai, *total_pegawai);
        cout << "[+] Pegawai berhasil dihapus.\n";

    } catch (const exception& e) {
        cout << "\n[!] Gagal menghapus: " << e.what() << "\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// area sorting
void mergeNamaDesc(Pegawai* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    Pegawai* L = new Pegawai[n1];
    Pegawai* R = new Pegawai[n2];
    for (int i = 0; i < n1; i++) *(L + i) = *(arr + left + i);
    for (int j = 0; j < n2; j++) *(R + j) = *(arr + mid + 1 + j);
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if ((L + i)->nama_pegawai >= (R + j)->nama_pegawai) *(arr + k++) = *(L + i++);
        else *(arr + k++) = *(R + j++);
    }
    while (i < n1) *(arr + k++) = *(L + i++);
    while (j < n2) *(arr + k++) = *(R + j++);
    delete[] L; delete[] R;
}
void mergeSortNama(Pegawai* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortNama(arr, left, mid);
        mergeSortNama(arr, mid + 1, right);
        mergeNamaDesc(arr, left, mid, right);
    }
}
void swapPegawai(Pegawai* a, Pegawai* b) { Pegawai temp = *a; *a = *b; *b = temp; }
int partitionUmur(Pegawai* arr, int low, int high) {
    int pivot = (arr + high)->umur; int i = (low - 1);
    for (int j = low; j <= high - 1; j++) if ((arr + j)->umur < pivot) swapPegawai((arr + ++i), (arr + j));
    swapPegawai((arr + i + 1), (arr + high)); return (i + 1);
}
void quickSortUmur(Pegawai* arr, int low, int high) {
    if (low < high) {
        int pi = partitionUmur(arr, low, high);
        quickSortUmur(arr, low, pi - 1);
        quickSortUmur(arr, pi + 1, high);
    }
}
void insertionSortJabatan(Pegawai* arr, int n) {
    for (int i = 1; i < n; i++) {
        Pegawai key = *(arr + i); int j = i - 1;
        while (j >= 0 && (arr + j)->jabatan > key.jabatan) { *(arr + j + 1) = *(arr + j); j--; }
        *(arr + j + 1) = key;
    }
}

// area searching
void sequentialSearchNama(Pegawai* arr, int* total_pegawai, string target) {
    bool ditemukan = false;
    bersihkanLayar();
    cout << "--- Hasil Pencarian Nama ---\n";
    for (int i = 0; i < *total_pegawai; i++) {
        if ((arr + i)->nama_pegawai == target) {
            cout << "Ditemukan:\nNama: " << (arr + i)->nama_pegawai << " | Umur: " << (arr + i)->umur 
                 << " | Jabatan: " << *((arr + i)->jabatan_ptr) << " | Alamat: " << (arr + i)->lokasi.kota << "\n\n";
            ditemukan = true;
        }
    }
    if (!ditemukan) cout << "[!] Pegawai dengan nama '" << target << "' tidak ditemukan.\n";
}

void binarySearchUmur(Pegawai* arr, int* total_pegawai, int target) {
    quickSortUmur(arr, 0, *total_pegawai - 1);
    perbaikiPointer(arr, *total_pegawai);
    int left = 0, right = *total_pegawai - 1;
    bool ditemukan = false;
    bersihkanLayar();
    cout << "--- Hasil Pencarian Umur ---\n";
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if ((arr + mid)->umur == target) {
            int temp = mid;
            while (temp >= 0 && (arr + temp)->umur == target) {
                cout << "Ditemukan -> Nama: " << (arr + temp)->nama_pegawai << " | Umur: " << (arr + temp)->umur 
                     << " | Jabatan: " << *((arr + temp)->jabatan_ptr) << "\n";
                temp--;
            }
            temp = mid + 1;
            while (temp < *total_pegawai && (arr + temp)->umur == target) {
                cout << "Ditemukan -> Nama: " << (arr + temp)->nama_pegawai << " | Umur: " << (arr + temp)->umur 
                     << " | Jabatan: " << *((arr + temp)->jabatan_ptr) << "\n";
                temp++;
            }
            ditemukan = true; break;
        }
        if ((arr + mid)->umur < target) left = mid + 1;
        else right = mid - 1;
    }
    if (!ditemukan) cout << "[!] Pegawai dengan umur '" << target << "' tidak ditemukan.\n";
}

int main() {
    Akun daftar_akun[100];
    int total_akun = 0;
    Pegawai daftar_pegawai[100];
    int total_pegawai = 0;

    int menu_awal;
    bool aplikasi_berjalan = true;

    while (aplikasi_berjalan) {
        cout << "--- Sistem Manajemen Pegawai Kebab Cendana ---\n";
        cout << "1. Register Akun Baru\n";
        cout << "2. Login\n";
        cout << "3. Keluar Aplikasi\n";
        cout << "Pilihan: ";
        
        try {
            if (!(cin >> menu_awal)) {
                throw runtime_error("Input harus berupa angka!");
            }
            
            switch (menu_awal) {
                case 1: registerAkun(daftar_akun, total_akun); break;
                case 2: 
                    if (loginAkun(daftar_akun, total_akun)) {
                        int menu_crud;
                        bool sesi_login = true;

                        do {
                            cout << "--- Menu Manajemen Pegawai ---\n";
                            cout << "1. Tambah Pegawai\n2. Lihat Daftar Pegawai\n3. Ubah Pegawai\n4. Hapus Pegawai\n";
                            cout << "5. Sorting Nama (Merge)\n6. Sorting Umur (Quick)\n7. Sorting Jabatan (Insertion)\n";
                            cout << "8. Cari Nama (Sequential)\n9. Cari Umur (Binary)\n10. Logout\n";
                            cout << "Pilihan: ";
                            
                            try {
                                if (!(cin >> menu_crud)) {
                                    throw runtime_error("Input menu harus berupa angka!");
                                }

                                switch (menu_crud) {
                                    case 1: tambahPegawai(daftar_pegawai, &total_pegawai); break;
                                    case 2: lihatPegawai(daftar_pegawai, &total_pegawai); break;
                                    case 3: ubahPegawai(daftar_pegawai, &total_pegawai); break;
                                    case 4: hapusPegawai(daftar_pegawai, &total_pegawai); break;
                                    case 5:
                                        if(total_pegawai > 0) {
                                            mergeSortNama(daftar_pegawai, 0, total_pegawai - 1);
                                            perbaikiPointer(daftar_pegawai, total_pegawai);
                                            lihatPegawai(daftar_pegawai, &total_pegawai);
                                            cout << "[+] Data diurutkan berdasarkan Nama (Z-A).\n";
                                        } else cout << "Data masih kosong!\n"; break;
                                    case 6:
                                        if(total_pegawai > 0) {
                                            quickSortUmur(daftar_pegawai, 0, total_pegawai - 1);
                                            perbaikiPointer(daftar_pegawai, total_pegawai);
                                            lihatPegawai(daftar_pegawai, &total_pegawai);
                                            cout << "[+] Data diurutkan berdasarkan Umur (Muda-Tua).\n";
                                        } else cout << "Data masih kosong!\n"; break;
                                    case 7:
                                        if(total_pegawai > 0) {
                                            insertionSortJabatan(daftar_pegawai, total_pegawai);
                                            perbaikiPointer(daftar_pegawai, total_pegawai);
                                            lihatPegawai(daftar_pegawai, &total_pegawai);
                                            cout << "[+] Data diurutkan berdasarkan Jabatan (A-Z).\n";
                                        } else cout << "Data masih kosong!\n"; break;
                                    case 8: {
                                        if (total_pegawai > 0) {
                                            string cari_nama; cout << "Masukkan nama pegawai: ";
                                            cin.ignore(); getline(cin, cari_nama);
                                            sequentialSearchNama(daftar_pegawai, &total_pegawai, cari_nama);
                                        } else cout << "Data kosong!\n"; break;
                                    }
                                    case 9: {
                                        if (total_pegawai > 0) {
                                            int cari_umur; cout << "Masukkan umur pegawai: ";
                                            try {
                                                if (!(cin >> cari_umur)) throw runtime_error("Umur harus angka!");
                                                binarySearchUmur(daftar_pegawai, &total_pegawai, cari_umur);
                                            } catch (const exception& e) {
                                                cout << "[!] Error: " << e.what() << "\n";
                                                cin.clear(); cin.ignore(10000, '\n');
                                            }
                                        } else cout << "Data kosong!\n"; break;
                                    }
                                    case 10: 
                                        bersihkanLayar();
                                        cout << "Logout berhasil.\n"; sesi_login = false; break;
                                    default: cout << "[!] Pilihan tidak valid!\n";
                                }
                            } catch (const exception& e) {
                                cout << "[!] Error: " << e.what() << "\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        } while (sesi_login);
                    }
                    break;
                case 3: prosesKeluar(3); aplikasi_berjalan = false; break;
                default: cout << "[!] Pilihan tidak valid!\n";
            }
        } catch (const exception& e) {
            cout << "[!] Error: " << e.what() << "\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return 0;
}