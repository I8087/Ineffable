@echo off
%tcc%\tcc -o ineffable.exe src/ineffable.c src/ineffable_lexer.c src/ineffable_lexerRPN.c src/ineffable_parser.c src/ineffable_assembler.c src/ineffable_vm.c DA\da.c -IDA
pause
