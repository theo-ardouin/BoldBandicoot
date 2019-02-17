local Point = {}

function Point.new(x, y)
  return setmetatable({
    x = x,
    y = y
  }, {
    __index = Point,
    __tostring = Point.toString
  })
end

function Point:getAngle(point)
  return math.atan2(point.y - self.y, point.x - self.x)
end

function Point:getDistance(point)
  return math.sqrt((self.x - point.x) ^ 2 + (self.y - point.y) ^ 2)
end

function Point:toString()
  return string.format("Point(%.2f, %.2f)", self.x, self.y)
end

return Point
