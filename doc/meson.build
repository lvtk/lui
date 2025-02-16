docs_enabled = get_option('doc').enabled()
dot = find_program ('dot', required : docs_enabled)
doxygen = find_program ('doxygen', required : docs_enabled)
sphinx_build = find_program ('sphinx-build', required : docs_enabled)

if doxygen.found() and sphinx_build.found() and dot.found()

conf_py = configure_file (configuration: {
        'LUI_VERSION' : meson.project_version() 
    },
    input : 'conf.py.in',
    output : 'conf.py')

overview = configure_file (configuration: {
        'LUI_VERSION' : meson.project_version(),
        'lui_abi_version'  : lui_abi_version
    },
    input : 'overview.rst.in',
    output : 'overview.rst')

rst_sources = files ('''
    development.rst
    dynmanifest.rst
    extensions.rst
    highlevel.rst
    hosting.rst
    graphics.rst
    index.rst
    styleguide.rst
    summary.rst
    widgets.rst
    plugins.rst
    projects.rst
    uis.rst
'''.split())

foreach f : rst_sources
  configure_file(copy: true, input: f, output: '@PLAINNAME@')
endforeach

subdir ('api')
subdir ('ui')

docs = custom_target(
  'html',
  command: [sphinx_build, '-M', 'html', '@OUTDIR@', '@OUTDIR@',
            '-E', '-q', '-t', 'html'],
  input: [ rst_sources ],
  output: 'html',
  build_by_default: true,
  install: true,
  install_dir: get_option('datadir') / 'doc' / 'lui-0')

subdir ('html/_static/js')

endif
