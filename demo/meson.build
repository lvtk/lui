demo_sources = '''
    demo.cpp
    dials.cpp
    entry.cpp
    images.cpp
    sliders.cpp
'''.split()

subdir('res')
demo_sources += demo_res_sources

demo_deps = [ lui_cairo_dep, cairo_dep, threads_dep ]

demo_includes = include_directories ('.')

liblui_demo = static_library ('lui-demo',
    demo_sources,
    include_directories : [ demo_includes ],
    dependencies : [ demo_deps ],
    install : false
)
