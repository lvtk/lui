
## REUSE test
if reuse_program.found()
  test('REUSE', reuse_program, 
    args: [ '--root', meson.project_source_root(), 'lint' ], 
    suite: 'metadata')
endif

if boost_dep.found()

## Unit Tests
unit_test_sources = '''
    observer_test.cpp
    string_test.cpp
    weak_ref_test.cpp
    ui_font_test.cpp
    main_unit.cpp
'''.split()

unit = executable ('lui-unit',
    unit_test_sources,
    dependencies : [ boost_dep, lui_internal_dep, widgets_dep, lilv_dep ],
    gnu_symbol_visibility : 'hidden',
    cpp_args : ['-DLUI_NO_SYMBOL_EXPORT'])

unit_tests = '''
    Font
    Observer
    String
    WeakRef
'''.split()


foreach t : unit_tests
    test (t, unit, args : [ '-t', t ],
        env : [
            'LV2_PATH=@0@'.format (meson.project_build_root())
        ]
    )
endforeach

if not get_option('bindings').disabled()
    # subdir ('lua')
endif

endif
