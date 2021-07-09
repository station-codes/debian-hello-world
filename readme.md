# getting started

## freedomboxalarm


### build

> $ sudo dpkg-buildpackage -b

### install

> $ sudo dpkg -i ../freedombox_1.0-1_all.deb 
  $ sudo dpkg --install ../*.deb

 $ sudo dpkg --list
 $ sudo dpkg --remove <package>

#### ftdi lib (for build)

> $ sudo apt-get install libftdi1

> $ dpkg -L libftdi1-dev
