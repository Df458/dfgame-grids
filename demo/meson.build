demodeps = [ application, core, graphics, grids, math, resource ]
demosrc  = [ 'main.c' ]
demoexe  = executable('demo_grids', demosrc,
                       dependencies : demodeps,
                       link_args : args,
                       install : false)

run_command('ctags', '-R', '.')
run_command('ln', '-rs', 'assets', '../build/demo')
