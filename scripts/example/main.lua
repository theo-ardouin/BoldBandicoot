local UID = require("UID")
local Tools = require("tools")
local World = require("world")
local Entity = require("entity")
local Packets = require("packets")

local _world = World.new()
local _packets = {
  move = function(server, peer, t)
    local entity = _world.entities[t[2]]
    entity.pos.x = tonumber(t[3])
    entity.pos.y = tonumber(t[4])
    entity.hasMoved = true
  end
}

function onUpdate(server, dt)
  _world:update(dt)
end

function onConnect(server, peer)
  for _, worldEntity in pairs(_world.entities) do
    api.Send(peer, Packets.Entity(worldEntity))
  end

  local entity = _world:add(Entity.new(UID.Next(), {x = 0.5, y = 0.5}, peer))
  api.SendAll(server, Packets.Entity(entity))
  api.Send(peer, Packets.Me(entity))
end

function onDisconnect(server, peer)
  local entity = _world:byPeer(peer)
  if entity then
    api.SendAll(server, Packets.Remove(entity))
    _world:remove(entity)
  end
end

function onPacket(server, peer, packet)
  local t = Tools.Split(api.StrPacket(packet))
  local execute = _packets[t[1]]
  if execute then
    local success, err = pcall(execute, server, peer, t)
    if not success then
      print(err)
    end
  else
    print("Unknown packet", api.StrPacket(packet))
  end
end
