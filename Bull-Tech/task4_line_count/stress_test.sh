set -e

MAX_FILES=50000
MAX_LINES=10000

show_menu() {
  echo ""
  echo "  --- line_count Stres Testi ---"
  echo "  1) Küçük Doğruluk Testi"
  echo "  2) Çok Dosya (Thread Stress)"
  echo "  3) Büyük Dosya (I/O Stress)"
  echo "  4) Hem Büyük Hem Çok Dosya (Full Stress)"
  echo "  q) Çıkış"
  echo "  (Max dosya: $MAX_FILES, max satır/dosya: $MAX_LINES)"
  echo ""
  printf "  Seçiminiz [1-4, q]: "
}

ask_values() {
  local desc="$1"
  local num_files
  local lines_per_file

  echo ""
  echo "=== $desc ==="
  printf "  Dosya sayısı (1-%s): " "$MAX_FILES"
  read -r num_files || exit 0
  printf "  Satır per dosya (1-%s): " "$MAX_LINES"
  read -r lines_per_file || exit 0

  if ! [[ "$num_files" =~ ^[0-9]+$ ]] || [ "$num_files" -lt 1 ]; then
    echo "  Hata: dosya sayısı pozitif tam sayı olmalı." >&2
    return 1
  fi
  if [ "$num_files" -gt "$MAX_FILES" ]; then
    echo "  Hata: en fazla $MAX_FILES dosya (max)." >&2
    return 1
  fi
  if ! [[ "$lines_per_file" =~ ^[0-9]+$ ]] || [ "$lines_per_file" -lt 1 ]; then
    echo "  Hata: satır sayısı pozitif tam sayı olmalı." >&2
    return 1
  fi
  if [ "$lines_per_file" -gt "$MAX_LINES" ]; then
    echo "  Hata: en fazla $MAX_LINES satır/dosya (max)." >&2
    return 1
  fi

  run_test "$num_files" "$lines_per_file" "stress_test_${num_files}f_${lines_per_file}l" "$desc"
}

run_test() {
  local num_files=$1
  local lines_per_file=$2
  local dir_name=$3
  local desc="$4"

  echo ""
  echo "  Dosya sayısı: $num_files"
  echo "  Satır/dosya: $lines_per_file"
  echo "  Klasör: $dir_name"
  echo ""

  rm -rf "$dir_name"
  mkdir -p "$dir_name"

  echo "  Oluşturuluyor..."
  for i in $(seq 1 "$num_files"); do
    for j in $(seq 1 "$lines_per_file"); do echo "line $j in file $i"; done > "$dir_name/f_$i.txt"
  done

  echo "  line_count çalıştırılıyor..."
  time ./line_count "$dir_name"
  echo "  Bitti. Klasör: $dir_name ($(ls -1 "$dir_name" | wc -l | tr -d ' ') dosya)"
}

# Menü (argüman yoksa)
if [ $# -eq 0 ]; then
  while true; do
    show_menu
    read -r choice || exit 0
    case "$choice" in
      1)
        ask_values "Küçük Doğruluk Testi" || true
        ;;
      2)
        ask_values "Çok Dosya (Thread Stress)" || true
        ;;
      3)
        ask_values "Büyük Dosya (I/O Stress)" || true
        ;;
      4)
        ask_values "Hem Büyük Hem Çok Dosya (Full Stress)" || true
        ;;
      q|Q)
        echo "  Çıkılıyor."
        exit 0
        ;;
      *)
        echo "  Geçersiz seçim. 1, 2, 3, 4 veya q girin."
        ;;
    esac
  done
fi
