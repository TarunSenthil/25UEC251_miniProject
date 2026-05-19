📂 File Structure :

Bank-Account-Management-System/
│
├── bank_account_system.c   # Main C source code
├── credit.dat              # Binary data file (stores records)
├── accounts.txt            # Generated report file
├── README.md               # Project documentation


▶️ How to Run :

🔹 Step 1: Save your code
Save your program as:
bank_account_system.c

🔹 Step 2: Create data file 
Before running, create an empty binary file:
Method 1 :
touch credit.dat

Method 2 (C initialization – better for exams) :
Create a small program to initialize 100 empty records (optional but ideal).

🔹 Step 3: Compile the program

gcc bank_account_system.c -o bank

 
🔹 Step 4: Run the program

./bank

🔹 Step 5: Use menu
You will see:

MENU
1 - Export to text file
2 - Update account
3 - Add new account
4 - Delete account
5 - Search account (NEW)
6 - Exit


⚠️ Important Notes:

1.credit.dat → stores binary records
2.accounts.txt → created when you choose option 
3.Max accounts supported → 100 (fixed size)
4.Account number must be between 1–100
