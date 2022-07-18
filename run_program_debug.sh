set -e
rm -rf build
meson build
ninja -C build
./build/src/unlockr