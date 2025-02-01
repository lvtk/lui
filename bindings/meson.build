
luadir_c = get_option('luadir_c')
if luadir_c == 'auto'
    luadir_c = get_option('libdir') / 'lua'
endif

luadir = get_option('luadir')
if luadir == 'auto'
    luadir = get_option('datadir') / 'lua'
endif

# TODO: msvc lua module building

lua_modules_suffix = []
if host_machine.system() == 'darwin'
    # lua needs it this way on OSX
    lua_modules_suffix = 'so'
elif host_machine.system() == 'windows'
    # windows nees this too? failed tests complain
    # about missing *.so files
    lua_modules_suffix = 'so'
endif

lua_includes = [ include_directories ('lua') ]
lua_deps = [ lua_dep ]

if lua_system
    lua_deps += []
    lua_version = lua_version
    lua_includes += include_directories (
        'lua/@0@'.format(lua_version))
else
    lua_deps += []
    lua_version = '5.4'
    lua_includes += include_directories (
        'lua/@0@'.format(lua_version))
endif

# place where the LVTK bindings get installed.
lua_cmod_subdir = '@0@/@1@'.format (luadir_c, lua_version)
lua_mod_subdir  = '@0@/@1@'.format (luadir,   lua_version)

lua_c_args = []
lua_cpp_args = []

if host_machine.system() == 'darwin'
    lua_cpp_args += ['-Wno-unknown-warning-option'] # sol2
elif host_machine.system() == 'windows'
    lua_cpp_args += ['-DLUA_BUILD_AS_DLL=1']
    lua_c_args += ['-DLUA_BUILD_AS_DLL=1']
endif

# build low level modules
subdir ('lvtk')

# build high level class Extensions
lua_cpp_sources = ['lvtk.cpp']
shared_module ('lvtk',
    lua_cpp_sources,
    name_prefix: '',
    name_suffix : lua_modules_suffix,
    include_directories : lua_includes,
    cpp_args : [ lua_cpp_args ],
    gnu_symbol_visibility : 'hidden',
    dependencies: [ pugl_cairo_dep, lui_internal_dep, lua_deps, 
                    host_dep, widgets_dep, cairo_dep, 
                    boost_dep ],
    objects : [],
    install : true,
    install_dir : lua_cmod_subdir)
