#include <iostream>
#include <string>

using namespace std;

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
    int umur; 
    string jabatan;
    Alamat lokasi; 
    string *jabatan_ptr; 
};

void prosesKeluar(int detik) {
    if (detik == 0) {
        cout << "Terima kasih telah menggunakan aplikasi ini!\n";
        return;
    }
    cout << "Aplikasi akan tertutup dalam " << detik << "...\n";
    prosesKeluar(detik - 1);
}

// fungsi helper untuk merapikan pointer setelah data di swap
void perbaikiPointer(Pegawai daftar_pegawai[], int n) {
    for (int i = 0; i < n; i++) {
        daftar_pegawai[i].jabatan_ptr = &daftar_pegawai[i].jabatan;
    }
}

// autentikasi
void registerAkun(Akun daftar_akun[], int &total_akun) {
    cout << "\n--- Register ---\n";
    cout << "Masukkan Nama (Tanpa Spasi) : ";
    cin >> daftar_akun[total_akun].nama_pengguna;
    cout << "Masukkan Password           : ";
    cin >> daftar_akun[total_akun].password_pengguna;
    
    total_akun++; 
    cout << "[+] Akun berhasil didaftarkan! Silakan Login.\n";
}

bool loginAkun(Akun daftar_akun[], int total_akun) {
    if (total_akun == 0) {
        cout << "[!] Belum ada akun. Silakan Register dulu.\n";
        return false;
    }

    int sisa_kesempatan = 3;
    string input_nama, input_password;

    cout << "\n--- Login ---\n";
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
        if (sisa_kesempatan > 0) cout << "[!] Nama atau Password salah! Sisa: " << sisa_kesempatan << "\n\n";
    }
    cout << "\n[X] Gagal login 3 kali. Kembali ke menu utama.\n";
    return false; 
}

// crud pegawai
void tambahPegawai(Pegawai daftar_pegawai[], int *total_pegawai) {
    int indeks = *total_pegawai;
    
    cout << "\n--- Tambah Pegawai ---\n";
    cout << "Nama Pegawai : ";
    cin.ignore(); 
    getline(cin, daftar_pegawai[indeks].nama_pegawai);
    
    cout << "Umur         : ";
    cin >> daftar_pegawai[indeks].umur;
    
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
}

void lihatPegawai(Pegawai daftar_pegawai[], int *total_pegawai) {
    int batas = *total_pegawai;
    
    cout << "\n--- Daftar Pegawai Kebab Cendana ---\n";
    if (batas == 0) {
        cout << "Belum ada data pegawai.\n";
    } else {
        cout << "--------------------------------------------------------------------------------------\n";
        cout << "No. | Nama                 | Umur | Jabatan              | Alamat (Kota, Jalan)\n";
        cout << "--------------------------------------------------------------------------------------\n";
        
        for (int i = 0; i < batas; i++) {
            cout << i + 1 << "   | ";
            
            string nama = daftar_pegawai[i].nama_pegawai;
            cout << nama;
            for (int s = nama.length(); s < 20; s++) cout << " ";
            
            cout << " | " << daftar_pegawai[i].umur << "   | ";

            string jabatan = *(daftar_pegawai[i].jabatan_ptr); 
            cout << jabatan;
            for (int s = jabatan.length(); s < 20; s++) cout << " ";
            
            cout << " | " << daftar_pegawai[i].lokasi.kota << ", " 
                 << daftar_pegawai[i].lokasi.jalan << "\n";
        }
        cout << "--------------------------------------------------------------------------------------\n";
    }
}

void ubahPegawai(Pegawai daftar_pegawai[], int *total_pegawai) {
    int batas = *total_pegawai;
    cout << "\n--- Ubah Data Pegawai ---\n";
    if (batas == 0) {
        cout << "Belum ada pegawai untuk diubah.\n";
    } else {
        int index_pegawai;
        cout << "Masukkan nomor pegawai yang akan diubah: ";
        cin >> index_pegawai;

        if (index_pegawai > 0 && index_pegawai <= batas) {
            int idx = index_pegawai - 1;
            cout << "Masukkan nama baru   : ";
            cin.ignore();
            getline(cin, daftar_pegawai[idx].nama_pegawai);
            
            cout << "Masukkan umur baru   : ";
            cin >> daftar_pegawai[idx].umur;
            
            cout << "Masukkan jabatan baru: ";
            cin.ignore();
            getline(cin, daftar_pegawai[idx].jabatan);
            
            daftar_pegawai[idx].jabatan_ptr = &daftar_pegawai[idx].jabatan;
            
            cout << "Masukkan kota baru   : ";
            getline(cin, daftar_pegawai[idx].lokasi.kota);
            
            cout << "Masukkan jalan baru  : ";
            getline(cin, daftar_pegawai[idx].lokasi.jalan);
            
            cout << "[+] Data berhasil diubah.\n";
        } else {
            cout << "[!] Nomor pegawai tidak valid.\n";
        }
    }
}

void hapusPegawai(Pegawai daftar_pegawai[], int *total_pegawai) {
    int batas = *total_pegawai;
    cout << "\n--- Hapus Data Pegawai ---\n";
    if (batas == 0) {
        cout << "Belum ada pegawai untuk dihapus.\n";
    } else {
        int index_pegawai;
        cout << "Masukkan nomor pegawai yang akan dihapus: ";
        cin >> index_pegawai;

        if (index_pegawai > 0 && index_pegawai <= batas) {
            for (int i = index_pegawai - 1; i < batas - 1; i++) {
                daftar_pegawai[i] = daftar_pegawai[i + 1];
            }
            (*total_pegawai)--; 
            perbaikiPointer(daftar_pegawai, *total_pegawai);
            cout << "[+] Pegawai berhasil dihapus.\n";
        } else {
            cout << "[!] Nomor pegawai tidak valid.\n";
        }
    }
}

// merge sort descending berdasarkan nama
void mergeNamaDesc(Pegawai* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    Pegawai* L = new Pegawai[n1];
    Pegawai* R = new Pegawai[n2];

    for (int i = 0; i < n1; i++) *(L + i) = *(arr + left + i);
    for (int j = 0; j < n2; j++) *(R + j) = *(arr + mid + 1 + j);

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if ((L + i)->nama_pegawai >= (R + j)->nama_pegawai) {
            *(arr + k) = *(L + i);
            i++;
        } else {
            *(arr + k) = *(R + j);
            j++;
        }
        k++;
    }
    while (i < n1) { *(arr + k) = *(L + i); i++; k++; }
    while (j < n2) { *(arr + k) = *(R + j); j++; k++; }
    
    delete[] L;
    delete[] R;
}

void mergeSortNama(Pegawai* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortNama(arr, left, mid);
        mergeSortNama(arr, mid + 1, right);
        mergeNamaDesc(arr, left, mid, right);
    }
}

// quicksort ascending berdasarkan umur 
void swapPegawai(Pegawai* a, Pegawai* b) {
    Pegawai temp = *a;
    *a = *b;
    *b = temp;
}

int partitionUmur(Pegawai* arr, int low, int high) {
    int pivot = (arr + high)->umur;
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        if ((arr + j)->umur < pivot) {
            i++;
            swapPegawai((arr + i), (arr + j));
        }
    }
    swapPegawai((arr + i + 1), (arr + high));
    return (i + 1);
}

void quickSortUmur(Pegawai* arr, int low, int high) {
    if (low < high) {
        int pi = partitionUmur(arr, low, high);
        quickSortUmur(arr, low, pi - 1);
        quickSortUmur(arr, pi + 1, high);
    }
}

// insertion sort ascending berdasarkan jabatan
void insertionSortJabatan(Pegawai* arr, int n) {
    for (int i = 1; i < n; i++) {
        Pegawai key = *(arr + i);
        int j = i - 1;
        
        while (j >= 0 && (arr + j)->jabatan > key.jabatan) {
            *(arr + j + 1) = *(arr + j);
            j = j - 1;
        }
        *(arr + j + 1) = key;
    }
}

// sequential search untuk nama pegawai 
void sequentialSearchNama(Pegawai* arr, int* total_pegawai, string target) {
    bool ditemukan = false;
    cout << "\n--- Hasil Pencarian Nama ---\n";
    for (int i = 0; i < *total_pegawai; i++) {
        if ((arr + i)->nama_pegawai == target) {
            cout << "Ditemukan pada indeks " << i << ":\n";
            cout << "Nama    : " << (arr + i)->nama_pegawai << "\n";
            cout << "Umur    : " << (arr + i)->umur << "\n";
            cout << "Jabatan : " << *((arr + i)->jabatan_ptr) << "\n";
            cout << "Alamat  : " << (arr + i)->lokasi.kota << "\n\n";
            ditemukan = true;
        }
    }
    if (!ditemukan) {
        cout << "[!] Pegawai dengan nama '" << target << "' tidak ditemukan.\n";
    }
}

// binary search untuk umur pegawai
void binarySearchUmur(Pegawai* arr, int* total_pegawai, int target) {
    // binary search mewajibkan data terurut, data diurutkan ascending terlebih dahulu
    quickSortUmur(arr, 0, *total_pegawai - 1);
    perbaikiPointer(arr, *total_pegawai);

    int left = 0;
    int right = *total_pegawai - 1;
    bool ditemukan = false;

    cout << "\n--- Hasil Pencarian Umur ---\n";
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if ((arr + mid)->umur == target) {
            int temp = mid;
            // periksa elemen sebelumnya jika ada umur yang sama
            while (temp >= 0 && (arr + temp)->umur == target) {
                cout << "Ditemukan:\n";
                cout << "Nama    : " << (arr + temp)->nama_pegawai << "\n";
                cout << "Umur    : " << (arr + temp)->umur << "\n";
                cout << "Jabatan : " << *((arr + temp)->jabatan_ptr) << "\n\n";
                temp--;
            }
            temp = mid + 1;
            // periksa elemen setelahnya jika ada umur yang sama
            while (temp < *total_pegawai && (arr + temp)->umur == target) {
                cout << "Ditemukan:\n";
                cout << "Nama    : " << (arr + temp)->nama_pegawai << "\n";
                cout << "Umur    : " << (arr + temp)->umur << "\n";
                cout << "Jabatan : " << *((arr + temp)->jabatan_ptr) << "\n\n";
                temp++;
            }
            ditemukan = true;
            break;
        }

        if ((arr + mid)->umur < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (!ditemukan) {
        cout << "[!] Pegawai dengan umur '" << target << "' tidak ditemukan.\n";
    }
}

int main() {
    Akun daftar_akun[100];
    int total_akun = 0;
    Pegawai daftar_pegawai[100];
    int total_pegawai = 0;

    int menu_awal;
    bool aplikasi_berjalan = true;

    while (aplikasi_berjalan) {
        cout << "\n=========================================\n";
        cout << "   Sistem Manajemen Pegawai Kebab Cendana  \n";
        cout << "===========================================\n";
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
                        cout << "\n=========================================\n";
                        cout << "          Menu Manajemen Pegawai        \n";
                        cout << "=========================================\n";
                        cout << "1. Tambah Pegawai (Create)\n";
                        cout << "2. Lihat Daftar Pegawai (Read)\n";
                        cout << "3. Ubah Pegawai (Update)\n";
                        cout << "4. Hapus Pegawai (Delete)\n";
                        cout << "5. Sorting Nama Pegawai (Z-A) - Merge\n";
                        cout << "6. Sorting Umur Pegawai (Kecil-Besar) - Quick\n";
                        cout << "7. Sorting Jabatan (A-Z) - Insertion\n";
                        cout << "8. Cari Nama Pegawai (Sequential Search)\n";
                        cout << "9. Cari Umur Pegawai (Binary Search)\n";
                        cout << "10. Logout\n";
                        cout << "Pilihan: ";
                        cin >> menu_crud;

                        switch (menu_crud) {
                            case 1: 
                                tambahPegawai(daftar_pegawai, &total_pegawai); 
                                break;
                            case 2: 
                                lihatPegawai(daftar_pegawai, &total_pegawai); 
                                break;
                            case 3: 
                                ubahPegawai(daftar_pegawai, &total_pegawai); 
                                break;
                            case 4: 
                                hapusPegawai(daftar_pegawai, &total_pegawai); 
                                break;
                            case 5:
                                if(total_pegawai > 0) {
                                    mergeSortNama(daftar_pegawai, 0, total_pegawai - 1);
                                    perbaikiPointer(daftar_pegawai, total_pegawai);
                                    cout << "\n[+] Data berhasil diurutkan berdasarkan Nama (Z-A).\n";
                                    lihatPegawai(daftar_pegawai, &total_pegawai);
                                } else cout << "Data masih kosong!\n";
                                break;
                            case 6:
                                if(total_pegawai > 0) {
                                    quickSortUmur(daftar_pegawai, 0, total_pegawai - 1);
                                    perbaikiPointer(daftar_pegawai, total_pegawai);
                                    cout << "\n[+] Data berhasil diurutkan berdasarkan Umur (Muda-Tua).\n";
                                    lihatPegawai(daftar_pegawai, &total_pegawai);
                                } else cout << "Data masih kosong!\n";
                                break;
                            case 7:
                                if(total_pegawai > 0) {
                                    insertionSortJabatan(daftar_pegawai, total_pegawai);
                                    perbaikiPointer(daftar_pegawai, total_pegawai);
                                    cout << "\n[+] Data berhasil diurutkan berdasarkan Jabatan (A-Z).\n";
                                    lihatPegawai(daftar_pegawai, &total_pegawai);
                                } else cout << "Data masih kosong!\n";
                                break;
                            case 8: {
                                if (total_pegawai > 0) {
                                    string cari_nama;
                                    cout << "Masukkan nama pegawai yang dicari: ";
                                    cin.ignore();
                                    getline(cin, cari_nama);
                                    sequentialSearchNama(daftar_pegawai, &total_pegawai, cari_nama);
                                } else cout << "Data masih kosong!\n";
                                break;
                            }
                            case 9: {
                                if (total_pegawai > 0) {
                                    int cari_umur;
                                    cout << "Masukkan umur pegawai yang dicari: ";
                                    cin >> cari_umur;
                                    binarySearchUmur(daftar_pegawai, &total_pegawai, cari_umur);
                                } else cout << "Data masih kosong!\n";
                                break;
                            }
                            case 10: 
                                cout << "Logout berhasil. Kembali ke menu autentikasi...\n";
                                sesi_login = false; 
                                break;
                            default: 
                                cout << "[!] Pilihan tidak valid!\n";
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