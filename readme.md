# Deribit Trading System

A high-performance C++ trading application for interacting with the Deribit cryptocurrency exchange.

## Overview

This system provides a robust trading interface for the Deribit exchange with the following key features:
- Real-time WebSocket communication
- Multi-threaded execution
- Built-in latency monitoring
- Order management capabilities
- Position tracking

## System Components

### 1. Trading Logic (`trade.cpp`)
- Order placement and management
- Order book monitoring
- Position tracking
- Interactive trading menu interface

### 2. WebSocket Handler (`websocket.cpp`)
- Real-time communication with Deribit
- Message sending and receiving
- Connection management

### 3. Latency Module (`latency.cpp`)
- High-precision latency measurements
- Microsecond-level accuracy
- Performance monitoring for operations

### 4. Thread Pool (`threads.cpp`)
- Concurrent operation handling
- Task queuing and execution
- Resource management

## Technical Details

### Dependencies
- Boost libraries (system, thread)
- OpenSSL
- nlohmann/json for JSON handling
- C++17 standard library

### Building the Project
```bash
mkdir build
cd build
cmake ..
make
```

### Performance

The system includes a high-resolution latency monitoring system that:
- Measures operation durations in microseconds
- Provides millisecond-precision output
- Tracks individual operation latencies

## Trading Features

1. Order Management
   - Place new orders
   - Cancel existing orders
   - Modify order parameters
   - View order book data

2. Position Management
   - Real-time position tracking
   - Current position view
   - Position monitoring

## Usage

After building, run the TradingApp executable:
```bash
./TradingApp
```

The interactive menu provides the following options:
1. Place Order
2. Cancel Order
3. Modify Order
4. Get Order Book
5. View Current Positions
6. Exit

## Technical Architecture

The system uses a multi-layered architecture:
1. User Interface Layer (Trading Menu)
2. Business Logic Layer (Trading Logic)
3. Communication Layer (WebSocket)
4. Performance Monitoring Layer (Latency Module)
5. Concurrency Layer (Thread Pool)

## Future Improvements

Potential areas for optimization:
1. Advanced order types implementation
2. Market data caching
3. Risk management features
4. Trading strategy integration
5. Enhanced error handling and recovery
6. Performance optimization for high-frequency trading

## Performance Monitoring

The latency module provides real-time performance metrics for:
- Order execution time
- WebSocket message latency
- System operation durations

### Latency Benchmarks

Initial benchmarking results from test runs:

1. WebSocket Operations:
   - Message Read Latency: 175-185ms average
   - Authentication Response: ~0.308ms server processing time
   - Order Placement Processing: ~1.86ms server-side processing

These measurements were taken on the Deribit testnet environment. Production environment latencies may vary based on network conditions and server load.

Key Performance Indicators:
- WebSocket connection establishment: Sub-second
- Message round-trip time: Under 200ms
- Server-side processing: 1-2ms range

### Bottleneck Analysis

Current identified bottlenecks:
1. Network latency (primary factor in WebSocket operations)
2. Message serialization/deserialization time
3. Authentication overhead on connection establishment

### Optimization Opportunities

Based on the benchmarking results, potential optimizations include:
1. Connection pooling for reduced authentication overhead
2. Message batching for multiple operations
3. Local order book caching to reduce network requests
4. Optimized JSON parsing for high-frequency operations

Note: These benchmarks represent initial testing. Continuous monitoring and optimization will be performed based on real-world usage patterns.