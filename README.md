# SLED1: Santa’s Latest Electronic Delivery system

## SCC.110 Software Development – Problem Set 9: Assessed Exercise

### 🎄 Project Overview

This program simulates **SLED1 (Santa’s Latest Electronic Delivery system)**, a drone developed to help Santa deliver parcels more efficiently during Christmas. It reads a `map.txt` file that defines the terrain, and a `sledcommands.txt` file that contains movement instructions. The drone then moves across the map accordingly, updating its state and reporting status information.

---

### 📁 Files

- `SLED1.c`: Main source code.
- `map.txt`: Defines the 30x30 map with symbols for different locations (e.g., house, factory, park).
- `sledcommands.txt`: A list of movement instructions for SLED1.

---

### 🔧 Compilation

Use `gcc` or another standard C compiler:

```bash
gcc -o sled SLED1.c
```

---

### ▶️ Running the Program

Ensure that `map.txt` and `sledcommands.txt` are located in the **same directory** as the compiled executable. Then run:

```bash
./sled
```

---

### 🗺 Map File Format (`map.txt`)

Each line represents a location on the 30x30 map:

```
x,y,symbol
```

Where:
- `x`, `y` are integers (0 ≤ x, y ≤ 29)
- `symbol` is a character:  
  - `.` (empty)  
  - `P` (parkland)  
  - `S` (street)  
  - `H` (house)  
  - `T` (tower)  
  - `F` (factory)  
  - `U` (university)

**Example:**
```
0,0,H
0,4,U
4,4,F
```

---

### 📜 Command File Format (`sledcommands.txt`)

Each line contains a command and an integer value:

```
FORWARD n
TURN n
```

Where:
- `FORWARD n`: Moves SLED1 `n` spaces in the current direction.
- `TURN n`: Turns SLED1 clockwise by `n` degrees (`0`, `90`, `180`, or `270` only).

**Example:**
```
FORWARD 9
TURN 90
FORWARD 9
```

---

### 🧱 SLED1 Structure

SLED1's status is stored in this structure:

```c
struct sled {
    int x, y;
    int orientation;     // 0 = North, 90 = East, 180 = South, 270 = West
    int totalDistance;   // total squares moved
};
```

Initial status:
- Location: `(0,0)`
- Orientation: `0` (North)
- Distance: `0`

---

### ✅ Functionality Overview

- `initialise_map(char map[30][30])`  
  Initializes all positions in the map with `.`

- `populate_map(FILE *fp, char map[30][30])`  
  Populates the map from `map.txt`

- `print_map(char map[30][30])`  
  Prints the map with `(0,0)` in the bottom-left corner

- `int process_command(FILE *fp, char map[30][30], struct sled *s)`  
  Executes all commands from `sledcommands.txt`

- `void print_sled(struct sled s)`  
  Prints the current sled status

- `void print_symbol(char map[30][30], struct sled s)`  
  Prints the symbol at the sled's current location

---

### 🧪 Sample Output

```
sled status:
location 5,6
orientation 0 degrees
distance travelled 25 squares
end sled status.

sled is flying over symbol H
```
