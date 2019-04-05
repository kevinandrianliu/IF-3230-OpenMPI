# Praktikum 2 IF3230 - OpenMPI Radix Sort

Cara Penggunaan Program
-----
1. Pull/Clone dari repository

2. Menggunakan perintah make untuk mencompile program di src

3. Menjalankan program dengan perintah <code>mpirun -np [P] mpi_radix_sort [N] --bind-to core:overload-allowed</code>, dimana [P] merupakan jumlah thread yang dipakai dan [N] merupakan jumlah elemen array yang dipakai


Pembagian Tugas
-----
- Bella Destiana Junaidi (13516070): Pembuatan laporan dan source code
    -  mengerjakan main program(implementasi MPI pada main)

- Kevin Andrian Liwinata (13516118): Pembuatan source code
    - mengerjakan fungsi-fungsi pembantu(rng, max, sort)
 

Deskripsi Solusi Paralel
-----
Pada radix sort, sebuah data dipecah ke dalam beberapa radix tertentu sebelum digabung menjadi sebuah hasil tertentu. Hal ini dapat dicapai dalam OpenMPI menggunakan fungsi-fungsi seperti MPI_Scatter untuk memecah data menjadi radix-radix, dan MPI_Gather untuk menggabungkan data yang telah dipecah dan diurutkan sebelumnya. Sebelum melakukan pemecahan, diperlukan inisiasi menggunakan MPI_Init, serta menentukan communicator dengan MPI_Comm_rank untuk *assign* suatu proses dengan id tertentu(maksimum adalah jumlah proses-1) dan MPI_Comm_size untuk meng-*assign* proses yang dibutuhkan.


Analisis Solusi
-----
Solusi ini memanfaatkan MPI_Scatter dan MPI_Gather sebagai fungsi OpenMPI utama untuk menjalankan radix sort. MPI_Scatter dilakukan untuk membagi data ke proses-proses yang ada secara berbeda(tidak ada data yang sama dalam satu proses), dan MPI_Gather untuk menyatukan data-data yang terpisah ke dalam suatu proses mengerjakan hal selanjutnya.

Pada proses ini digunakan 4 proses untuk mengoptimasi waktu. Untuk ukuran data yang besar, dapat digunakan lebih dari 4 proses untuk mempercepat kinerja, namun ada beberapa kasus di mana jumlah thread yang terlalu banyak menyebabkan proses menjadi lebih lambat, sehingga harus berhati-hati untuk memilih jumlah proses yang akan dipakai.

Pengukuran Kinerja
-----
Program ini dapat mencapai waktu-waktu sebagai berikut.
- N = 5000: 0.379 ms, 0.479 ms, 0.416 ms
- N = 50000: 3.252 ms, 3.327 ms, 3.323 ms
- N = 100000: 7.410 ms, 7.430 ms, 7.409 ms
- N = 200000: 14.671 ms, 14.773 ms, 14.725 ms 
- N = 400000: 29.979 ms, 29.988 ms, 30.475 ms

Dibandingkan dengan radix sort serial yang dapat mencapai waktu-waktu berikut:
- N = 5000: 1.949 ms, 2.088 ms, 1.272 ms
- N = 50000: 13.318 ms, 21.635 ms, 13.779 ms
- N = 100000: 36.934 ms, 27.078 ms, 27.339 ms
- N = 200000: 55.188 ms, 60.575 ms, 56.118 ms
- N = 400000: 169.037 ms, 112.246 ms, 111.766 ms

Hasil pengujian didapatkan dalam pengujian di server SSH 10.5.32.27. 

Analisis Kinerja
-----
Dari hasil yang didapatkan, dapat disimpulkan bahwa proses secara paralel menghasilkan waktu yang jauh lebih cepat daripada secara serial. Hal ini disebabkan oleh pemecahan proses utama menjadi berbagai subproses yang berjalan secara bersamaan dan kemudian digabungkan, sehingga waktu yang diperhitungkan adalah waktu dari subproses tersebut.
