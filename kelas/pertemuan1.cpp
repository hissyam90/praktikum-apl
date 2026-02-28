#include <iostream>
using namespace std;
int main() {
int z = 1;
cout << "Sebelum increment " << z << endl;
cout << "Increment di depan " << ++z << ", sudah bertambah" <<
endl;
cout << "Increment di belakang " << z++ << ", belum bertambah" <<
endl;
cout << "Hasil akhir " << z << endl;
return 0;
}