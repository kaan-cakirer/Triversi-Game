#include <stdio.h>

int main(void) {
    
    int N;
    char tahta[23][23];
    int i, j, x = 0, y = 0, k;
    int oyuncu = 1, devam = 1;
    char renk[3] = {'K', 'S', 'M'};
    int puan[3] = {0, 0, 0};
    int dxdy[8][2] = {
        {-1, 0}, {0, -1}, {1, 0}, {0, 1},
        {1, 1}, {-1, 1}, {1, -1}, {-1, -1}
    };
    

    printf("Tahta Boyutu (maksimum limit 23) = ");
    scanf("%d", &N);

    if (N < 1 || N > 23) {
        printf("Geçersiz Tahta Boyutu!!\nBoyut 1 İle 23 Arasında Olmalı!!\n");
        return 0;
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            tahta[i][j] = '.';
        }
    }

    printf("\nBaşlangıç tahtası:\n\n  ");
    for (i = 1; i <= N; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (i = 0; i < N; i++) {
        printf("%d ", i + 1);
        for (j = 0; j < N; j++) {
            printf("%c ", tahta[i][j]);
        }
        printf("\n");
    }

    int ilk_hamle_yapildi = 0;

    while (devam == 1) {

        int hamle_dogru = 0;
        while (hamle_dogru == 0) {
            printf("Oyuncu %d (%c), taş koymak istediğiniz koordinatı giriniz (Satır Sütun): ", oyuncu, renk[oyuncu - 1]);
            scanf("%d %d", &x, &y);

            if (x >= 1 && x <= N && y >= 1 && y <= N && tahta[x - 1][y - 1] == '.') {
                if (!ilk_hamle_yapildi) {
                    int merkez_icerisinde = 0;

                    if (N % 2 == 0) {
                        if ((x - 1 == N / 2 && y - 1 == N / 2) ||
                            (x - 1 == N / 2 - 1 && y - 1 == N / 2) ||
                            (x - 1 == N / 2 && y - 1 == N / 2 - 1) ||
                            (x - 1 == N / 2 - 1 && y - 1 == N / 2 - 1)) {
                            merkez_icerisinde = 1;
                        }
                    } else {
                        if (x - 1 == N / 2 && y - 1 == N / 2) {
                            merkez_icerisinde = 1;
                        }
                    }

                    if (merkez_icerisinde) {
                        hamle_dogru = 1;
                        ilk_hamle_yapildi = 1;
                    } else {
                        printf("İlk hamlede taşı tahtanın ortasına koymalısınız!\n");
                    }
                } else {
                    int komsu_var = 0;
                    for (k = 0; k < 8; k++) {
                        int x_komsu = x - 1 + dxdy[k][0];
                        int y_komsu = y - 1 + dxdy[k][1];
                        if (x_komsu >= 0 && x_komsu < N && y_komsu >= 0 && y_komsu < N) {
                            if (tahta[x_komsu][y_komsu] != '.') {
                                komsu_var = 1;
                            }
                        }
                    }

                    if (komsu_var) {
                        hamle_dogru = 1;
                    } else {
                        printf("Taşınızı daha önce oynanmış taşların hemen yanına koymalısınız!\n");
                    }
                }
            } else {
                printf("Geçersiz koordinat veya dolu yer! Lütfen tekrar deneyin.\n");
            }
        }

        // Taşı koy ve ilk hali yazdır
        tahta[x - 1][y - 1] = renk[oyuncu - 1];
        printf("\nGÜNCEL TAHTA\n\n");
        for (i = 0; i <= N; i++) {
            if (i==0) {
                printf("  ");
            }
            else printf("%d ", i);
        }
        printf("\n");

        for (i = 0; i < N; i++) {
            printf("%d ", i + 1);
            for (j = 0; j < N; j++) {
                printf("%c ", tahta[i][j]);
            }
            printf("\n");
        }


        // Renk değiştirme işlemi
        for (k = 0; k < 8; k++) {
            int xyeni = x - 1 + dxdy[k][0];
            int yyeni = y - 1 + dxdy[k][1];
            int tasRakip = 0;

            while (xyeni >= 0 && xyeni < N && yyeni >= 0 && yyeni < N &&
                   tahta[xyeni][yyeni] != '.' && tahta[xyeni][yyeni] != renk[oyuncu - 1]) {
                xyeni += dxdy[k][0];
                yyeni += dxdy[k][1];
                tasRakip = 1;
            }

            if (tasRakip == 1 && xyeni >= 0 && xyeni < N && yyeni >= 0 && yyeni < N &&
                tahta[xyeni][yyeni] == renk[oyuncu - 1]) {
                xyeni -= dxdy[k][0];
                yyeni -= dxdy[k][1];
                while (xyeni != x - 1 || yyeni != y - 1) {
                    tahta[xyeni][yyeni] = renk[oyuncu - 1];
                    xyeni -= dxdy[k][0];
                    yyeni -= dxdy[k][1];
                    
                    // Değişimden sonraki tahtayı yazdır
                    printf("\nGÜNCEL TAHTA\n\n");
                    for (i = 0; i <= N; i++) {
                        if (i==0) {
                            printf("  ");
                        }
                        else printf("%d ", i);
                    }
                    printf("\n");

                    for (i = 0; i < N; i++) {
                        printf("%d ", i + 1);
                        for (j = 0; j < N; j++) {
                            printf("%c ", tahta[i][j]);
                        }
                        printf("\n");
                    }
                }
            }
        }

       

        // Oyuncu sırasını değiştir
        oyuncu = (oyuncu % 3) + 1;

        // Devam kontrolü
        devam = 0;
        for (i = 0; i < N && !devam; i++) {
            for (j = 0; j < N && !devam; j++) {
                if (tahta[i][j] == '.') {
                    devam = 1;
                }
            }
        }
    }


    printf("\nOyun bitti! Tüm taşlar yerleştirildi.\n");

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (tahta[i][j] == 'K') {
                puan[0]++;
            } else if (tahta[i][j] == 'S') {
                puan[1]++;
            } else if (tahta[i][j] == 'M') {
                puan[2]++;
            }
        }
    }

    printf("\nPuanlar!!\n");
    printf("Kırmızı (K): %d\n", puan[0]);
    printf("Sarı (S): %d\n", puan[1]);
    printf("Mavi (M): %d\n", puan[2]);

    if (puan[0] > puan[1] && puan[0] > puan[2]) {
        printf("Kazanan: Oyuncu 1 (Kırmızı)!\n");
    } else if (puan[1] > puan[0] && puan[1] > puan[2]) {
        printf("Kazanan: Oyuncu 2 (Sarı)!\n");
    } else if (puan[2] > puan[0] && puan[2] > puan[1]) {
        printf("Kazanan: Oyuncu 3 (Mavi)!\n");
    } else {
        printf("Oyun berabere bitti!\n");
    }

    return 0;
}
