#include <iostream>
#include <string>

using namespace std;

int main() {
    string nama_pengguna;
    string password_pengguna;
    int sisa_kesempatan = 3;
    bool is_login_berhasil = false;

    cout << "========================================\n";
    cout << "          SISTEM KONVERSI WAKTU         \n";
    cout << "========================================\n";

    while (sisa_kesempatan > 0) {
        cout << "\n------------------------------------------\n";
        cout << "               FORM LOGIN                 \n";
        cout << "------------------------------------------\n";
        cout << "Masukkan Nama     : ";
        cin >> nama_pengguna; 
        cout << "Masukkan Password : ";
        cin >> password_pengguna;

        // validasi login
        if (nama_pengguna == "antung" && password_pengguna == "092") {
            is_login_berhasil = true;
            cout << "\n[+] Login Berhasil! Selamat datang, antung.\n";
            break; 
        } else {
            sisa_kesempatan--; 
            if (sisa_kesempatan > 0) {
                cout << "[!] Nama atau Password salah! Sisa percobaan: " << sisa_kesempatan << "\n";
            }
        }
    }

    // gagal 3 kali end program
    if (!is_login_berhasil) {
        cout << "\n[X] Akses Ditolak. Anda salah memasukkan data 3 kali. Program berhenti.\n";
        return 0; 
    }

    int pilihan_menu;
    
    // long long int biar bisa nampung banyak angka tanpa error :)
    long long int nilai_waktu;
    long long int sisa_waktu, hasil_jam, hasil_menit, hasil_detik;

    do {
        cout << "\n========================================\n";
        cout << "             MENU KONVERSI              \n";
        cout << "========================================\n";
        cout << "1. Jam   -> Menit dan Detik\n";
        cout << "2. Menit -> Jam dan Detik\n";
        cout << "3. Detik -> Jam dan Menit\n";
        cout << "4. Keluar\n";
        cout << "========================================\n";
        cout << "Masukkan pilihan menu (1-4): ";
        cin >> pilihan_menu;

        if (pilihan_menu == 1) {
            cout << "\n-- Konversi Jam --\n";
            cout << "Masukkan nilai waktu : ";
            cin >> nilai_waktu;

            cout << "Hasil Konversi: " << nilai_waktu << " Jam = " 
                 << nilai_waktu * 60 << " Menit ATAU " 
                 << nilai_waktu * 3600 << " Detik.\n";
        } 
        else if (pilihan_menu == 2) {
            cout << "\n-- Konversi Menit --\n";
            cout << "Masukkan nilai waktu : ";
            cin >> nilai_waktu;

            hasil_jam = nilai_waktu / 60;
            hasil_menit = nilai_waktu % 60; 
            hasil_detik = nilai_waktu * 60;
            
            cout << "Hasil Total   : " << hasil_detik << " Detik.\n";
            cout << "Hasil Lengkap : " << hasil_jam << " Jam, " << hasil_menit << " Menit.\n";
        } 
        else if (pilihan_menu == 3) {
            cout << "\n-- Konversi Detik --\n";
            cout << "Masukkan nilai waktu : ";
            cin >> nilai_waktu;

            hasil_jam = nilai_waktu / 3600;
            sisa_waktu = nilai_waktu % 3600;
            hasil_menit = sisa_waktu / 60;
            hasil_detik = sisa_waktu % 60;
            
            cout << "Hasil Lengkap : " << hasil_jam << " Jam, " << hasil_menit << " Menit, dan " << hasil_detik << " Detik.\n";
        } 
        else if (pilihan_menu == 4) {
            cout << "\nTerima kasih telah menggunakan program ini!\n";
        } 
        else {
            cout << "\n[!] Pilihan tidak valid. Silakan pilih angka 1-4. \n";
        }

    } while (pilihan_menu != 4);

    return 0;
}