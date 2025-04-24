this a trading bot for test.deribit, it will use the deribit api
major actions:  place order, cancel, modifym, see orderbook, see current position

will use multi-threading with thread pool and conditional dynamic thread generation to avoid latency bottleneck of constant thread generation for every action.

will try to make a gui for this

focus is on performance and low-latency