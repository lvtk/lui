

foreach n : 'import object'.split()
    configure_file (
        input       : '@0@.lua'.format(n),
        output      : '@0@.lua'.format(n),
        copy        : true,
        install     : true,
        install_dir : lua_mod_subdir / 'lvtk'
    )
endforeach

foreach n : 'bytes midi round'.split()
    shared_module (n, [ '@0@.c'.format(n) ],
        name_prefix             : '',
        name_suffix             : lua_modules_suffix,
        include_directories     : [ lua_includes ],
        gnu_symbol_visibility   : 'hidden',
        dependencies            : [ lui_internal_dep, lua_deps ],
        c_args                  : [ lua_c_args ],
        install                 : true,
        install_dir             : lua_cmod_subdir / 'lvtk')
endforeach
