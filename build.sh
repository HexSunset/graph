mkdir -p build/
g++ -o build/main src/main.cpp -lm -lraylib

if [[ "$1" = "run" && $? -eq 0 ]]; then
    build/main
fi
