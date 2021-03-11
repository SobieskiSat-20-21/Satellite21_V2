C:\Users\jskup\Desktop\Electronics\stm32\dfu-util\dfu-util.exe -a 0 -s 0x08000000:leave -D C:\Users\jskup\Desktop\CanSat\GitHub\Satellite21_V2\build\Satellite21_V2.bin
ping -n 2 127.0.0.1 >nul
putty -serial COM18