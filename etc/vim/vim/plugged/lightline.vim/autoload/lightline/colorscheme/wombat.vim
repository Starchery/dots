" =============================================================================
" Filename: autoload/lightline/colorscheme/wombat.vim
" Author: itchyny
" License: MIT License
" Last Change: 2015/11/30 08:37:43.
" =============================================================================
" idk
let s:base03 = [ '#1f1d1d', 16 ]
" idk
let s:base023 = [ '#353535 ', 236 ]
" middle bg and first fg?
let s:base02 = [ '#444444 ', 0 ]
" filename bg
let s:base01 = [ '#585858', 236 ]
" idk
let s:base00 = [ '#666666', 7  ]
" rightmost
let s:base0 = [ '#808080', 3 ]
" percent text
let s:base1 = [ '#969696', 247 ]
" encoding text
let s:base2 = [ '#a8a8a8', 248 ]
" filename fg
let s:base3 = [ '#d0d0d0', 252 ]
let s:yellow = [ '#cae682', 180 ]
let s:orange = [ '#e5786d', 173 ]
let s:red = [ '#e5786d', 2 ]
let s:magenta = [ '#f2c68a', 2 ]
let s:blue = [ '#8ac6f2', 3 ]
let s:cyan = s:blue
let s:green = [ '#95e454', 1 ]
let s:p = {'normal': {}, 'inactive': {}, 'insert': {}, 'replace': {}, 'visual': {}, 'tabline': {}}
let s:p.normal.left = [ [ s:base02, s:blue ], [ s:base2, s:base01 ] ]
let s:p.normal.right = [ [ s:base02, s:base0 ], [ s:base1, s:base01 ] ]
let s:p.inactive.right = [ [ s:base023, s:base01 ], [ s:base00, s:base02 ] ]
let s:p.inactive.left =  [ [ s:base1, s:base02 ], [ s:base00, s:base023 ] ]
let s:p.insert.left = [ [ s:base02, s:green ], [ s:base2, s:base01 ] ]
let s:p.replace.left = [ [ s:base00, s:red ], [ s:base2, s:base01 ] ]
let s:p.visual.left = [ [ s:base00, s:magenta ], [ s:base2, s:base01 ] ]
let s:p.normal.middle = [ [ s:base2, s:base02 ] ]
let s:p.inactive.middle = [ [ s:base1, s:base023 ] ]
let s:p.tabline.left = [ [ s:base3, s:base00 ] ]
let s:p.tabline.tabsel = [ [ s:base3, s:base03 ] ]
let s:p.tabline.middle = [ [ s:base2, s:base02 ] ]
let s:p.tabline.right = [ [ s:base2, s:base00 ] ]
let s:p.normal.error = [ [ s:base03, s:red ] ]
let s:p.normal.warning = [ [ s:base023, s:yellow ] ]

let g:lightline#colorscheme#wombat#palette = lightline#colorscheme#flatten(s:p)
