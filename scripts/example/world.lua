local Tools = require("scripts.example.tools")

local World = {}

function World.new()
  return setmetatable({
    entities = {},
    elapsed = 0
  }, {
    __index = World
  })
end

function World:add(entity)
  if entity then
    entity.world = self
    self.entities[entity.uid] = entity
  end
  return entity
end

function World:remove(entity)
  if entity then
    entity.world = self
    self.entities[entity.uid] = nil
  end
end

function World:update(dt)
  self.elapsed = self.elapsed + dt
  for _, entity in pairs(self.entities) do
    entity:update(dt)
  end
end

function World:send(packet, predicate)
  predicate = predicate or function()end
  for _, entity in pairs(self.entities) do
    if entity.peer and predicate(entity) then
      api.Send(entity.peer, packet)
    end
  end
end

function World:find(predicate)
  for _, entity in pairs(self.entities) do
    if predicate(entity) then
      return entity
    end
  end
  return nil
end

function World:byPeer(peer)
  return self:find(function(entity)
    return entity.peer == peer
  end)
end

return World
