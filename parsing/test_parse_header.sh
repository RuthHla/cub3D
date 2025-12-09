#!/bin/bash

# === 0) Config générale ===
CC="cc"
CFLAGS="-Wall -Wextra -Werror -g"

# Chemins vers les libs comme dans ton Makefile
LIBFT_DIR="../libft"
CUB_DIR="."   # à adapter si ta lib cub est dans un sous-dossier

# === 1) Build des bibliothèques ===

echo "=== Building libft ==="
make -C "$LIBFT_DIR" || { echo "❌ libft: build failed"; exit 1; }
echo "✅ libft OK"
echo

# === 2) Compilation du binaire de test ===

SRC="
main_test.c
parse_arg.c
save_map.c
parse_colors.c
parse_textures.c
utils.c
../init/init.c
../init/build_map.c
"

OUT="parser_tester"

echo "Compiling $OUT..."

# -I. au cas où ton cub.h est à la racine
# -I"$LIBFT_DIR" si tu inclues "libft.h"
# -L"$LIBFT_DIR" -lft pour linker libft.a
$CC $CFLAGS $SRC \
    -I. -I"$LIBFT_DIR" \
    -L"$LIBFT_DIR" -lft \
    -o "$OUT" || { echo "❌ Compilation failed"; exit 1; }

echo "✅ Compilation OK"
echo

# === 3) Liste des maps à tester ===
MAPS=(
    "../map/bad/color_invalid_rgb.cub"
    "../map/bad/color_missing_ceiling_rgb.cub"
    "../map/bad/color_missing_floor_rgb.cub"
    "../map/bad/color_missing.cub"
    "../map/bad/color_none.cub"
    "../map/bad/empty.cub"
    "../map/bad/file_letter_end.cub"
    "../map/bad/filetype_missing"
    "../map/bad/filetype_wrong.buc"
    "../map/bad/no_permission.cub"
    "../map/bad/textures_dir.cub"
    "../map/bad/textures_duplicates.cub"
    "../map/bad/textures_forbidden.cub"
    "../map/bad/textures_invalid.cub"
    "../map/bad/textures_missing.cub"
    "../map/bad/textures_none.cub"
    "../map/bad/textures_not_xpm.cub"
)

# === 4) Lancement des tests ===
# === 4) Lancement des tests ===
echo "Running tests..."
echo

#important de boucler les executions sinon pb avec le buf static/fd de gnl
for map in "${MAPS[@]}"; do
    ./"$OUT" "$map"
    echo
done

