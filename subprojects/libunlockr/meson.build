project('libunlockr', 'cpp')

deps = [
    dependency('libqpdf', version: '>=10.5.0'),
    dependency('glib-2.0', version: '>=2.0')
]


so = shared_library('unlockr',
  'libunlockr.cpp',
  dependencies: deps,
  install : true,
  install_dir: get_option('prefix') / 'lib'
  )

message(so.full_path())