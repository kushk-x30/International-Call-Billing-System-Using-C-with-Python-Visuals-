# 📞 International Call Billing System

A C-based international call billing manager with integrated Python data visualization. The system lets you track, manage, and analyze customer call data through a terminal menu, and generates Matplotlib charts for usage and revenue insights.

> **Made by Group-12** | Languages: C · Python

---

## 📁 Project Structure

```
├── billing_system.c       # Core C program — all billing logic & menu
├── analyze_customers.py   # Python script — Pandas + Matplotlib charts
└── customers.csv          # Auto-generated data file (created on Save)
```

---

## ⚙️ Features

### C Billing System (`billing_system.c`)
- **Add Customer** — Enter name, international phone number, and call usage in minutes; bill is auto-calculated based on country code
- **View All Customers** — Tabular display with name, phone, usage, bill (Rs), and user type
- **Search Customer** — Lookup by phone number
- **Modify Record** — Update a customer's usage and recalculate bill (with confirmation)
- **Delete Record** — Remove a customer entry (with confirmation)
- **Save to CSV** — Exports all records to `customers.csv`
- **Show Graph** — Saves CSV then launches the Python visualization script
- **Show Statistics** — Displays total customers, average usage, average bill, and top customer
- **Sort Customers** — Sort by Name (A–Z) or Usage (High to Low) using `qsort`
- **Export Single Customer** — Saves one customer's details to a `.txt` file

### Python Visualization (`analyze_customers.py`)
- **Bar Chart** — Customer count per user type (Very Low / Low / Moderate / High / Very High)
- **Pie Chart** — Revenue share (in Rs) broken down by user type

---

## 🌐 International Call Rates

| Country Code | Country       | Rate (Rs/min) |
|--------------|---------------|---------------|
| `+91`        | India         | 0.10          |
| `+1`         | USA / Canada  | 7.00          |
| `+44`        | UK            | 8.50          |
| `+61`        | Australia     | 9.00          |
| `+81`        | Japan         | 10.00         |
| `+49`        | Germany       | 8.00          |
| Other        | Default       | 12.00         |

---

## 👤 User Type Classification

| Usage (minutes) | User Type  |
|-----------------|------------|
| < 100           | Very Low   |
| 100 – 300       | Low        |
| 301 – 500       | Moderate   |
| 501 – 1000      | High       |
| > 1000          | Very High  |

---

## 🚀 How to Run

### Prerequisites
- GCC compiler
- Python 3.x with `pandas` and `matplotlib`

```bash
pip install pandas matplotlib
```

### Compile & Run the C Program

```bash
gcc billing_system.c -o billing_system
./billing_system        # Linux / macOS
billing_system.exe      # Windows
```

### Run the Python Visualizer Separately (optional)

```bash
python analyze_customers.py
```

> **Note:** Make sure `customers.csv` exists (use menu option **6 – Save to CSV** first) before running the visualizer, or select option **7 – Show Graph** directly from the menu which saves and launches it automatically.

---

## 📋 Phone Number Format

Phone numbers must follow the format `+CCXXXXXXXXXX` where `CC` is the country code:

```
+911234567890   ✅ Valid (India)
+14155552671    ✅ Valid (USA)
1234567890      ❌ Invalid (missing +)
```

---

## 📊 Sample CSV Output

```
Name,Phone,Usage,Bill_INR,User_Type
Alice,+911234567890,250.0,25.00,Low
Bob,+14155552671,800.0,5600.00,High
Charlie,+447700900123,150.0,1275.00,Low
```

---

## 🛠️ Known Issues

- `analyze_customers.py` contains an unresolved Git merge conflict marker (`<<<<<<< HEAD` / `>>>>>>>`). Remove the duplicate block and conflict markers before running.
- The program supports up to **100 customers** in memory at a time.

---

## 📄 License

This project was built for academic purposes. Feel free to use or modify it for learning.
