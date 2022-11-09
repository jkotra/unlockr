install_data(
    'icons/'+app_id+'.svg',
    install_dir: join_paths(icondir / 'scalable' / 'apps')
)

i18n.merge_file(
    input: project_id + '.desktop',
    output: project_id + '.desktop',
    po_dir: '../po',
    type: 'desktop',
    install: true,
    install_dir: join_paths(datadir, 'applications')
)


i18n.merge_file(
    input: project_id + '.metainfo.xml',
    output: project_id + '.metainfo.xml',
    po_dir: '../po',
    install: true,
    install_dir: join_paths(datadir, 'metainfo')
)