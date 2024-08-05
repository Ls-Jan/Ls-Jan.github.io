

``call``+``goto``能解决不少问题(倒不如说是绕开)



```bash
@echo off

SET val="XXXXX"
SET val="   "
SET val=%val:~1,-1%

call :EmptyTest %val%
goto :eof

:EmptyTest
if "%1"=="" ( echo Empyt!!! )
```
