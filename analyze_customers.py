<<<<<<< HEAD
import pandas as pd
import matplotlib.pyplot as plt
import os

def plot_data(csv_file):
    if not os.path.exists(csv_file):
        print("customers.csv not found.")
        return

    df = pd.read_csv(csv_file)

    if df.empty:
        print("customers.csv is empty.")
        return

    print(f"Loaded {len(df)} customer records.")

    # Bar Chart - User count per type
    user_type_counts = df['User_Type'].value_counts().sort_index()
    plt.figure(figsize=(8, 5))
    bars = user_type_counts.plot(kind='bar', color='skyblue', edgecolor='black')

    plt.title("Customer Count per User Type")
    plt.xlabel("User Type")
    plt.ylabel("Number of Customers")
    plt.grid(axis='y')
    plt.gca().yaxis.set_major_locator(plt.MaxNLocator(integer=True))  # Ensure integer ticks

    # Add count labels above bars
    for i, (index, value) in enumerate(user_type_counts.items()):
        plt.text(i, value + 0.1, f"{index}: {int(value)}", ha='center', va='bottom', fontsize=9)

    plt.tight_layout()
    plt.show()

    # Pie Chart - Revenue share with Rs labels
    bill_per_type = df.groupby('User_Type')['Bill_INR'].sum().sort_index()
    labels = [f"{t} (Rs {v:.2f})" for t, v in bill_per_type.items()]
    plt.figure(figsize=(6, 6))
    plt.pie(bill_per_type, labels=labels, autopct='%1.1f%%', startangle=90, colors=plt.cm.Paired.colors)
    plt.title("Revenue Share by User Type")
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    plot_data("customers.csv")





=======
import pandas as pd
import matplotlib.pyplot as plt
import os

def plot_data(csv_file):
    if not os.path.exists(csv_file):
        print("customers.csv not found.")
        return

    df = pd.read_csv(csv_file)

    if df.empty:
        print("customers.csv is empty.")
        return

    print(f"Loaded {len(df)} customer records.")

    # Bar Chart - User count per type
    user_type_counts = df['User_Type'].value_counts().sort_index()
    plt.figure(figsize=(8, 5))
    bars = user_type_counts.plot(kind='bar', color='skyblue', edgecolor='black')

    plt.title("Customer Count per User Type")
    plt.xlabel("User Type")
    plt.ylabel("Number of Customers")
    plt.grid(axis='y')
    plt.gca().yaxis.set_major_locator(plt.MaxNLocator(integer=True))  # Ensure integer ticks

    # Add count labels above bars
    for i, (index, value) in enumerate(user_type_counts.items()):
        plt.text(i, value + 0.1, f"{index}: {int(value)}", ha='center', va='bottom', fontsize=9)

    plt.tight_layout()
    plt.show()

    # Pie Chart - Revenue share with Rs labels
    bill_per_type = df.groupby('User_Type')['Bill_INR'].sum().sort_index()
    labels = [f"{t} (Rs {v:.2f})" for t, v in bill_per_type.items()]
    plt.figure(figsize=(6, 6))
    plt.pie(bill_per_type, labels=labels, autopct='%1.1f%%', startangle=90, colors=plt.cm.Paired.colors)
    plt.title("Revenue Share by User Type")
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    plot_data("customers.csv")





>>>>>>> 5f091d4 (Initial commit: Customer Billing System with Data Analysis)
