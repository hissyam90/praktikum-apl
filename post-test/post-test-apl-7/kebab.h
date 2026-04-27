#ifndef KEBAB_H
#define KEBAB_H

#include <string>

using namespace std;

// database
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

// fungsi untuk memperbaiki pointer jabatan_ptr
void perbaikiPointer(Pegawai daftar_pegawai[], int n) {
    for (int i = 0; i < n; i++) {
        daftar_pegawai[i].jabatan_ptr = &daftar_pegawai[i].jabatan;
    }
}

#endif