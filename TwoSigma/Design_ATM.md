# Requirement
ATM oo design - 设计interface - 
有基本的interface, 写implementation 

```
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
```

# Good reference

https://www.elprocus.com/automatic-teller-machine-types-working-advantages/  
http://www.math-cs.gordon.edu/courses/cs211/ATMExample/

# Introduction
  
The automatic teller machine (ATM) is an automatic banking machine (ABM) which allows customer to complete basic transactions without any help of bank representatives. There are two types of automatic teller machines (ATMs). The basic one allows the customer to only draw cash and receive a report of the account balance. Another one is a more complex machine which accepts the deposit, provides credit card payment facilities and reports account information.  
  
It is an electronic device which is used by only bank customers to process account transactions. The users access their account through special type of plastic card that is encoded with user information on a magnetic strip. The strip contains an identification code that is transmitted to the bank’s central computer by modem. The users insert the card into ATMs to access the account and process their account transactions.
  
# Automatic Telling Machine Block Diagram
  
![alt](https://www.elprocus.com/wp-content/uploads/2013/10/Automatic-Teller-Machine.png)
       
 The Automatic telling machine consists of mainly two input devices and four output devices that are;

Input Devices:

1. Card reader
2. Keypad

Output Devices:

1. Speaker
2. Display Screen
3. Receipt Printer
4. Cash Depositor      


# ATM Networking

The internet service provider (ISP) also plays an important role in the ATMs. This provides communication between ATM and host processors. When the transaction is made, the details are input by the card holder. This information is passed on to the host processor by the ATM machine. The host processor checks these details with authorized bank. If the details are matched, the host processor sends the approval code to the ATM machine so that the cash can be transferred.

![alt](https://www.elprocus.com/wp-content/uploads/2013/10/Automatic-Teller-Machine-Networking.png)

# ATM Security

The ATM card is secured with PIN number which is kept secret. There is no way to get the PIN number from your card. It is encrypted by the strong software like Triple data Encryption Slandered.

The Automatic teller machine is simply a data terminal with two input and four output devices. These devices are interfaced to the processor. The processor is heart of the ATM machine. All the ATM machines working around the world are based on centralized database system. The ATM has to connect and communicate with the host processor (server).  The host processor is communicating with the internet service provider (ISP). It is the gateway through all the ATM networks available to the card holder.

![alt](https://www.elprocus.com/wp-content/uploads/2013/10/Automatic-Teller-Machine-Architecture.png)

When a card holder wants does an ATM transaction, user provides necessary information through card reader and keypad. The ATM forwards this information to the host processor. The host processor enters the transaction request to the cardholder bank. If the card holder requests the cash, the host processor takes the cash from the card holder account. Once the funds are transferred from the customer account to host processor bank account, the processor sends approval code to the ATM and the authorized machine to dispense the cash. This is the way to get the amount on ATMs. The ATM network is fully based on centralized database environment. This will make life easer and secured the cash.

# How ATM works

![alt](https://qph.ec.quoracdn.net/main-qimg-35f71e7a81d1b89ddbcd4034735ad16f)

An ATM is simply a data terminal with two input and four output devices. Like any other data terminal, the ATM has to connect to, and communicate through, a __host processor__. The host processor is analogous to an __Internet service provider (ISP)__ in that it is the gateway through which all the various ATM networks become available to the cardholder (the person wanting the cash).

Most host processors can support either leased-line or dial-up machines. Leased-line machines connect directly to the host processor through a four-wire, point-to-point, dedicated telephone line. Dial-up ATMs connect to the host processor through a normal phone line using a modem and a toll-free number, or through an Internet service provider using a local access number dialed by modem.

Leased-line ATMs are preferred for very high-volume locations because of their thru-put capability, and dial-up ATMs are preferred for retail merchant locations where cost is a greater factor than thru-put. The initial cost for a dial-up machine is less than half that for a leased-line machine. The monthly operating costs for dial-up are only a fraction of the costs for leased-line.

_The host processor may be owned by a bank or financial institution, or it may be owned by an independent service provider. Bank-owned processors normally support only bank-owned machines, whereas the independent processors support merchant-owned machines._

![alt](https://qph.ec.quoracdn.net/main-qimg-dd876128d56bfb8a206e16d4216646b0)

You're probably one of the millions who has used an ATM. As you know, an ATM has two input devices:

* Card reader - The card reader captures the account information stored on the magnetic stripe on the back of an ATM/debit or credit card. The host processor uses this information to route the transaction to the cardholder's bank.  
* Keypad - The keypad lets the cardholder tell the bank what kind of transaction is required (cash withdrawal, balance inquiry, etc.) and for what amount. Also, the bank requires the cardholder's personal identification number (PIN) for verification. Federal law requires that the PIN block be sent to the host processor in encrypted form.  

And an ATM has four output devices:

* Speaker - The speaker provides the cardholder with auditory feedback when a key is pressed.  
* Display screen - The display screen prompts the cardholder through each step of the transaction process. Leased-line machines commonly use a monochrome or color CRT (cathode ray tube) display. Dial-up machines commonly use a monochrome or color LCD.  
* Receipt printer - The receipt printer provides the cardholder with a paper receipt of the transaction.  
* Cash dispenser - The heart of an ATM is the safe and cash-dispensing mechanism. The entire bottom portion of most small ATMs is a safe that contains the cash.  

#### Settlement Funds

![alt](https://qph.ec.quoracdn.net/main-qimg-11ae52119b36a537854cadfa160fec6d)

When a cardholder wants to do an ATM transaction, he or she provides the necessary information by means of the card reader and keypad. The ATM forwards this information to the host processor, which routes the transaction request to the cardholder's bank or the institution that issued the card. If the cardholder is requesting cash, the host processor causes an electronic funds transfer to take place from the customer's bank account to the host processor's account. Once the funds are transferred to the host processor's bank account, the processor sends an approval code to the ATM authorising the machine to dispense the cash. The processor then ACHs the cardholder's funds into the merchant's bank account, usually the next bank business day. In this way, the merchant is reimbursed for all funds dispensed by the ATM.

So when you request cash, the money moves electronically from your account to the host's account to the merchant's account.


# OO design

The general object-oriented design pattern for ATM is __state pattern__. The state pattern is a __behavioral software design pattern__ that implements a __state machine__ in an object-oriented way. With the state pattern, a state machine is implemented by implementing each individual state as a derived class of the state pattern interface, and implementing state transitions by invoking methods defined by the pattern's superclass.

What problems can the State design pattern solve? 

1. An object should change its behavior when its internal state changes.  
2. State-specific behavior should be defined independently. That is, new states should be added and the behavior of existing states should be changed independently.  



# Sample Code

```cpp
//http://www.newthinktank.com/2012/10/state-design-pattern-tutorial/


// Implement the default behavior.
class ATMState{
public:
  virtual InsertCard(ATM* atm) {/*implementation*/}
  virtual float GetBalanceInfo(ATM* atm){/*implementation*/}
  virtual bool Deposit(ATM* atm,float val){/*implementation*/}
  virtual bool Withdraw(ATM* atm,float val){/*implementation*/}
  virtual bool VerifyPIN(ATM* atm,int pinVal){/*implementation*/}
private:
  friend class ATM;
};

// Maintain no local state,
// so it can be shared and only one instance is required.
class NoCardState : public ATMState {
public:
  static NoCardState& Instance(){
    static NoCardState instance;
    return instance;
  }
  virtual InsertCard(ATM* atm) {atm->ChangeState(HasCardState::Instance);}
  virtual bool Withdraw(ATM* atm,float val){std::cout<<"Please insert card"<<std::endl;}
  virtual bool VerifyPIN(ATM* atm,int pinVal){std::cout<<"Please insert card"<<std::endl;}
  //.........
private:
  NoCardState(){}
  NoCardState(const NoCardState& other) = delete;
  NoCardState& operator=(const NoCardState& other) = delete;
};

class HasCardState : public ATMState {
public:
  static HasCardState& Instance(){
    static HasCardState instance;
    return instance;
  }
  virtual bool Withdraw(ATM* atm,float val){std::cout<<"You hasn't input PIN yet"<<std::endl;}
  bool VerifyPIN(ATM* atm,int pinVal) {atm->ChangeState(HasPINState::Instance);}
private:
  HasCardState(){}
  HasCardState(const HasCardState& other) = delete;
  HasCardState& operator=(const HasCardState& other) = delete;
};

class HasPINState : public ATMState {
public:
  static HasPINState& Instance(){
    static HasPINState instance;
    return instance;
  }
  virtual bool Withdraw(ATM* atm,float val){std::cout<<"You have withdrawn "<<val<<std::endl;}
private:
  HasPINState(){}
  HasPINState(const HasPINState& other) = delete;
  HasPINState& operator=(const HasPINState& other) = delete;
};

class ATM{
private:
  ATMState *m_state; // keeps an instance of state class ATMState
  void ChangeState(ATMState *new_state) {m_state = new_state;}
public:
  ATM(){m_state = & NoCardState::Instance();} // initial state is no card
  void InsertCard() {m_state->InsertCard(this);}
  float GetBalance(){return m_state->GetBalance(this);}
  bool Deposit(float val){return m_state->Deposit(this,val);}
  bool Withdraw(float val){return m_state->Withdraw(this,val);}
  bool VerifyPIN(int pinVal){return m_state->VerifyPIN(this,pinVal);}
};

int main(){
  ATM atm;
  atm.Withdraw();
  atm.InsertCard();
  atm.VerifyPin(1234);
  atm.Withdraw(100.50);
}
```
