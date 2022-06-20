DEVICE=/dev/ttyUSB0
stty -F $DEVICE 4800 istrip cs7 parenb -parodd brkint \
ignpar icrnl ixon ixany opost onlcr cread hupcl isig icanon \
echo echoe echok
chmod 777 $DEVICE
