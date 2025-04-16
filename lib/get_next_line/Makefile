# Hedef kütüphane dosyası adı
NAME = getnextline.a

# Derleyici ve arşivleyici
CC = gcc
AR = ar rcs
RM = rm -f

# Derleyici bayrakları (Uyarıları aç, hataları göster, header dosyaları için geçerli dizini ekle)
CFLAGS = -Wall -Wextra -Werror -I.

# --- Dosya Tanımları ---

# Zorunlu ('Mandatory') kaynak dosyaları
SRCS_MANDATORY = get_next_line.c \
                 get_next_line_utils.c

# Bonus kaynak dosyaları
SRCS_BONUS = get_next_line_bonus.c \
             get_next_line_utils_bonus.c

# Zorunlu kaynak dosyalarından türetilen obje dosyaları (.o)
OBJS_MANDATORY = $(SRCS_MANDATORY:.c=.o)

# Bonus kaynak dosyalarından türetilen obje dosyaları (.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

# Header dosyaları (Derleme bağımlılıkları için)
HDRS = get_next_line.h
HDRS_BONUS = get_next_line_bonus.h # Bonus header'ı da ekleyelim

# --- Hedef Kuralları ---

# Varsayılan hedef: Zorunlu kütüphaneyi oluştur
all: $(NAME)

# Zorunlu kütüphaneyi oluşturma kuralı
# $(OBJS_MANDATORY)'ye bağlıdır.
$(NAME): $(OBJS_MANDATORY)
	@$(AR) $(NAME) $(OBJS_MANDATORY)
	@echo "GetNextLine (Mandatory) kütüphanesi '$(NAME)' oluşturuldu."

# Bonus kütüphaneyi oluşturma kuralı
# Bu hedef, mevcut $(NAME) dosyasını bonus versiyonuyla değiştirir.
# Önce mevcut objeleri temizler, sonra bonus objeleri derler ve arşivler.
bonus: fclean_objs $(OBJS_BONUS)
	@$(AR) $(NAME) $(OBJS_BONUS)
	@echo "GetNextLine (Bonus) kütüphanesi '$(NAME)' oluşturuldu (mevcut üzerine yazıldı)."

# Genel kural: .c dosyasını .o dosyasına derle
# İlgili header dosyalarındaki değişiklikleri de takip eder.
%.o: %.c $(HDRS) $(HDRS_BONUS) Makefile
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Derlendi: $< -> $@"

# Obje dosyalarını temizleme
clean:
	@$(RM) $(OBJS_MANDATORY) $(OBJS_BONUS)
	@echo "GetNextLine obje dosyaları temizlendi."

# Sadece obje dosyalarını temizlemek için yardımcı hedef (bonus tarafından kullanılır)
fclean_objs:
	@$(RM) $(OBJS_MANDATORY) $(OBJS_BONUS)

# Tam temizleme (obje dosyaları + kütüphane)
fclean: clean
	@$(RM) $(NAME)
	@echo "GetNextLine kütüphanesi '$(NAME)' temizlendi."

# Yeniden derleme (tam temizleme + varsayılan hedef)
re: fclean all

# Dosya olmayan hedefler (Make'in bu isimlerde dosya aramasını engeller)
.PHONY: all bonus clean fclean fclean_objs re
