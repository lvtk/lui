
libdir = get_option('libdir')

### LVTK Widgets
widgets_sources = files('''
    ui/button.cpp
    ui/embed.cpp
    ui/entry.cpp
    ui/font.cpp
    ui/graphics.cpp
    ui/image.cpp
    ui/main.cpp
    ui/fitment.cpp
    ui/slider.cpp
    ui/style.cpp
    ui/view.cpp
    ui/widget.cpp
'''.split())

if host_machine.system() == 'darwin'
    widgets_sources += 'ui/embed_mac.mm'
elif host_machine.system() == 'linux'
    widgets_sources += 'ui/embed_x11.cpp'
elif host_machine.system() == 'windows'
    widgets_sources += 'ui/embed_win32.cpp'
endif

liblui_deps = [ lui_internal_dep, pugl_dep, boost_dep, ui_apple_deps ]
add_project_arguments ('-DPUGL_STATIC', language : ['c', 'cpp'])

liblui = library ('lui-@0@'.format (lui_abi_version),
    widgets_sources,
    c_args : [ '-DLUI_BUILD' ],
    cpp_args : [ '-DLUI_BUILD' ],
    dependencies : liblui_deps,
    gnu_symbol_visibility : 'hidden',
    install : true,
    install_dir : libdir)
lui_dep = declare_dependency (
    link_with : liblui,
    include_directories : [],
    dependencies : liblui_deps)

subdir ('ui/res')

### Lui Cairo
if cairo_dep.found()
    cairo_deps = [ lui_dep, cairo_dep, pugl_cairo_dep ]
    libcairo = library ('lui-cairo-@0@'.format (lui_abi_version),
        [ 'ui/cairo.cpp' ],
        gnu_symbol_visibility : 'hidden',
        link_with : [],
        include_directories : [],
        c_args : [ '-DLUI_BUILD' ],
        cpp_args : [ '-DLUI_BUILD' ],
        dependencies : cairo_deps,
        install : true,
        install_dir : libdir)
    lui_cairo_dep = declare_dependency (
        link_with : [ libcairo ],
        include_directories : [],
        dependencies : cairo_deps)
else
    lui_cairo_dep = dependency('', required : false)
endif
