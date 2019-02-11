project('dfgame-grids', 'c',
        version : '0.0.1',
        license : 'MIT',
        default_options : ['c_std=gnu11'])

compiler = meson.get_compiler('c')

pkgconfig = import('pkgconfig')

m = compiler.find_library('m', required : false)
tidy = find_program('clang-tidy', required: false)
gl = dependency('gl')
cunit = dependency('cunit')

dfgame      = subproject('dfgame')
application = dfgame.get_variable('application_game')
core        = dfgame.get_variable('core')
graphics    = dfgame.get_variable('graphics')
math        = dfgame.get_variable('math')
resource    = dfgame.get_variable('resource')
glsl_gen    = dfgame.get_variable('glsl_gen')

args = []
subdir('src')
subdir('test')
subdir('demo')

run_command('ctags', '-R', '.')
