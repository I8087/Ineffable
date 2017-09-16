@echo off
%tcc%\tcc -o ineffable.exe ineffable.c ineffable_lexer.c ineffable_parser.c DA\da.c -IDA
pause
