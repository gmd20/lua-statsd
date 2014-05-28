lua-statsd
==========

A Lua module to send statistics to Graphite， a clone of [Statsd](https://github.com/etsy/statsd)

说明
-----
用Lua代码实现了类似[Statsd](https://github.com/etsy/statsd)的功能，可以记录counter和timer统计信息，然后通过UDP接口发送给Graphite。可用作程序的监控或者统计接口。在Graphite中可以图形查看统计情况。


使用例子
--------
```lua

local statsd = require "statsd"
require "socket"
local s = statsd.metric:new {name= "testing_metric"}


s:starttimer()
socket.select(nil, nil, 1)
s:stoptimer()

s:starttimer()
socket.select(nil, nil, 0.01)
s:stoptimer()

s:starttimer()
socket.select(nil, nil, 0.876)
s:stoptimer()

socket.select(nil, nil, 10)

s:starttimer()
s:stoptimer()



local i = 1
local t0 = socket.gettime()

for i =1, 10000000 do
  s:starttimer()
  s:stoptimer()
end

local t1 = socket.gettime()
require "math"
local duration = math.floor((t1-t0)*1000)
print(" used time: ".. duration .."ms")

```


windows平台的优化
=================
自己用C++的std::sort替换掉table.sort之后，快了很多。再用自己实现的gettime替换掉socket.gettime()之后性能提高了6倍左右。  
优化之后，运行 10000000 次  starttimer() stoptimer()总共消耗时间880毫秒左右。  
对应代码在 windows_optimization_version  目录下






类似或者相关项目
----------------
1. [Statsd](https://github.com/etsy/statsd)
2. [lua-statsd-client](https://github.com/stvp/lua-statsd-client)
3. [lua-statsd](https://github.com/cwarden/lua-statsd)


查看直方图（histogram）
-----------------------

```
http://localhost:9000/render/?height=300&
width=740&from=-24h&title=Render time histogram&
vtitle=relative frequency in %&yMax=100&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_0_01,stats.timers.render_time.count),100),'2FFF00'),'0.01')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_0_05,stats.timers.render_time.count),100),'64DD0E'),'0.05')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_0_1,stats.timers.render_time.count),100),'9CDD0E'),'0.1')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_0_5,stats.timers.render_time.count),100),'DDCC0E'),'0.5')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_1,stats.timers.render_time.count),100),'DDB70E'),'1')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_5,stats.timers.render_time.count),100),'FF6200'),'5')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_10,stats.timers.render_time.count),100),'FF3C00'),'10')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_50,stats.timers.render_time.count),100),'FF1E00'),'50')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_inf,stats.timers.render_time.count),100),'FF0000'),'inf')&
lineMode=slope&areaMode=stacked&drawNullAsZero=false&hideLegend=false
```

```
http://localhost:9000/render/?height=300&
width=740&from=-24h&title=Render time histogram&
vtitle=relative frequency in %, leaving out first class&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_0_05,stats.timers.render_time.count),100),'64DD0E'),'0.05')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_0_1,stats.timers.render_time.count),100),'9CDD0E'),'0.1')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_0_5,stats.timers.render_time.count),100),'DDCC0E'),'0.5')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_1,stats.timers.render_time.count),100),'DDB70E'),'1')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_5,stats.timers.render_time.count),100),'FF6200'),'5')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_10,stats.timers.render_time.count),100),'FF3C00'),'10')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_50,stats.timers.render_time.count),100),'FF1E00'),'50')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_inf,stats.timers.render_time.count),100),'FF0000'),'inf')&
lineMode=slope&areaMode=stacked&drawNullAsZero=false&hideLegend=false
```

```
http://localhost:9000/render/?height=300&
width=740&from=-24h&title=Render time histogram&
vtitle=rel. freq with scale adjustment per band&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_0_01,stats.timers.render_time.count),0.01),'2FFF00'),'0.01')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_0_05,stats.timers.render_time.count),0.04),'64DD0E'),'0.05')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_0_1,stats.timers.render_time.count),0.05),'9CDD0E'),'0.1')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_0_5,stats.timers.render_time.count),0.4),'DDCC0E'),'0.5')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_1,stats.timers.render_time.count),0.5),'DDB70E'),'1')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_5,stats.timers.render_time.count),4),'FF6200'),'5')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_10,stats.timers.render_time.count),5),'FF3C00'),'10')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_50,stats.timers.render_time.count),40),'FF1E00'),'50')&
target=alias(color(scale(divideSeries(stats.timers.render_time.bin_inf,stats.timers.render_time.count),60),'FF0000'),'inf')&
lineMode=slope&areaMode=stacked&drawNullAsZero=false&hideLegend=false
```

可以使用上面这几个Graphite的render接口调用，视图稍微有点不同，参考
http://dieter.plaetinck.be/histogram-statsd-graphing-over-time-with-graphite.html
