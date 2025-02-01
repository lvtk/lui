
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

widgets_deps = [ dep, pugl_dep, boost_dep, ui_apple_deps ]
add_project_arguments ('-DPUGL_STATIC', language : ['c', 'cpp'])

libwidgets = library ('lvtk-widgets-@0@'.format (lui_abi_version),
    widgets_sources,
    c_args : [ '-DLUI_BUILD' ],
    cpp_args : [ '-DLUI_BUILD' ],
    dependencies : widgets_deps,
    gnu_symbol_visibility : 'hidden',
    install : true,
    install_dir : libdir)
widgets_dep = declare_dependency (
    link_with : libwidgets,
    include_directories : [],
    dependencies : widgets_deps)

subdir ('ui/res')

### LVTK Cairo
if pugl_cairo_dep.found()
    cairo_deps = [ widgets_dep, cairo_dep, pugl_cairo_dep ]
    libcairo = library ('lvtk-cairo-@0@'.format (lui_abi_version),
        [ 'ui/cairo.cpp' ],
        gnu_symbol_visibility : 'hidden',
        link_with : [],
        include_directories : [],
        c_args : [ '-DLUI_BUILD' ],
        cpp_args : [ '-DLUI_BUILD' ],
        dependencies : cairo_deps,
        install : true,
        install_dir : libdir)
    cairo_dep = declare_dependency (
        link_with : [ libcairo ],
        include_directories : [],
        dependencies : cairo_deps)
else
    cairo_dep = dependency('', required : false)
endif

### LVTK Hosting
# The host_dep is declared for convenience to pull in lilv and suil
if lilv_dep.found() and suil_dep.found()
    host_dep = declare_dependency (
        link_with : [],
        include_directories : [],
        dependencies : [ dep, lilv_dep, suil_dep ])
else
    host_dep = dependency('', required : false)
endif
