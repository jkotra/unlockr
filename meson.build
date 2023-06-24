project('com.github.jkotra.unlockr' , 'c', 
          version: '0.8.1',
    meson_version: '>= 0.58.0',
  default_options:  [ 'warning_level=2',
                      'c_std=gnu11',
                      'werror=true',
                    ],
)

add_global_arguments([
                      '-Wno-unused-variable',
                      '-Wno-unused-parameter'
                      ],
                     language: 'c')

app_id = 'com.github.jkotra.unlockr'
project_id = app_id

prefix = get_option('prefix') # should be /usr
bindir = get_option('bindir') # should be bin
datadir = get_option('datadir') # should be /usr/share
icondir = join_paths(datadir, 'icons/hicolor')
locale_dir = join_paths(prefix, get_option('localedir'))

add_project_arguments([
  '-I' + meson.project_build_root(),
], language: 'c')

subdir('include')
subdir('src')
subdir('po')
subdir('data')

meson.add_install_script('meson_post_install.py')