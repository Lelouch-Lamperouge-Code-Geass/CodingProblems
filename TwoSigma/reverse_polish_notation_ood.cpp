
/* 
Interpreter Design Pattern: Interpreter pattern provides a way to evaluate language grammar or expression. 
This pattern involves implementing an expression interface which tells to interpret a particular context. 
In computer programming, the interpreter pattern is a design pattern that specifies how to evaluate sentences 
in a language. The basic idea is to have a class for each symbol (terminal or nonterminal) in a specialized 
computer language. The syntax tree of a sentence in the language is an instance of the composite pattern and 
is used to evaluate (interpret) the sentence for a client. In computer science, an abstract syntax tree (AST), 
or just syntax tree, is a tree representation of the abstract syntactic structure of source code written in 
a programming language. Each node of the tree denotes a construct occurring in the source code. 
The syntax is "abstract" in not representing every detail appearing in the real syntax.
A parse tree or parsing tree or derivation tree or (concrete) syntax tree is an ordered, 
rooted tree that represents the syntactic structure of a string according to some context-free grammar. 
The term parse tree itself is used primarily in computational linguistics; in theoretical syntax 
the term syntax tree is more common. Parse trees are distinct from the abstract syntax trees used in computer programming, 
in that their structure and elements more concretely reflect the syntax of the input language. 
*/
#include <unordered_map>
#include <iostream>
#include <vector>
#include <memory>
#include <cassert>

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
