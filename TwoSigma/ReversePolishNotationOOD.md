# Interpreter Pattern

In computer programming, the __interpreter pattern__ is a design pattern that specifies how to evaluate sentences in a language. The basic idea is to have a class for each symbol (__terminal__ or __nonterminal__) in a specialized computer language. The __syntax tree__ of a sentence in the language is an instance of the __composite pattern__ and is used to evaluate (interpret) the sentence for a client. In computer science, an abstract syntax tree (AST), or just syntax tree, is a tree representation of the abstract syntactic structure of source code written in a programming language. Each node of the tree denotes a construct occurring in the source code. 

The syntax is "abstract" in not representing every detail appearing in the real syntax. A parse tree or parsing tree or derivation tree or (concrete) syntax tree is an ordered, rooted tree that represents the syntactic structure of a string according to some context-free grammar. The term parse tree itself is used primarily in computational linguistics; in theoretical syntax the term syntax tree is more common. Parse trees are distinct from the abstract syntax trees used in computer programming, in that their structure and elements more concretely reflect the syntax of the input language. 

http://stackoverflow.com/questions/1809670/how-to-implement-serialization-in-c


#### Overview

What problems can the Interpreter design pattern solve?

* A grammar for a simple language should be defined
* so that sentences in the language can be interpreted.

When a problem occurs very often, it could be considered to represent it as a sentence in a simple language (Domain Specific Languages) so that an interpreter can solve the problem by interpreting the sentence.

For example, when many different or complex search expressions must be specified. Implementing (hard-wiring) them directly into a class is inflexible because it commits the class to particular expressions and makes it impossible to specify new expressions or change existing ones independently from (without having to change) the class.

What solution does the Interpreter design pattern describe?

* Define a grammar for a simple language by defining an Expression class hierarchy and implementing an interpret() operation.  
* Represent a sentence in the language by an abstract syntax tree (AST) made up of Expression instances.  
* Interpret a sentence by calling interpret() on the AST.  

The expression objects are composed recursively into a composite/tree structure that is called abstract syntax tree.

The Interpreter pattern doesn't describe how to build an abstract syntax tree. This can be done either manually by a client or automatically by a parser.

![alt](https://upload.wikimedia.org/wikipedia/commons/3/33/W3sDesign_Interpreter_Design_Pattern_UML.jpg)


# Factory method pattern

In class-based programming, the __factory method pattern__ is a creational pattern that uses factory methods to deal with the problem of creating objects without having to specify the exact class of the object that will be created. This is done by creating objects by calling a factory method—either specified in an interface and implemented by child classes, or implemented in a base class and optionally overridden by derived classes—rather than by calling a constructor.

### Overview

* How can an object be created so that subclasses can redefine which class to instantiate?  
* How can a class defer instantiation to subclasses?  

Creating an object directly within the class that requires (uses) the object is inflexible because it commits the class to a particular object and makes it impossible to change the instantiation independently from (without having to change) the class.

The Factory Method design pattern describes how to solve such problems:  

* Define a separate operation (factory method) for creating an object.  
* Create an object by calling a factory method.  


# Solution

In this solution, we use interpreter pattern to define token's hierarchy. And we use factory method to make client be able to define their open operator and operand.

```cpp
#include <unordered_map>
#include <iostream>
#include <vector>
#include <memory>
#include <cassert>

// When define tokens, we use interpreter pattern.
// The Execute(std::vector<OperandPtr> & operands) is like our interpret function.
class Token {
public:
  virtual ~Token(){}
};


class Operand : public Token {
public:
  Operand(double val) : m_value(val) {}
  virtual ~Operand(){}
  void SetValue(double val) { m_value = val; }
  double GetValue() const { return m_value; }
private:
  double m_value;
};
typedef std::shared_ptr<Operand> OperandPtr;

class Operator : public Token {
public:
  virtual ~Operator() {}
  virtual void Execute(std::vector<OperandPtr> & operands) = 0;
};
typedef std::shared_ptr<Operator> OperatorPtr;

class Add : public Operator {
public:
  virtual void Execute(std::vector<OperandPtr> & operands) {
    OperandPtr curr = operands.back();
    operands.pop_back();
    operands.back()->SetValue( operands.back()->GetValue() + curr->GetValue() );
  }
};

class Sub : public Operator {
public:
  virtual void Execute(std::vector<OperandPtr> & operands) {
    OperandPtr curr = operands.back();
    operands.pop_back();
    operands.back()->SetValue( operands.back()->GetValue() - curr->GetValue() );
  }
};

class Mul : public Operator {
public:
  virtual void Execute(std::vector<OperandPtr> & operands) {
    OperandPtr curr = operands.back();
    operands.pop_back();
    operands.back()->SetValue( operands.back()->GetValue() * curr->GetValue() );
  }
};

class Div : public Operator {
public:
  virtual void Execute(std::vector<OperandPtr> & operands) {
    OperandPtr curr = operands.back();
    operands.pop_back();
    operands.back()->SetValue( operands.back()->GetValue() / curr->GetValue() );
  }
};

// Here we used factory method.
class OperatorCreator {
public:
  virtual ~OperatorCreator(){}
  virtual OperatorPtr Create() = 0;
};
typedef std::shared_ptr<OperatorCreator> OperatorCreatorPtr;

class AddCreator : public OperatorCreator {
public:
  virtual OperatorPtr Create() {
    OperatorPtr reval = std::make_shared<Add>();
    return reval;
  }
};

class SubCreator : public OperatorCreator {
public:
  virtual OperatorPtr Create() {
    OperatorPtr reval = std::make_shared<Sub>();
    return reval;
  }
};

class MulCreator : public OperatorCreator {
public:
  virtual OperatorPtr Create() {
    OperatorPtr reval = std::make_shared<Mul>();
    return reval;
  }
};

class DivCreator : public OperatorCreator {
public:
  virtual OperatorPtr Create() {
    OperatorPtr reval = std::make_shared<Div>();
    return reval;
  }
};

// Even this class's name has "Factory", it has nothing to do
// with factory method.
class OperatorFactory {
public:
  bool IsOperator(const std::string & str) const {
    return m_mapper.count(str) != 0;
  }

  OperatorPtr GetOperator(const std::string & str) {
    if (!IsOperator(str)) {
      return nullptr;
    } else {
      return m_mapper[str]->Create();
    }
  }

  void RegisterOperator(const std::string & str, OperatorCreatorPtr & creator) {
    if (str.empty() || !creator) return;
    m_mapper[str] = creator;
  }

private:
  std::unordered_map<std::string, OperatorCreatorPtr> m_mapper;
};

class Calculator {
public:
  double Calculate(const std::vector<std::string> & strs) const {
    OperatorCreatorPtr add_creator = std::make_shared<AddCreator>();
    OperatorCreatorPtr sub_creator = std::make_shared<SubCreator>();
    OperatorCreatorPtr mul_creator = std::make_shared<MulCreator>();
    OperatorCreatorPtr div_creator = std::make_shared<DivCreator>();

    OperatorFactory operator_factory;
    operator_factory.RegisterOperator("+",add_creator);
    operator_factory.RegisterOperator("-",sub_creator);
    operator_factory.RegisterOperator("*",mul_creator);
    operator_factory.RegisterOperator("/",div_creator);

    std::vector<OperandPtr> operands;
    for (const std::string & str : strs) {
      if (operator_factory.IsOperator(str)) {
        OperatorPtr cur_operator = operator_factory.GetOperator(str);
        cur_operator->Execute(operands);
      } else {
        operands.push_back( std::make_shared<Operand>(std::stod(str)) );
      }
    }
    return operands.back()->GetValue();
  }
};

void UnitTest() {
  Calculator calculator;
  std::vector<std::string> tokens = {"3","2","-"};
  assert(calculator.Calculate(tokens) == 1);

  tokens = {"3","2","5","/","+","2","4","*","-"};
  assert(calculator.Calculate(tokens) == -4.6);
}


int main() {
  UnitTest();
  return 0;
}
```
