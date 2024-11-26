# Welcome to the Cash Flow Minimizer System README !!

This system minimizes the number of transactions among multiple banks in different corners of the world that use different modes of payment. There is one world bank (with all payment modes) to act as an intermediary between banks that have no common mode of payment.

---

## Getting Started

Let's take an example. say we have the following banks:

- **Bank_of_America** (World Bank)
- **Wells_Fargo**
- **Royal_Bank_of_Canada**
- **Westpac**
- **National_Australia_Bank**
- **Goldman_Sachs**

### Payments to be Made

| Debtor Bank                 | Creditor Bank            | Amount (Rs) |
|-----------------------------|--------------------------|-------------|
| Goldman_Sachs              | Bank_of_America         | 100         |
| Goldman_Sachs              | Wells_Fargo             | 300         |
| Goldman_Sachs              | Royal_Bank_of_Canada    | 100         |
| Goldman_Sachs              | Westpac                 | 100         |
| National_Australia_Bank    | Bank_of_America         | 300         |
| National_Australia_Bank    | Royal_Bank_of_Canada    | 100         |
| Bank_of_America            | Wells_Fargo             | 400         |
| Wells_Fargo                | Royal_Bank_of_Canada    | 200         |
| Royal_Bank_of_Canada       | Westpac                 | 500         |

This is represented below as a directed graph with the directed edge representing debts.

![image](https://github.com/user-attachments/assets/632b6449-53e3-48d2-aedd-0a1359b641fb)
---

## Payment Modes

Each bank only supports a set of payment modes and can make or receive payments only via those modes. **Only the World Bank supports all payment modes.**

For this example, the available payment modes are:

- **Google_Pay**
- **AliPay**
- **Paytm**

### Supported Payment Modes by Each Bank

| Bank                       | Supported Payment Modes           |
|----------------------------|------------------------------------|
| Bank_of_America            | Google_Pay, AliPay, Paytm         |
| Wells_Fargo                | Google_Pay, AliPay                |
| Royal_Bank_of_Canada       | AliPay                            |
| Westpac                    | Google_Pay, Paytm                 |
| Goldman_Sachs              | Paytm                             |
| National_Australia_Bank    | AliPay, Paytm                     |

---

## Algorithm

To minimize cash flow, we calculate the **net amount** for each bank:

**Net Amount** = `[Sum of all credits (amounts to be received)] - [Sum of all debits (amounts to pay)]`

### Steps:

1. Identify the **max debtor** (Bank X with net amount `x`) and **max creditor** (Bank Y with net amount `y`) among the banks.  
2. Ensure Bank X and Bank Y share at least one common payment mode (say `M1`).  
3. Calculate `z = min(|x|, y)` (minimum of the absolute value of `x` and `y`).  
4. Settle `z` by transferring from Bank X to Bank Y via `M1`.  

### After Settlement:

- If `|x| < y`:  
  Bank X is **completely settled** and removed from the list.  
- If `|x| > y`:  
  Bank Y is **completely settled** and removed from the list.  
- If `|x| = y`:  
  Both Bank X and Bank Y are **completely settled** and removed from the list.

5. Repeat the process for the remaining banks until all debts are cleared.

---

### Example Output

For the current example, the transactions for **minimum cash flow** are as follows:

![image](https://github.com/user-attachments/assets/b2846649-da1a-41f0-bb2e-ad61846bfb8b)

So this is the required answer.

---

## How to Use?

This system is completely menu-driven. When you run the **C Application**, it will guide you through the process and display the final output.  
Below is the execution of our current example:

![Screenshot_2024-11-26_145655 1](https://github.com/user-attachments/assets/a0dc78c2-5e93-4b67-8400-7794123374a5)

![WhatsApp Image 2024-11-26 at 14 58 33_46250607](https://github.com/user-attachments/assets/048bd076-ad7d-4fa2-98f7-9ce5eb43e344)


---

## Thank You!!

Enjoy using the **Cash Flow Minimizer System** to optimize and simplify financial transactions across multiple banks!




