# unlockR


<img height="256" alt="unlockR" src="static/light.png" />

A simple tool to decrypt PDF files.

---

## Linux

<a href='https://flathub.org/apps/details/com.github.jkotra.unlockr'><img height='50' alt='Download on Flathub' src='https://flathub.org/assets/badges/flathub-badge-en.png'/></a>

`meson build -Dprefix=/usr`
`ninja install -C build`

### Flatpak


```
flatpak-builder --user --install build-dir dist/flatpak/com.github.jkotra.unlockr.yml --force-clean
```

to build from local directory, use:
```
flatpak-builder --user --install build-dir dist/flatpak/local.yml --force-clean
```

---

## Windows

### Install dependencies


```
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-gtk4 mingw-w64-x86_64-libadwaita mingw-w64-x86_64-qpdf mingw-w64-x86_64-pkg-config
```



to import ddl dependencies in `msys2.exe`:

`ldd unlockr.exe | grep '\/mingw.*\.dll' -o | xargs -I{} cp "{}" .`


* Or, run `windows_portable.py`