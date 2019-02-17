function onUpdate(server, dt)
end

function onConnect(server, peer)
  print("Connected")
  api.Send(peer, "Hello, you")
end

function onDisconnect(server, peer)
  print("Disconnected")
  api.SendAll(server, "Goodbye, someone")
end

function onPacket(server, peer, packet)
  local str = api.StrPacket(packet)
  print("Packet", str)
  api.Send(peer, str)
end
