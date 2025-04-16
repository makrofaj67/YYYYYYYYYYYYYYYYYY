Harika bir derleme yapmışsın! Şimdi bu maddeleri daha düzenli, mantıksal bir sıra ile ve eksikleri/yanlışları düzelterek temize çekelim. Bu liste, harita doğrulama (parsing) aşamasında yapman gereken tüm kontrolleri kapsamalıdır:

so_long Harita Doğrulama Kontrol Listesi

    Argüman Kontrolü:

        Program tam olarak bir argümanla mı çalıştırıldı?

        Verilen argüman (dosya adı) .ber uzantısı ile mi bitiyor?

    Dosya Erişimi ve İçeriği:

        Argüman olarak verilen dosya var mı ve okuma izni var mı? (open ile kontrol)

        Dosya boş mu? (Boş dosya geçersizdir).

        Dosya okunurken bir hata oluştu mu? (read ile kontrol)

    Harita Yapısı Kontrolleri:

        Dikdörtgenlik: Haritadaki tüm satırlar aynı uzunlukta mı? (Farklı uzunluktaki satırlar geçersizdir).

        Minimum Boyut: Harita, duvarlarla çevrilebilecek ve en az 1 'P', 1 'E', 1 'C' içerebilecek kadar büyük mü? (Genellikle en az 3x3 boyutunda olması mantıklıdır, ama bu dolaylı olarak diğer kurallarla da kontrol edilebilir).

        Geçerli Karakterler: Harita sadece 0 (boş alan), 1 (duvar), C (koleksiyon), E (çıkış), P (başlangıç) karakterlerini mi içeriyor? Başka herhangi bir karakter (boşluk, tab, geçersiz karakterler vb.) var mı?

    Harita İçeriği Kontrolleri:

        Duvarla Çevrilme (Enclosed/Surrounded): Haritanın tüm dış kenarları (ilk satır, son satır, ilk sütun, son sütun) tamamen '1' (duvar) karakterlerinden mi oluşuyor?

        Gerekli Bileşen Sayıları:

            Haritada tam olarak 1 tane 'P' (başlangıç noktası) var mı? (Ne eksik ne fazla).

            Haritada tam olarak 1 tane 'E' (çıkış) var mı? (Ne eksik ne fazla).

            Haritada en az 1 tane 'C' (koleksiyon) var mı? (Daha fazla olabilir ama sıfır olamaz).

    Yol Geçerliliği Kontrolü:

        Oyuncu ('P'), harita üzerinde hareket ederek ('0', 'C', 'E' üzerinden, '1' duvarlarından geçemez) tüm 'C' (koleksiyon) karakterlerine ulaşabiliyor mu?

        Oyuncu, tüm koleksiyonları topladıktan sonra 'E' (çıkış) karakterine ulaşabiliyor mu?

        Önemli Not: Bu kontrol genellikle bir pathfinding algoritması (Flood Fill veya Breadth-First Search gibi) ile yapılır. Önce P'den tüm C'lere ve E'ye erişim var mı diye kontrol edilir.

Genel Hata Yönetimi Kuralı:

    Yukarıdaki kontrollerden herhangi biri başarısız olursa (yani bir kural ihlal edilirse):

        Program standart çıktıya tam olarak "Error\n" mesajını yazdırmalıdır.

        (İsteğe bağlı ama önerilen): "Error\n" mesajından sonra, hatanın nedenini belirten daha açıklayıcı bir mesaj yazdırılabilir (Örn: "Error\nMap is not rectangular.\n").

        O ana kadar malloc ile ayrılmış tüm bellek alanları free ile serbest bırakılmalıdır (hafıza sızıntısı olmamalıdır).

        Açık olan dosya tanıtıcıları kapatılmalıdır.

        Program exit() fonksiyonu ile (genellikle exit(1) gibi bir hata koduyla) sonlandırılmalıdır.

Bu liste, önceki listendeki tüm geçerli noktaları içeriyor, yanlışları (kare yerine dikdörtgen) düzeltiyor ve bazı noktaları (duvarlar ve P/E sayısı gibi) netleştiriyor. Bu sırayla kontrolleri yaparsan daha mantıklı bir akış izlemiş olursun.
