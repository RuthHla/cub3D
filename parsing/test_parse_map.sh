#!/bin/bash

# === 0) Config générale ===
CC="cc"
CFLAGS="-Wall -Wextra -Werror -g"

# Chemins vers les libs comme dans ton Makefile
LIBFT_DIR="../libft"
CUB_DIR="."

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
parse_map.c
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
    "../map/bad/map_first.cub"
    "../map/bad/map_middle.cub"
    "../map/bad/map_missing.cub"
    "../map/bad/map_only.cub"
    "../map/bad/map_too_small.cub"
    "../map/bad/player_multiple.cub"
    "../map/bad/player_none.cub"
    "../map/bad/player_on_edge.cub"
    "../map/bad/wall_hole_east.cub"
    "../map/bad/wall_hole_north.cub"
    "../map/bad/wall_hole_south.cub"
    "../map/bad/wall_hole_west.cub"
    "../map/bad/wall_none.cub"
    "../map/good/creepy.cub"
    "../map/good/glue.cub"
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

