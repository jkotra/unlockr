conf = configuration_data()
conf.set('VERSION', meson.project_version())
conf.set('LOCALE_DIR', join_paths(get_option('prefix'), get_option('datadir'), 'locale'))

bin_exec = configure_file(
  input: 'details.h',
  output: 'details.h',
  configuration: conf,
)