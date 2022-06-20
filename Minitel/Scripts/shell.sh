DEVICE=/dev/ttyUSB0
echo 'On the minitel'
echo 'Press FNCT T A'
echo '      FNCT T E'
echo '      FNCT P 4'
bash < $DEVICE > $DEVICE &> $DEVICE
