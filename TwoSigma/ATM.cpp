// Very good reference: http://www.math-cs.gordon.edu/courses/cs211/ATMExample/
/***
ATM oo design - 设计interface - 
有基本的interface, 写implementation 

Accounts: 
- checking 
- saving 
Functions: 
- withdraw 
- deposit 
- transfer 
- inquiry 
- setting 

class ATM 
class User 
class Accounts


 ***/
class ATMCard {
private:
  std::string m_card_number;
};

// ATM state interface
class ATMState {
public:
  void InsertCard() = 0;
  void VerifyPin() = 0;
  void Deposit() = 0;
  void Withdraw() = 0;
  void Inquery() = 0;
};

// Concrete state classes, they should be singleton.
// They won't have any member variables in general, so they are thread-safe
class NoCardState : public ATMState { }; // this is the first state
class HasCardState : public ATMState { }; // has card, not verify PIN yet
class VerifiedPinState : public ATMState { }; // verified PIN

// maintain reference to ATMState
class ATM {
public:
  ATM(){}
  void InsertCard() {}
  void VerifyPin() {}
  void Deposit() {}
  void Withdraw() {}
  void Inquery() {}
private:
  // States management
  void ChangeState(ATMStatePtr & state){m_state_ptr = state;}
  ATMStatePtr m_state_ptr; // maintain 
  
  // Component parts of the ATM
  CardReaderPtr m_card_reader_ptr; // card reader
  CashDispenserPtr m_cash_dispenser_ptr; // cash dispenser
  CustomerConsolePtr m_customer_console_ptr; // customer console
  LogPtr m_log_ptr; // Logger
  OperatorPanelPtr m_operator_panel_ptr; // Operator Panel
  ReceiptPrinterPtr m_receipt_printer_ptr; // Receipt Printer
};

class User { };

// Account base class.
// General implementation should be defined here.
// While leave derived classes for account-type specific implementation.
class Account {
public:
  virtual void Deposit() {}
  virtual void Withdraw() {}
  virtual void Inquiry() {}
  virtual void Transfer() {}
};

class CheckingAccount : public Account {};
class SavingAccount : public Account {};

/***
Transaction hierarchy.
Command pattern, memonto pattern may be suitable here depends on requirements.
***/
class Transaction {
public:
  virtual Execute() = 0;
  virtual void Undo() = 0; 
  virtual void Redo() = 0; 
  virtual ~Transation() {};
};

class Withdrawal : public Transaction {
public:
  Withdrawal(AccountPtr account_ptr, double amount) 
    : m_account_ptr(account_ptr), m_amount(amount), m_executed(false) {
    
  }
  virtual void Execute() { 
    if (!m_executed) { 
      m_account_ptr->Withdraw(m_amount); 
      m_executed = true;
    }
  }
  virtual void Undo() { 
    if (m_executed){
      m_account_ptr->Withdraw(amount);
      m_account_ptr->Deposit(amount);
      m_executed = false;
    }
  }
private:
  bool m_executed;
  AccountPtr m_account_ptr;
  double m_amount;
};

// same for other transactions
class Deposit : public Transaction {};
class Inquiry : public Transaction {};
class Transfer : public Transaction {};

// Offer limited interaction with relational database
class BankDatabaseProxy {
public:
  UserPtr AuthenticateUser(const std::string & card_number, const std::string & pin);
  void Transfer(AccountPtr account, double amount);
  void Inquiry(AccountPtr account);
  void Deposit(AccountPtr account, double amount);
  void Withdraw(AccountPtr account, double amount);
};

