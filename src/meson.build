deps = [ core, graphics, math ]
src  = [
    'grid.c',
    'shapes.c',
]
lib = static_library('dfgame_grids', src,
                         dependencies : deps,
                         link_args : args,
                         install : true)

pkgconfig.generate(libraries : lib,
                    version : '0.1.0',
                    name : 'dfgame-grids',
                    filebase : 'dfgame-grids',
                    extra_cflags : [ '-I${prefix}/include/dfgame/grids' ],
                    requires : ['libxml-2.0', 'dfgame-core', 'dfgame-graphics', 'dfgame-math'],
                    libraries : ['-ldfgame_grids'],
                    description : 'dfgame grids module, provides grid utility functions')

install_headers([
  'grid.h',
], subdir : 'dfgame/grids')

grids = declare_dependency(include_directories : include_directories('.'), link_with : lib)

if tidy.found()
    run_target(
        'tidy-grids',
        command: [
            tidy,
            '-checks=*',
            '-p', meson.build_root()
        ] + src)
endif
