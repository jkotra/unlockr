#!/usr/bin/env python3

import shutil
import subprocess
from pathlib import Path
LDD = "C:/msys64/usr/bin/ldd.exe"
MINGW_W64_BIN_DIR = Path("C:/msys64/mingw64/bin")

shutil.copyfile("C:/msys64/mingw64/share/glib-2.0/schemas/gschemas.compiled", "build/src/gschemas.compiled")
shutil.copyfile("build/subprojects/libunlockr/libunlockr.dll", "build/src/libunlockr.dll")
out = subprocess.run([LDD, "build/src/unlockr.exe"], stdout=subprocess.PIPE)
for lib in out.stdout.decode("utf-8").strip().split("\n"):
    _lib = lib.split("=>")
    lib_name = _lib[0].strip()
    lib_path = _lib[1].strip().split(" ")[0].strip()
    print(lib_name, lib_path)

    if "mingw64" in lib_path:
        shutil.copyfile(MINGW_W64_BIN_DIR / lib_name, f"build/src/{lib_name}")
        print(lib_name, "copied")

shutil.make_archive("release", "zip", "build/src/")