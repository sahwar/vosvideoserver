echo on
IF NOT EXIST %1Release mkdir %1Release
IF NOT EXIST %1Release\PocoFoundation.dll copy %THIRDPARTY_ROOT%\poco-1.4.7p1\lib\PocoFoundation.dll %1Release