let g:syntastic_cpp_compiler = "g++"
let g:syntastic_cpp_compiler_options = "-std=c++17 -Wconversion -pedantic -lglut -lGL -lGLU -lGLEW"
let NERDTreeIgnore = ['\.o$']
nnoremap <c-w>D :ConqueGdb<CR><Esc><C-W>J<C-W>500-<C-W>5+:set wfh<CR>ifile run_game<CR>
