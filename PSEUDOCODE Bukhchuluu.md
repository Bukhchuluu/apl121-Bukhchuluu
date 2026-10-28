# Pseudocode: марафоны хурд, pace, 5 км-ийн хүснэгт, 3 гүйгчийн эрэмбэ

Тэмдэглэгээ: `←` онооно, `mod` үлдэгдэл, `/` нь тоон хуваалт. Бүх алхам нь төгсгөлтэй (finite).

## Дэд алгоритмууд

```
SUBALGORITHM PrintTime(sec)
  ss ← sec mod 60
  mm ← (sec mod 3600 - ss) / 60
  hh ← (sec - sec mod 3600) / 3600
  OUTPUT hh, ":"
  IF mm < 10 THEN OUTPUT "0" END IF
  OUTPUT mm, ":"
  IF ss < 10 THEN OUTPUT "0" END IF
  OUTPUT ss
END

SUBALGORITHM PrintFixed2(v)
  fp ← v mod 100
  ip ← (v - fp) / 100
  OUTPUT ip, "."
  IF fp < 10 THEN OUTPUT "0" END IF
  OUTPUT fp
END
```

## Үндсэн алгоритм

```
ALGORITHM MarathonPace
  t1 ← 0, t2 ← 0, t3 ← 0
  b1 ← 1, b2 ← 2, b3 ← 3

  REPEAT
    INPUT zai
    IF zai < 25 OR zai > 100 THEN
      OUTPUT "Алдаа: зай 25-аас 100 км хооронд байх ёстой."
    END IF
  UNTIL zai >= 25 AND zai <= 100

  REPEAT
    INPUT h, m, s
    IF h < 0 OR m < 0 OR m > 59 OR s < 0 OR s > 59 OR (h = 0 AND m = 0 AND s = 0) THEN
      OUTPUT "Алдаа: цаг >= 0, минут 0-59, секунд 0-59, нийт > 0."
    END IF
  UNTIL time is valid

  niit ← h*3600 + m*60 + s
  hurd ← zai / (niit / 3600)
  pace ← niit / zai
  p    ← Round(pace)
  pm   ← p / 60
  ps   ← p mod 60

  OUTPUT "Дундаж хурд:", hurd, "км/ц"
  OUTPUT "1 км-ийн хугацаа:", pm, ":", ps

  IF hurd >= 15 THEN
    OUTPUT "Түвшин: Элит"
  ELSE IF hurd >= 10 THEN
    OUTPUT "Түвшин: Дундаж"
  ELSE
    OUTPUT "Түвшин: Эхлэн гүйгч"
  END IF

  OUTPUT "Км", "Хугацаа", "Хувь%"
  FOR km ← 5 TO zai STEP 5
    t   ← Round(pace * km)
    pct ← km * 100 / zai
    OUTPUT km
    CALL PrintTime(t)
    OUTPUT pct
  END FOR
  OUTPUT "Finish"
  CALL PrintTime(niit)
  OUTPUT 100.00

  OUTPUT "3 гүйгчийн мэдээлэл:"
  FOR k ← 1 TO 3
    REPEAT
      INPUT rh, rm, rs
      IF time is invalid THEN OUTPUT "Алдаа: ..." END IF
    UNTIL time is valid
    rt ← rh*3600 + rm*60 + rs
    IF k = 1 THEN t1 ← rt
    ELSE IF k = 2 THEN t2 ← rt
    ELSE t3 ← rt
    END IF
  END FOR

  IF t1 > t2 THEN swap t1, t2 AND swap b1, b2 (via tmp) END IF
  IF t2 > t3 THEN swap t2, t3 AND swap b2, b3 (via tmp) END IF
  IF t1 > t2 THEN swap t1, t2 AND swap b1, b2 (via tmp) END IF

  OUTPUT "Эрэмбэ (хамгийн хурдан нь эхэнд):"
  OUTPUT "1-р байр:", b1, "-р гүйгч";  CALL PrintTime(t1)
  OUTPUT "2-р байр:", b2, "-р гүйгч";  CALL PrintTime(t2)
  OUTPUT "3-р байр:", b3, "-р гүйгч";  CALL PrintTime(t3)
END
```

## Trace table: зай 25 км, хугацаа 2:05:00

| Алхам | zai | h m s | niit | hurd | pace | p | pm:ps |
|---|---|---|---|---|---|---|---|
| INPUT zai | 25 | | | | | | |
| INPUT h, m, s | 25 | 2 5 0 | | | | | |
| niit | 25 | 2 5 0 | 7500 | | | | |
| hurd | 25 | 2 5 0 | 7500 | 12.0 | | | |
| pace | 25 | 2 5 0 | 7500 | 12.0 | 300 | | |
| p, pm, ps | 25 | 2 5 0 | 7500 | 12.0 | 300 | 300 | 5:00 |

## Trace table: 5 км-ийн давталт (pace = 300)

| km | km <= zai ? | t | PrintTime(t) | pct |
|---|---|---|---|---|
| 5 | Yes | 1500 | 0:25:00 | 20.00 |
| 10 | Yes | 3000 | 0:50:00 | 40.00 |
| 15 | Yes | 4500 | 1:15:00 | 60.00 |
| 20 | Yes | 6000 | 1:40:00 | 80.00 |
| 25 | Yes | 7500 | 2:05:00 | 100.00 |
| 30 | No | | | |

5 мөр гарч, km = 30 үед давталт дуусна. Дараа нь Finish мөр хэвлэгдэнэ.

## Trace table: 3 гүйгчийн эрэмбэ

Гүйгч 1 = 3:10:05 (11405 с), гүйгч 2 = 2:59:59 (10799 с), гүйгч 3 = 3:30:00 (12600 с).

| Алхам | t1 | t2 | t3 | b1 | b2 | b3 |
|---|---|---|---|---|---|---|
| унших | 11405 | 10799 | 12600 | 1 | 2 | 3 |
| t1 > t2 ? Yes, swap | 10799 | 11405 | 12600 | 2 | 1 | 3 |
| t2 > t3 ? No | 10799 | 11405 | 12600 | 2 | 1 | 3 |
| t1 > t2 ? No | 10799 | 11405 | 12600 | 2 | 1 | 3 |

Үр дүн: 1-р байр 2-р гүйгч, 2-р байр 1-р гүйгч, 3-р байр 3-р гүйгч.
