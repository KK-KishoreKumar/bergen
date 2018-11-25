:SetUp
@echo off

:readNotification:	
echo -{ ...
echo -{ Warning: This script will create the Boot Manager for Bergen Operating System 0.1
echo -{ Warning: ...
	pause

    rem
    rem Ordem de montagem:
    rem stage1, stage2, msm, bl, kernel, browser, fat16 stuff and vhd footer.
    rem


    rem cd c:\sdk\bin

:Start 
echo -{ ... 
echo -{ Creating BM.BIN for Bergen Operating System

    rem SET ROOT=C:\gramado\g03\branch\boot\bm\r0001
    rem cd %ROOT%

    nasm -I c:/bergen/programs/bm/stage1/ ^
         -I c:/bergen/programs/bm/stage2/ ^
         -I c:/bergen/programs/bm/stage2/include/ ^
         -I c:/bergen/programs/bm/stage2/lib16/ ^
         -I c:/bergen/programs/bm/stage3/ ^
         -I c:/bergen/programs/bm/stage3/drivers/ ^
         -I c:/bergen/programs/bm/stage3/fs/ ^
         -I c:/bergen/programs/bm/stage3/include/ ^
         -I c:/bergen/programs/bm/stage3/kernel/ ^
         -I c:/bergen/programs/bm/stage3/lib32/ ^
         -I c:/bergen/programs/bm/stage3/shell/  c:/bergen/programs/bm/main.asm  -o  BM.BIN


:Copying
    rem copy BM.BIN ??\BM.BIN 

:End
echo -{ ...
echo -{ End.
	pause


