# LAM-Research-Challenge

## Precise Dispensing and Segregation System

### Overview
This project introduces a cost-effective, precision liquid dispensing system that utilizes a peristaltic pump and servo-driven pinch valves for non-contact liquid handling. Designed for applications requiring high accuracy and contamination-free handling, this system segregates red and blue solutions and dispenses them with exceptional precision.

---

### System Description

#### 1. Reservoirs and Pinch Valves
- Two reservoirs hold red and blue solutions, controlled by servo-driven pinch valves.
- Pinch valves are connected to a T-connector leading to the peristaltic pump.

#### 2. Dispensing Mechanism
- A peristaltic pump directs the liquid into containers placed on a load cell pedestal.
- The load cell measures the dispensed weight, automatically taring the initial container weight.
- Dispensed weights are displayed on an I2C OLED Display.

#### 3. Anti-Mixing Mechanism
- Residual solutions are intelligently moved back to their respective reservoirs after dispensing, preventing cross-contamination.

#### 4. Segregation and Storage
- A linear actuator alternates between the two vessels or the spout, ensuring proper segregation and dispensing for five cycles.

---

### Project Images
| <img src="https://github.com/user-attachments/assets/e9632c0a-0aed-455c-ad33-aed2e7522740" width="500" height="500" /> | <img src="https://github.com/user-attachments/assets/26ca9f2c-8a38-4e5b-a93d-3d420375ea28" width="500" height="500" /> |
| :-------------------------------------------------------------------------------------------: | :-----------------------------------------------------------------------------------------------: |

### Project Video
[![Project Video](https://img.youtube.com/vi/de52cf5e-987c-410b-9c9e-fc585f40a9df/0.jpg)](https://github.com/user-attachments/assets/de52cf5e-987c-410b-9c9e-fc585f40a9df)



