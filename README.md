# unlockR

A simple tool to decrypt PDf files.

---

## Linux

`meson build -Dprefix=/usr`

`ninja install -C build`


## Windows

### Install dependencies


```
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-gtk4 mingw-w64-x86_64-libadwaita mingw-w64-x86_64-qpdf mingw-w64-x86_64-pkg-config
```



* to import ddl dependencies in `msys2.exe`:
`ldd unlockr.exe | grep '\/mingw.*\.dll' -o | xargs -I{} cp "{}" .`

* Or, run `windows_portable.py`