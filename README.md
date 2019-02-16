# Server

Multi-purpose server using Lua as scripting engine and enet as network layer

# Installation

## Enet
```
$ git clone git@github.com:lsalzman/enet.git
$ cd enet
$ sudo apt-gen install autogen autoconf libtool
$ autoreconf -vfi
$ ./configure && make && sudo make install
```
[Reference](http://enet.bespin.org/Installation.html)

## Lua
```
$ curl -R -O http://www.lua.org/ftp/lua-5.2.4.tar.gz
$ tar -xf lua-5.2.4.tar.gz
$ cd lua-5.2.4
$ make linux && sudo make install
```
[Reference](https://www.lua.org/manual/5.2/readme.html)
