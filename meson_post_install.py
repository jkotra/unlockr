#!/usr/bin/env python3
from os import environ, path
import platform
from subprocess import call
import platform

print("post install script...")

prefix = environ.get('MESON_INSTALL_PREFIX', '/usr/local')
datadir = path.join(prefix, 'share')
destdir = environ.get('DESTDIR', '')
print(prefix, datadir, destdir)

if "linux" in platform.platform().lower():
    print('Updating icon cache...')
    call(['gtk-update-icon-cache', '-qtf', path.join(datadir, 'icons', 'hicolor')])
    print("Installing new Schemas")
    call(['glib-compile-schemas', path.join(datadir, 'glib-2.0/schemas')])