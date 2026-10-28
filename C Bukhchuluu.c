#include <stdio.h>

int main(void) {

    const double MIN_KM = 25.0;
    const double MAX_KM = 100.0;
    const int STEP = 5;

    double zai = 0, hurd = 0, pace = 0;
    int h = 0, m = 0, s = 0, niit = 0;
    int p = 0, pm = 0, ps = 0;
    int km = 0, t = 0, th = 0, tm = 0, ts = 0;
    int k = 0, rh = 0, rm = 0, rs = 0, rt = 0;
    int t1 = 0, t2 = 0, t3 = 0;
    int b1 = 1, b2 = 2, b3 = 3;
    int tmp = 0;
    int bad = 0;

    do {
        printf("Зайг км-ээр оруулна  (%.0f-%.0f): ", MIN_KM, MAX_KM);
        scanf("%lf", &zai);
        bad = (zai < MIN_KM || zai > MAX_KM);
        if (bad) {
            printf("Алдаа: зай %.0f %.0f км хооронд байх ёстой.\n", MIN_KM, MAX_KM);
        }
    } while (bad);

    do {
        printf("Дуусгасан хугацаа (цаг минут секунд): ");
        scanf("%d %d %d", &h, &m, &s);
        bad = (h < 0 || m < 0 || m > 59 || s < 0 || s > 59 ||
               (h == 0 && m == 0 && s == 0));
        if (bad) {
            printf("Алдаа: цаг >= 0, минут 0-59, секунд 0-59, нийт > 0.\n");
        }
    } while (bad);

    niit = h * 3600 + m * 60 + s;
    hurd = zai / ((double)niit / 3600);
    pace = (double)niit / zai;
    p = (int)(pace + 0.5);
    pm = p / 60;
    ps = p % 60;

    printf("\nДyндaж хурд: %.2f км/ц\n", hurd);
    printf("1 км-ийн хугацаа: %d:%02d\n", pm, ps);

    if (hurd >= 15) {
        printf("Түвшин: Элит\n");
    } else if (hurd >= 10) {
        printf("Түвшин: Дундаж\n");
    } else {
        printf("Түвшин: Эхлэн гүйгч\n");
    }

    printf("\nkм      Хугацаа    Хувь%%\n");
    for (km = STEP; km <= zai; km += STEP) {
        t = (int)(pace * km + 0.5);
        th = t / 3600;
        tm = t / 60 % 60;
        ts = t % 60;
        printf("%-6d %2d:%02d:%02d %8.2f\n", km, th, tm, ts, km * 100.0 / zai);
    }
    printf("%-6s %2d:%02d:%02d %8.2f\n", "Finish", h, m, s, 100.0);

    printf("\n3 гүйгчийн мэдээлэл:\n");
    for (k = 1; k <= 3; k++) {
        do {
            printf("%d-p гүйгчийн хугацаа (цаг минут секунд): ", k);
            scanf("%d %d %d", &rh, &rm, &rs);
            bad = (rh < 0 || rm < 0 || rm > 59 || rs < 0 || rs > 59 ||
                   (rh == 0 && rm == 0 && rs == 0));
            if (bad) {
                printf("Алдаа: цаг >= 0, минут 0-59, секунд 0-59, нийт > 0.\n");
            }
        } while (bad);

        rt = rh * 3600 + rm * 60 + rs;
        if (k == 1) {
            t1 = rt;
        } else if (k == 2) {
            t2 = rt;
        } else {
            t3 = rt;
        }
    }

    if (t1 > t2) {
        tmp = t1; t1 = t2; t2 = tmp;
        tmp = b1; b1 = b2; b2 = tmp;
    }
    if (t2 > t3) {
        tmp = t2; t2 = t3; t3 = tmp;
        tmp = b2; b2 = b3; b3 = tmp;
    }
    if (t1 > t2) {
        tmp = t1; t1 = t2; t2 = tmp;
        tmp = b1; b1 = b2; b2 = tmp;
    }

    printf("\nЭpэммэ (хамгийн хурдан нь эхэнд):\n");
    printf("1-p байр: %d-p гүйгч  %d:%02d:%02d\n", b1, t1 / 3600, t1 / 60 % 60, t1 % 60);
    printf("2-p байр: %d-p гүйгч  %d:%02d:%02d\n", b2, t2 / 3600, t2 / 60 % 60, t2 % 60);
    printf("3-p байр: %d-p гүйгч  %d:%02d:%02d\n", b3, t3 / 3600, t3 / 60 % 60, t3 % 60);

    return 0;
}
