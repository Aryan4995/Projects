# Quantitative Trading & Low-Latency Infrastructure

**Status:** Active Development (Phase 3: Execution Algorithms)

This repository contains the ongoing construction of a high-frequency trading simulation environment. The architecture is designed to be highly modular, separating heavy C++ computation (matching engine) from algorithmic execution and risk management.

Currently, the core foundation (the Limit Order Book) and initial execution algorithms (TWAP) are deployed, and we are systematically building out the surrounding microservices.

## 🟢 Deployed Modules

### 1. `order_book/` (Core Matching Engine & Data Logger)
* **Status:** Fully Operational
* Engineered a low-latency Limit Order Book (LOB) matching engine in C++.
* Utilizes custom doubly-linked lists and hash maps (`std::map`, `std::list`) to enforce strict price-time (FIFO) priority.
* Achieves O(1) insertions, cancellations, and partial fill updates.
* **Data Pipeline:** Features a custom C++ data logger (`Logger.h`) that outputs real-time execution data (`trades.csv`) matching standard Binance historical tick data formats.

### 2. `strategy/` (Algorithmic Execution)
* **Status:** Active (Simulating inside the C++ Engine)
* Developing institutional execution algorithms to minimize market impact.
* **Current Focus:** Time-Weighted Average Price (TWAP) bots designed to slice large block orders and hide footprints from predatory liquidity takers, contrasting against high-slippage "Whale" market orders.

## 🚧 Development Roadmap (Architecture Initialized)

The following modules have been architected into the repository structure and are actively undergoing development:

* **`oms/` (Order Management System):** Will track order lifecycles (New, Partially Filled, Filled, Canceled) asynchronously.
* **`event_engine/`:** The backbone message bus to route market data events between the strategies and the LOB.
* **`risk_manager/`:** A pre-trade risk layer to intercept toxic flow and enforce inventory limits.
* **`backtester/` & `monte_carlo/`:** Python-based quantitative analytics modules optimized for ingesting the high-resolution tick data (`trades.csv`) produced by the C++ engine.
* **`data/` & `replay/`:** Pipelines to ingest historical Level 2 market depth data.
* **`volatility_surface/`:** Local volatility calibration grids for options pricing.

## ⚙️ Tech Stack
* **Core Execution Engine:** C++17 (STL, Low-Latency Memory Management)
* **Target Analytics Stack:** Python, Pandas, Matplotlib
* **Design Focus:** Market Microstructure, O(1) Data Structures, Algorithmic Execution