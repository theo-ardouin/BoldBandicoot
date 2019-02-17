local Packets = {}

function Packets.Entity(entity)
  return string.format("entity %s %f %f", entity.uid, entity.pos.x, entity.pos.y)
end

function Packets.Me(entity)
  return string.format("me %s", entity.uid)
end

function Packets.Move(entity)
  return string.format("move %s %f %f", entity.uid, entity.pos.x, entity.pos.y)
end

function Packets.Remove(entity)
  return string.format("remove %s", entity.uid)
end

return Packets
