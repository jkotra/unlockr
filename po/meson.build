i18n = import('i18n')

message('Update translations')
i18n.gettext('unlockr', preset: 'glib')


i18n.merge_file(
    input: '../data/' + project_id + '.desktop',
    output: project_id + '.desktop',
    po_dir: '.',
    type: 'desktop',
    install: true,
    install_dir: join_paths(datadir, 'applications')
)


i18n.merge_file(
    input: '../data/' + project_id + '.metainfo.xml',
    output: project_id + '.metainfo.xml',
    po_dir: '.',
    install: true,
    install_dir: join_paths(datadir, 'metainfo')
)