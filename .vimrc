let g:syntastic_cpp_compiler = "g++"
let g:syntastic_cpp_compiler_options = "-std=c++17 -Wconversion -Wall -Wextra -pedantic -g3 -DRUNTESTS -lglut -lGL -lGLU -lGLEW -Isrc/ -Isrc/frame_buffer"
let NERDTreeIgnore = ['\.o$', '\.d$']
let g:syntastic_cpp_config_file = '.include_dirs'
let g:syntastic_cpp_check_header = 1
nnoremap <c-w>D :ConqueGdb<CR><Esc><C-W>J<C-W>500-<C-W>5+:set wfh<CR>ifile run_game<CR>
nnoremap <F2> gT:silent! wa<CR>:terminal ++close ./stall_if_error "make -j all"<CR><C-W>T
nnoremap <F3> gT:silent! wa<CR>:terminal ++close ./stall_if_error "make -j test"<CR><C-W>T
