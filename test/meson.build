test_grids_src = [
    'main.c',

    'test_shapes.c',
]
test_grids = executable('test_grids', test_grids_src, include_directories : include_directories('../src'), dependencies : [ cunit, deps ], link_with : [ lib ])
test('Grid module tests', test_grids)
