# BoldBandicoot

BoldBandicoot is a multi-purpose server using Lua as scripting engine and ENet as network layer

# How to use

```
make && ./server.out

Usage: server.out [script=<script>] [port=<port>] [tickrate=<tickrate>] [timeout=<timeout>]
  script    Server's Lua script path: Must be the entry point
  port      Server's port
  tickrate  Server's update frequency in seconds
  timeout   Server's network timeout in seconds
```


# Scripting

## API
`api.Send(peer:lightuserdata, message:string) -> void`
> Sends a message to a peer

`api.SendAll(server:lightuserdata, message:string) -> void`
> Broadcasts a message:string to all the connected peers

`api.StrPacket(packet:lightuserdata) -> string`
> Retreives the packet's content as a string

`api.Disconnect(peer:lightuserdata, reason:number) -> void`
> Disconnects a peer

`api.ForceDisconnect(peer:lightuserdata) -> void`
> Forces to disconnect a peer

## Entry points
```
onUpdate(server:lightuserdata, dt:number) -> void
onConnect(server:lightuserdata, peer:lightuserdata) -> void
onDisconnect(server:lightuserdata, peer:lightuserdata) -> void
onPacket(server:lightuserdata, peer:lightuserdata, packet:lightuserdata) -> void
```

# Requirements

## ENet
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

## pthread
