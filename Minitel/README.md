Information, electronics and software for the French Minitel system
===================================================================

Minitel as a terminal
---------------------

(See reference 7).

Step 1: install terminal info for minitel

```
  $ wget http://canal.chez.com/mntl.ti
  $ sudo tic mntl.ti -o /etc/terminfo
```

Step 2: 
```
  $ sudo agetty -c ttyUSB0 4800 m1b-x80
```

Step 3: on the minitel
- `FNCT` `T` `A`
- `FNCT` `T` `E`
- `FNCT` `P` `4`

Nearly usable (but `<CTRL>` key does not seem to work...).


Display videotext graphics on the Minitel
-----------------------------------------

Step 1:
```
  $ cd Scripts
  $ sudo minitel.sh
```

Step 2: on the minitel
- `FNCT` `T` `E`
- `FNCT` `P` `4`

Step 3: 
```
  $ cd ../Software
  $ make
  $ ./MinitelDemo > /dev/ttyUSB0
```

Links
-----

- [1](https://jbellue.github.io/stum1b/#0-1)
- [2](http://hxc2001.free.fr/minitel/index.html)
- [3](https://blog.typogabor.com/2007/10/28/dada-le-minitel-bien-involontairement-oui/)
- [4](https://www.goto10.fr/minitel/divers/codeurs-en-seine-minitel.pdf)
- [5](https://archive.softwareheritage.org/browse/origin/directory/?origin_url=https://github.com/01010101/Minitel/)
- [6](https://info.blaisepascal.fr/3615-tuveuxmaphoto)
- [7](https://arduiblog.com/2019/04/29/ressuscitez-le-minitel/)
