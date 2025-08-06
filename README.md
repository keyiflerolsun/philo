# 🍽️ Philosophers (philo)

## 📋 Proje Açıklaması

`philo`, klasik **"Dining Philosophers"** (Yemek Yiyen Filozoflar) problemini C dilinde ve École 42 kapsamında simüle eden gelişmiş bir uygulamadır. Bu proje, **eşzamanlılık (concurrency)**, **senkronizasyon** ve **paralel programlama** konularını derinlemesine öğrenmeyi amaçlar.

### 🎯 Ana Özellikler

- **🧵 Thread Management**: Her filozof ayrı bir `pthread` ile çalışır
- **🔒 Mutex Synchronization**: `pthread_mutex_t` ile çatal paylaşımı ve veri tutarlılığı
- **⚡ Deadlock Prevention**: Akıllı fork sıralama algoritması (`left_fork < right_fork`)
- **📊 Real-time Monitoring**: Hayatta kalma kontrolü için ayrı thread
- **🛡️ Data Race Protection**: Kritik bölgelerin mutex ile korunması
- **⏱️ Precision Timing**: Mikrosaniye hassasiyetinde zaman yönetimi

## 🚀 Kurulum ve Derleme

### Gereksinimler
- **GCC/Clang** derleyici
- **pthread** kütüphanesi
- **GNU Make**
- **POSIX** uyumlu sistem (Linux/macOS)

### Derleme
```bash
# Proje dizinine git
cd philo/

# Derle
make

# Temizle
make clean

# Tamamen temizle
make fclean

# Yeniden derle
make re
```

## 💻 Kullanım

### Temel Komut
```bash
./philo count tt_die tt_eat tt_sleep [must_eat]
```

### Parametreler
| Parametre | Açıklama | Örnek |
|-----------|----------|-------|
| `count` | Filozof sayısı (ve eş sayıda çatal) | `5` |
| `tt_die` | Aç kalarak ölmeyeceği maksimum süre (ms) | `800` |
| `tt_eat` | Yemek yeme süresi (ms) | `200` |
| `tt_sleep` | Uyuma süresi (ms) | `200` |
| `must_eat` | **(Opsiyonel)** Her filozofun kaç kez yemek yemesi gerektiği | `7` |

### 📝 Örnek Kullanımlar

```bash
# 5 filozof, 800ms'de ölür, 200ms yer, 200ms uyur
./philo 5 800 200 200

# 4 filozof, her biri 3 kez yemek yemeli
./philo 4 410 200 200 3

# Tek filozof (özel durum)
./philo 1 800 200 200

# Büyük grup
./philo 100 800 200 200
```

## 📊 Çıktı Formatı

```
<timestamp> <philosopher_id> <status>
```

### Çıktı Elemanları
| Eleman | Açıklama | Örnek |
|--------|----------|-------|
| `timestamp` | Başlangıçtan geçen milisaniye | `142` |
| `philosopher_id` | Filozof kimlik numarası (1..count) | `3` |
| `status` | Filozofun mevcut durumu | `is eating` |

### Durum Mesajları
- 🍴 `has taken a fork` - Çatal aldı
- 🍽️ `is eating` - Yemek yiyor  
- 😴 `is sleeping` - Uyuyor
- 🤔 `is thinking` - Düşünüyor
- ☠️ `died` - Öldü

### Örnek Çıktı
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
142 2 has taken a fork
142 2 has taken a fork  
142 2 is eating
200 1 is sleeping
342 2 is sleeping
400 1 is thinking
```

## 🔒 Deadlock ve Data Race Çözümleri

### 🚫 Deadlock Prevention (Kilitlenme Önleme)
**Problem**: Filozoflar karşılıklı olarak birbirlerinin ellerindeki çatalı beklerse kilitlenme oluşur.

**Çözüm**: **Dijkstra'nın Banker's Algorithm** prensibi uygulanır:
```c
// Deadlock önlemek için fork sıralaması
if (philo->left_fork < philo->right_fork) {
    take_fork(philo, philo->left_fork);
    take_fork(philo, philo->right_fork);
} else {
    take_fork(philo, philo->right_fork);
    take_fork(philo, philo->left_fork);
}
```

### 🛡️ Data Race Protection (Veri Yarışı Koruması)
**Problem**: Birden fazla thread'in paylaşılan verilere eşzamanlı erişmesi veri tutarsızlığına yol açar.

**Çözüm**: Kritik bölgeler mutex ile korunur:
- **`print_mutex`**: Çıktı senkronizasyonu
- **`death_mutex`**: Ölüm durumu kontrolü  
- **`forks[i]`**: Her çatal için ayrı mutex

```c
// Güvenli çıktı
pthread_mutex_lock(&vars->print_mutex);
printf("%ld %d %s\n", timestamp, id, message);
pthread_mutex_unlock(&vars->print_mutex);
```

## 📁 Proje Yapısı

```
philo/
├── 📄 Makefile          # Derleme konfigürasyonu
├── 📄 philo.h           # Header dosyası (struct ve prototipler)
├── 📄 main.c            # Program giriş noktası ve argüman kontrolü
├── 📄 init.c            # Mutex ve filozof dizilim başlatma
├── 📄 routine.c         # Ana filozof döngüsü (eat/sleep/think)
├── 📄 utils.c           # Yardımcı fonksiyonlar (zaman, uyku, fork)
├── 📄 check_alive.c     # Hayatta kalma kontrol thread'i
├── 📄 atoi.c            # Güvenli string->int dönüşümü
└── 📁 obj/              # Object dosyaları (.o)

practices/                # Öğrenme materyalleri
├── 📄 00_time.c         # Zaman ölçümü örnekleri
├── 📄 01_thread.c       # Thread kullanımı
├── 📄 02_mutex.c        # Mutex örnekleri
└── 📄 03_semaphore.c    # Semaphore alternatifleri
```

### Modül Açıklamaları

| Dosya | Sorumluluk | Ana Fonksiyonlar |
|-------|------------|------------------|
| **`philo.h`** | Veri yapıları ve prototipler | `t_philo`, `t_vars` struct'ları |
| **`main.c`** | Program akışı ve temizlik | `main()`, `check_args()`, `clean()` |
| **`init.c`** | Başlatma işlemleri | `init_prog()`, mutex ve thread init |
| **`routine.c`** | Filozof yaşam döngüsü | `routine()`, `take_forks()`, yemek döngüsü |
| **`utils.c`** | Yardımcı operasyonlar | `get_time_ms()`, `ft_sleep()`, `log_status()` |
| **`check_alive.c`** | Monitoring | `check_alive()`, `is_dead()` |
| **`atoi.c`** | Güvenli parsing | `ft_atoi()` (overflow korumalı) |

## 🧪 Test Senaryoları

### ✅ Temel Test Durumları
```bash
# 1. Normal çalışma
./philo 5 800 200 200

# 2. Hızlı ölüm testi  
./philo 4 310 200 100

# 3. Tek filozof (özel durum)
./philo 1 800 200 200

# 4. Must eat tamamlama
./philo 4 410 200 200 3

# 5. Büyük grup performansı
./philo 200 800 200 200
```

### 🚨 Edge Case Testleri
```bash
# Impossible scenario (hemen ölmeli)
./philo 4 1 800 200

# Very fast eating
./philo 5 800 1 1

# Large group with tight timing
./philo 100 410 200 200
```

---

<div align="center">
  <p><strong>🎓 42 İstanbul'da geliştirilmiştir</strong></p>
</div>
