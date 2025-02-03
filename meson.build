project ('lui', ['cpp', 'c'], 
    version : '0.0.1',
    meson_version : '>= 1.0.0',
    license : 'MIT',
    default_options: [
        'b_ndebug=if-release',
        'buildtype=release',
        'c_std=c99',
        'cpp_std=c++20',
    ])

# library versioning
version_array = meson.project_version().split('.')
lui_version_major = version_array[0].to_int()
lui_version_minor = version_array[1].to_int()
lui_version_micro = version_array[2].to_int()
lui_abi_version = '0.0'

if host_machine.system() == 'darwin'
    add_languages (['objcpp', 'objc' ])
endif

pymod = import('python')
python3_exe = pymod.find_installation ('python3')
bundle_py   = files ('scripts/bundle.py').get(0)

headers = []

subdir ('meson/deps')
subdir ('meson/supress')

if get_option('default_library') == 'both'
  if host_machine.system() == 'windows'
    error('default_library=both is not supported on Windows')
  endif
elif get_option('default_library') == 'static'
    add_project_arguments(['-DLUI_STATIC'], language: ['c', 'cpp'])
endif

lui_internal_dep = declare_dependency (
    include_directories : [ 'include', 'src' ],
    dependencies : [])

### shared libs
subdir ('src')

if not get_option('bindings').disabled()
    # subdir ('bindings')
endif

### Demo
if not get_option('demo').disabled()
    if pugl_cairo_dep.found()
        subdir ('demo')
        lui_demo_exe = executable (
            'lui-demo', 
            'demo/main.cpp',
            cpp_args : [ '-DLUI_NO_SYMBOL_EXPORT', '-DLUI_DEMO_CAIRO=1' ],
            include_directories : [],
            link_with : [ liblui_demo ],
            dependencies : [ demo_deps ],
            win_subsystem : 'windows',
            install : true
        )

        if host_machine.system() == 'darwin'
            bundle_cmd = [ python3_exe, bundle_py, '--binary', '@INPUT@',
                            '--output', '@OUTPUT@',
                            '--plist', files ('demo/Info.plist') ]

            if get_option ('buildtype').contains('debug')
                bundle_cmd = [ bundle_cmd, '--no-strip' ]
            endif

            custom_target (
                'LUI.app',
                build_by_default: true,
                command: bundle_cmd ,
                input: lui_demo_exe,
                output: 'LUI.app',
                install: false
            )
        endif
    endif
endif

### Install Headers and PC

install_subdir ('include' / 'lui', install_dir : get_option('includedir') / 'lui-@0@'.format(lui_abi_version))
subdir ('meson/pkgconfig')

### Tests
if not get_option('test').disabled()
    subdir('test')
endif

### Docs
if not get_option('doc').disabled()
    subdir ('doc')
endif

### Summary
summary('Docs', not get_option('doc').disabled(), bool_yn: true)

summary('Tests', not get_option('test').disabled(), bool_yn: true)

summary ('Modules', lua_dep.found(), section : 'Lua', bool_yn: true)
if lua_dep.found()
    summary('Tests', lua_program.found() and not get_option('test').disabled(), 
        section : 'Lua', bool_yn: true)
    summary('Version', lua_version, section : 'Lua')
endif

summary ('Graphics', 'Cairo', section : 'Widgets')
summary ('Demo', not get_option('demo').disabled(), bool_yn: true, section: 'Widgets')

summary ('Prefix', get_option('prefix'), section: 'Paths')
summary ('Headers', get_option('prefix') / get_option('includedir'), section: 'Paths')
summary ('Libraries', get_option('prefix') / get_option('libdir'), section: 'Paths')
summary ('Programs', get_option('prefix') / get_option('bindir'), section: 'Paths')
