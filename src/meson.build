sources = [
  'main.c',
  'about.c',
  'process.c',
  'utils.c'
]

libunlockr_project = subproject('libunlockr')
so = libunlockr_project.get_variable('so')

deps = [
  dependency('gio-2.0', version: '>= 2.50'),
  dependency('libadwaita-1', version: '>=1'),
  dependency('gmodule-2.0', version: '>=2.0'),
]

gnome = import('gnome')

sources += gnome.compile_resources('unlockr-resources',
                                    '../data/unlockr.gresource.xml',
                                    c_name: 'unlokckr',
                                    source_dir: '../data'
                                )

if build_machine.system() == 'windows'
  windows = import('windows')
  sources += windows.compile_resources('../data/icons/favicon.rc',
                                        depend_files: '../data/icons/com.github.jkotra.unlockr.ico'
  )
endif

incdir = include_directories('../include')

#Note - win_subsystem: 'windows,6.0' is required to hide CMD window.
executable('unlockr', sources,
dependencies: deps,
include_directories : incdir,
install: true,
link_with: so,
win_subsystem: 'windows,6.0'
)