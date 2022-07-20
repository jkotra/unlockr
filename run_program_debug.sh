set -e
rm -rf build
meson build
ninja -C build
G_MESSAGES_DEBUG=all ./build/src/unlockr