set -e
rm -rf build
meson setup build
ninja -C build
G_MESSAGES_DEBUG=all ./build/src/unlockr