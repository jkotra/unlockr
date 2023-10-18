set -e
rm -rf build
meson setup build
ninja -C build
export GSETTINGS_SCHEMA_DIR="build/data"
export G_MESSAGES_DEBUG=all
./build/src/unlockr