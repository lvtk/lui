cc = meson.get_compiler ('c')
cpp = meson.get_compiler ('cpp')
dl_dep = cc.find_library ('dl', required: false)
reuse_program = find_program ('reuse', required : false)
threads_dep = dependency ('threads')

cocoa_dep = dependency('', required : false)
corevideo_dep = dependency('', required : false)
apple_deps = []
ui_apple_deps = []

if host_machine.system() == 'darwin'
    cocoa_dep = dependency('appleframeworks', required: true, 
        modules: ['Foundation'])
    corevideo_dep = dependency('appleframeworks', required: false, 
        modules: ['CoreVideo', 'CoreGraphics', 'Cocoa'])
    apple_deps = [cocoa_dep]
    ui_apple_deps = [apple_deps, corevideo_dep]
endif

### Cairo
cairo_dep = dependency ('cairo', 
    required : true,
    fallback: [ 'cairo', 'cairo_dep' ],
    version : '>= 1.16.0',
    default_options : [
        'default_library=static',
        'quartz=auto',
        'png=enabled',
        'dwrite=enabled',
        'fontconfig=enabled',
        'freetype=disabled',
        'tests=disabled',
        'gtk2-utils=disabled',
        'xlib=@0@'.format(host_machine.system() == 'linux' ? 'enabled' : 'disabled'),
        'xcb=disabled',
        'xlib-xcb=disabled',
        'glib=disabled',
        'spectre=disabled',
        'symbol-lookup=disabled',
        'tee=disabled',
        'zlib=disabled',
        'c_args=-Wno-maybe-uninitialized'
    ])

### Pugl
pugl_opts = [
    'default_library=static',
    'tests=disabled',
    'examples=disabled',
    'cairo=@0@'.format (cairo_dep.found() ? 'enabled' : 'disabled'),
    'opengl=disabled',
    'vulkan=disabled',
    'stub=false',
    'docs=disabled'
]

pugl_dep = dependency ('pugl-0', 
    fallback : [ 'pugl', 'pugl_dep' ],
    version : '>= 0.4.0',
    required : true,
    default_options : pugl_opts
)

pugl_cairo_dep = dependency ('', required : false)
if cairo_dep.found()
    pugl_cairo_dep = dependency ('pugl-cairo-0', 
        fallback : [ 'pugl', 'pugl_cairo_dep' ],
        version : '>= 0.4.0',
        default_options : pugl_opts,
        required : true
    )
endif

### Boost
boost_dep = dependency ('boost', required: get_option('test').enabled())

### Lua if wanted
lua_dep = dependency ('', required : false)
lua_program = find_program ('', required : false)
lua_version = '0.0.0'

if not get_option ('bindings').disabled()
    ## Lua: Use either lua 5.3 or 5.4 depending on what's on the
    # system.  If lua not found. Use 5.4.

    lua_system = false

    if host_machine.system() != 'windows'
        lua_dep = dependency('', required : false)
        lua_version = ''
        lua_program = find_program ('lua5.4', required : false)

        if not lua_program.found()
            lua_program = find_program('lua5.3', required : false)
        endif

        if not lua_program.found()
            lua_program = find_program('lua', required : false)
        endif

        if lua_program.found()
            pymod = import('python')
            lua_version = run_command(pymod.find_installation('python3'), '../../scripts/luavers.py',
                lua_program, check : true).stdout().strip()
            if not lua_version.version_compare ('>= 5.3')
            lua_system = false
            else
            lua_system = true
            endif
        endif
    endif

    if not lua_system
        lua_proj = subproject ('lua', 
        default_options : [
            'loadlib=disabled',
            'interpreter=true',
            'line_editing=disabled'
        ])

        lua_dep = lua_proj.get_variable ('lua_dep')
        lua_version = '5.4'
        lua_program = lua_proj.get_variable ('lua_exe')
        lua_system = false
    endif
endif
