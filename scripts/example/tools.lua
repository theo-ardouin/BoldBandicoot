local Tools = {}

function Tools.Split(str, separator)
  local t = {}
  separator = separator or "%s"
  for s in string.gmatch(str, "([^" .. separator .. "]+)") do
    table.insert(t, s)
  end
  return t
end

function Tools.Has(t, value)
  for _, val in pairs(t) do
    if val == value then
      return true
    end
  end
  return false
end

return Tools
