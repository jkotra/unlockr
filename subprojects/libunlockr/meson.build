project('libunlockr', 'cpp', 
        default_options : ['werror=false'])

deps = [
    dependency('libqpdf', version: '>=11.0.0'),
    dependency('glib-2.0', version: '>=2.0')
]


so = shared_library('unlockr',
  'libunlockr.cpp',
  dependencies: deps,
  install : true,
  install_dir: get_option('prefix') / 'lib'
  )

message(so.full_path())