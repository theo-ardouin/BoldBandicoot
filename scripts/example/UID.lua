local UID = {
  id = 0
}

function UID.Next()
  local id = UID.id

  UID.id = UID.id + 1
  return string.format("uid:%d", id)
end

return UID
