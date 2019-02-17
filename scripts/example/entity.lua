local Point = require("scripts.example.point")
local Packets = require("scripts.example.packets")

local Entity = {}

function Entity.new(uid, pos, peer)
  return setmetatable({
    uid = uid,
    pos = Point.new(pos.x, pos.y),
    peer = peer,
    hasMoved = false,
    destroyed = false,
    world = nil
  }, {
    __index = Entity
  })
end

function Entity:update(dt)
  if self.world and self.hasMoved then
    self.world:send(Packets.Move(self), function(entity)
      return entity ~= self
    end)
    self.hasMoved = false
  end
end

function Entity:destroy()
  self.destroyed = true
  if self.world then
    self:onDestroy()
  end
end

function Entity:onSpawn()
end

function Entity:onDestroy()
end

return Entity
