# Quantitative Trading & Low-Latency Infrastructure
**Status:** Active Development / Refactoring core C++ engines for public release.

This repository contains the core infrastructure for a high-frequency trading simulation environment, including a custom C++ Limit Order Book, execution agents, and tick-level backtesting frameworks. 

*Note: Several modules are currently undergoing memory-optimization refactoring and parameter tuning. Full code pushes are ongoing.*

---

## 🏗️ Core Architecture Modules

### 1. [order_book/](./order_book) : Limit Order Book & Microstructure Analytics
*(Status: Refactoring C++ memory management and L2 parsing logic)*
* Engineered a low-latency Limit Order Book (LOB) matching engine in C++, utilizing custom doubly-linked lists and hash maps to enforce strict price-time (FIFO) priority.
* Achieves O(1) insertions, cancellations, and partial fill updates.
* **Next Push:** Integrating historical Level 2 tick data parser to reconstruct full market depth and analyze latency-driven slippage.

### 2. [strategy/](./strategy) & [oms/](./oms) : High-Frequency Market Making Engine
*(Status: Tuning Avellaneda-Stoikov risk parameters for out-of-sample testing)*
* Developed a market-making agent designed to operate directly on the simulated LOB to strictly manage inventory risk.
* Implements adverse selection safeguards by calculating real-time Order Flow Imbalance (OFI) to detect toxic flow.
* **Next Push:** Backtest results of quoting logic across varying volatility regimes to balance fill rates against directional exposure.

### 3. [backtester/](./backtester) : Tick-Level Statistical Arbitrage
*(Status: Optimizing memory footprint for high-resolution tick data streams)*
* Built an event-driven pairs trading backtester optimized for tick data, utilizing the Johansen test for robust multivariate cointegration.
* Executes walk-forward optimization and rolling out-of-sample testing to verify mean-reversion stability.
* **Next Push:** Incorporating realistic market friction, transaction costs, and spread-crossing logic.

### 4. [volatility_surface/](./volatility_surface) : Local Volatility Calibration
*(Status: Finalizing Dupire finite difference grids)*
* Constructs a local volatility surface from delayed options data, enforcing strict arbitrage-free conditions.
* Calibrates Dupire's formula using finite differences to extract local volatility grids.
* **Next Push:** Stress-testing boundary breakdowns for short-dated OTM puts.

---
## ⚙️ Tech Stack
* **Core Engine:** C++ (STL, Low-Latency Memory Management)
* **Analytics & Backtesting:** Python, Pandas, SciPy, Statsmodels
* **Focus:** Market Microstructure, O(1) Data Structures, Event-Driven Architecture
