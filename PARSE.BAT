@echo off
Bison\bin\yacc.exe -y -d -v yacc_syntax.y
Flex\bin\lex.exe flex_tokens.l
gcc main.c lex.yy.c y.tab.c alloc_wrap.c ast.c string_tools.c typedef_name.c -o c_parser.exe
set /p in="Enter input filename (leave empty for `stdin'): "
c_parser.exe %in% out.txt
rm c_parser.exe
pause