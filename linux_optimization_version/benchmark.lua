-- require('mobdebug').start("192.168.56.1")


local statsd = require "statsd"
require "socket"
local s = statsd.metric:new {name= "testing_metric"}

--[[
s:starttimer()
socket.select(nil, nil, 3)
s:stoptimer()

s:starttimer()
socket.select(nil, nil, 1)
s:stoptimer()

s:starttimer()
socket.select(nil, nil, 0.01)
s:stoptimer()

s:starttimer()
socket.select(nil, nil, 0.05)
s:stoptimer()

s:starttimer()
socket.select(nil, nil, 0.34)
s:stoptimer()

s:starttimer()
socket.select(nil, nil, 0.123)
s:stoptimer()

s:starttimer()
socket.select(nil, nil, 0.876)
s:stoptimer()

socket.select(nil, nil, 10)

s:starttimer()
s:stoptimer()
--]]


local i = 1
local t0 = socket.gettime()

for i =1, 10000000 do
  local t0 = s:starttimer()
  s:stoptimer(t0)
end

local t1 = socket.gettime()
require "math"
local duration = math.floor((t1-t0)*1000)
print(" used time: ".. duration .."ms")



