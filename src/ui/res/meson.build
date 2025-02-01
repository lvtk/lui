
res_sources = []

res_gen = generator (find_program('python3', 'python'),
    output : [ '@PLAINNAME@.h' ],
    arguments : [ meson.project_source_root() / 'scripts/bin2c.py', 
                  '@INPUT@', '@OUTPUT@', '@INPUT@' ])

res_sources += res_gen.process ('Roboto-Regular.ttf', 'Roboto-Bold.ttf', 'Roboto-Light.ttf')
res_includes = include_directories('.')
