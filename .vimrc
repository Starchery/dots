set nocompatible
set nu rnu
set hlsearch
set incsearch
set ignorecase smartcase
"set noshowmode
"set laststatus=2
set t_Co=256

call plug#begin('~/.vim/plugged')
" Plug 'itchyny/lightline.vim'
Plug 'dylanaraps/wal.vim'
call plug#end()

colorscheme wal
" let g:lightline = {'colorscheme': 'tomorrow'}
colorscheme wal
" let g:lightline = {'colorscheme': 'wombat'}

