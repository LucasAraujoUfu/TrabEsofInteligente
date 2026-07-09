#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Uso: $0 arquivo.cpp"
    exit 1
fi

SOURCE="$1"
EXECUTABLE="programa"

INPUT_DIR="input"
EXPECTED_DIR="output"
RESULT_DIR="exec"

mkdir -p "$RESULT_DIR"

echo "Compilando $SOURCE..."
g++ -std=c++17 -O2 "$SOURCE" -o "$EXECUTABLE"

if [ $? -ne 0 ]; then
    echo "Erro de compilação."
    exit 1
fi

echo "Compilação concluída."
echo

for input_file in "$INPUT_DIR"/*; do
    filename=$(basename "$input_file")
    output_file="$RESULT_DIR/$filename"
    expected_file="$EXPECTED_DIR/$filename"

    echo "Executando: $filename"

    start=$(date +%s%N)

	"./$EXECUTABLE" < "$input_file" > "$output_file"

	end=$(date +%s%N)
	elapsed_s=$(awk "BEGIN {printf \"%.6f\", ($end - $start)/1000000000}")

    if [ ! -f "$expected_file" ]; then
        echo "  [WARNING] Output esperado não encontrado."
        continue
    fi

    if diff -q "$output_file" "$expected_file" > /dev/null; then
        echo "  [OK] ${elapsed_s}s"
    else
        echo "  [FAIL]"
        diff -u "$expected_file" "$output_file"
    fi

    echo
done

rm -f "$EXECUTABLE"
