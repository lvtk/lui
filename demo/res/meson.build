demo_res_sources = []

demo_res_gen = generator (find_program('python3', 'python'),
    output : [ '@PLAINNAME@.h' ],
    arguments : [ meson.project_source_root() / 'scripts' / 'bin2c.py', 
                  '@INPUT@', '@OUTPUT@', '@INPUT@' ])

demo_res_sources += demo_res_gen.process (
    'lv2_logo.png'
)
demo_res_includes = include_directories('.')
