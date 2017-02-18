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
typedef std::shared_ptr<ATMCard> ATMCardPtr;

class ATM {
public:
  ATM(){}
  void InsertCard(ATMCardPtr & card_ptr) {
    
  }
  void VerifyPin(const std::string & pin) {
    
  }
  void Deposit() {}
  void Withdraw() {}
  void Inquery() {}

};
class User {
  bool VerifyPin(const std::string & pin) {
    return  pin == m_pin_number;
  }
private:
  std::string m_name;
  std::string m_pin_number; 
};


enum AccountType {
  CHECKING = 0,
  SAVING
};

class Account {
public:
  void Deposit(double val, const AccountType & account_type) {
    if (account_type == CHECKING) {
      m_checking_balance += val;
    } else {
      m_saving_balance += val;
    }
  }
  void Withdraw(double val) {}
private:
  double m_checking_balance;
  double m_saving_balance;
};
