// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <memory>
#include <unordered_set>
#include <string>
#include <cctype>
#include <stack>
#include <numeric>
#include <functional> 

using namespace std;

// Abstract class for operators
class Operator {
public:
	enum OpType{
		Binary,
		Unary
	};
	explicit Operator(OpType ot) {m_op_type = ot;}
	virtual ~Operator() {}
	virtual double get_result(const vector<double> & values) {return 0.0;}
	OpType m_op_type;
};
// Abstract class for binary operators
class BinaryOperator : public Operator {
public:
	BinaryOperator():Operator(Operator::Binary){}
	virtual ~BinaryOperator(){}
};

class Add : public BinaryOperator {
public:
	Add(){}
	virtual double get_result(const vector<double> & values) { return std::accumulate(values.begin(),values.end(), 0.0,std::plus<double>());}
};

class Sub : public BinaryOperator {
public:
	Sub(){}
	virtual double get_result(const vector<double> & values)  { return std::accumulate(values.begin(),values.end(), 0.0, std::minus<double>());}
};

class Mul : public BinaryOperator {
public:
	Mul(){}
	virtual double get_result(const vector<double> & values) { return std::accumulate(values.begin(),values.end(), 1.0, std::multiplies<double>());}
};

class Div : public BinaryOperator {
public:
	Div(){}
	virtual double get_result(const vector<double> & values)  { return std::accumulate(values.begin()+1,values.end(), values.front(), std::divides<double>());}
};

class Token {
public:
	Token(const std::string & text) {m_text = text;}
	string m_text;
};

class Tokenizer {
public:
	Tokenizer(const std::string & str) {
		std::size_t index(0);
		while (index!=std::string::npos) {
			if (str[index]==' ') { //ignore whitespaces
				index = str.find_first_not_of(" ",index+1);
			} else if( std::isdigit(str[index])) { // number
				std::size_t found  = str.find_first_not_of("0123456789",index);
				m_tokens.push_back( str.substr(index,found-index) );
				index = found;
			} else { // +,-,*,/
				m_tokens.push_back( str.substr(index,1));
				++ index;
			}
		}
	}
	bool has_next() {return !m_tokens.empty();}
	Token next_token() {Token token = m_tokens.front();m_tokens.pop_front();return token; }
private:
	std::list<Token> m_tokens;
};

class Calculator {
	
public:
	Calculator(){}

	double calculate(Tokenizer tokenizer) {
		preprocess(tokenizer);// populate operators and operands
		while ( !m_operators.empty() ) {
			std::shared_ptr<Operator> op =  m_operators.top();
			m_operators.pop();
			if (op->m_op_type == Operator::Binary) {
				double right = m_operands.top(); 
				m_operands.pop();
				double left = m_operands.top();
				m_operands.pop();

				vector<double> values;
				values.push_back(left);
				values.push_back(right);
				double res = op->get_result( values ) ;
				m_operands.push( op->get_result( values ) );
			} else {
				// default unary operation
				
			}
		}
		return m_operands.top();
	}
private:
	void preprocess(Tokenizer tokenizer) {
		m_operators = std::stack<std::shared_ptr<Operator> >();
		m_operands = std::stack<double>(); //
		while(tokenizer.has_next()) {
			const Token & tk = tokenizer.next_token();
			if ( !std::isdigit( tk.m_text[0]) ) {
				m_operators.push( get_operator(tk.m_text[0]) );
			} else {
				m_operands.push(std::stod(tk.m_text));
			}
		}
	}

	static std::shared_ptr<Operator> get_operator(const char c) {
		switch (c) {
		case '+' : return std::make_shared<Add>();
		case '-' : return std::make_shared<Sub>();
		case '*' : return std::make_shared<Mul>();
		case '/' : return std::make_shared<Div>();
		default:
			throw invalid_argument ("Invalid operator");
		}
	}

	std::stack<	std::shared_ptr<Operator> > m_operators;
	std::stack<double> m_operands;
};

int _tmain(int argc, _TCHAR* argv[])
{
	Tokenizer tk("3+2/5-2*4");
	Calculator cal;
	double value = cal.calculate(tk);
	return 0;
}

