# Praktikum 1 IF3230 - OpenMPI Radix Sort

Cara Penggunaan Program
-----
1. Pull/Clone dari repository

2. Menggunakan perintah make untuk mencompile program di src

3. Menjalankan program dengan perintah <code>mpirun -np [P] --hostfile mpi_hostfile mpi_radix_sort [N] --bind-to core:overload-allowed</code>, dimana [P] merupakan jumlah thread yang dipakai dan [N] merupakan jumlah elemen array yang dipakai


Pembagian Tugas
-----
- Bella Destiana Junaidi (13516070): 

- Kevin Andrian Liwinata (13516118): 
 

Deskripsi Solusi Paralel
-----
Pada radix sort, sebuah data dipecah ke dalam beberapa radix tertentu sebelum digabung.


Analisis Solusi
-----



Pengukuran Kinerja
-----
Program ini dapat mencapai waktu-waktu sebagai berikut.
- N = 5000: 
- N = 50000: 
- N = 100000: 
- N = 200000: 
- N = 400000: 

Dibandingkan dengan radix sort serial yang dapat mencapai waktu-waktu berikut:
- N = 5000: 1.949 ms, 2.088 ms, 1.272 ms
- N = 50000: 13.318 ms, 21.635 ms, 13.779 ms
- N = 100000: 36.934 ms, 27.078 ms, 27.339 ms
- N = 200000: 55.188 ms, 60.575 ms, 56.118 ms
- N = 400000: 169.037 ms, 112.246 ms, 111.766 ms
 

Analisis Kinerja
-----
