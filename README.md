# ATM System — C++

A console-based ATM simulation developed using C++. The system allows authenticated clients to access their accounts and perform essential ATM operations through an interactive menu, with account data stored in a text file.

## Features

- **Account Authentication:** Log in using an account number and PIN code.
- **Quick Withdrawal:** Withdraw money using predefined amounts.
- **Normal Withdrawal:** Enter a custom withdrawal amount with validation.
- **Deposit:** Add money to the current account balance.
- **Balance Inquiry:** View account details and the available balance.
- **Balance Validation:** Prevent withdrawals that exceed the available balance.
- **Persistent Data Storage:** Load client records from `bankfile.txt` and save balance updates.
- **Interactive ATM Menu:** Navigate between transactions and return to the main menu.
- **Logout:** End the current session.

## Technologies Used

- C++
- Standard C++ Libraries
- Structures (`struct`)
- Enumerations (`enum`)
- Vectors (`std::vector`)
- File Handling (`fstream`)
- Functions and Modular Programming

## How to Run

1. Clone or download this repository.
2. Open `ATM_System.vcxproj` or the solution file in Visual Studio, if available.
3. Build the project.
4. Run the application.
5. Log in using a valid account number and PIN from the configured data file.
6. Choose an ATM operation from the main menu.

## Data Storage

Client information is stored in `bankfile.txt`, including account number, PIN, client name, phone number, and account balance.

**Note:** This is an educational console project and is not intended for real financial transactions.

## Author

Ahmed Ghanem

---

*Developed as a practical C++ project to apply file handling, structured data management, input validation, and transaction logic.*
