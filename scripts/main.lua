function onUpdate(server, dt)
end

function onConnect(server, peer)
  print("Connected")
end

function onDisconnect(server, peer)
  print("Disconnected")
end

function onPacket(server, peer, packet)
  local str = api.StrPacket(packet)
  print("Packet", str)
  api.Send(peer, str)
end
