
/* 
Interpreter Design Pattern: Interpreter pattern provides a way to evaluate language grammar or expression. 
This pattern involves implementing an expression interface which tells to interpret a particular context. 
In computer programming, the interpreter pattern is a design pattern that specifies how to evaluate sentences 
in a language. The basic idea is to have a class for each symbol (terminal or nonterminal) in a specialized 
computer language. The syntax tree of a sentence in the language is an instance of the composite pattern and is used to evaluate (interpret) the sentence for a client.
In computer science, an abstract syntax tree (AST), or just syntax tree, is a tree representation of the abstract syntactic structure of source code written in a programming language. Each node of the tree denotes a construct occurring in the source code. The syntax is "abstract" in not representing every detail appearing in the real syntax.
A parse tree or parsing tree or derivation tree or (concrete) syntax tree is an ordered, rooted tree that represents the syntactic structure of a string according to some context-free grammar. The term parse tree itself is used primarily in computational linguistics; in theoretical syntax the term syntax tree is more common. Parse trees are distinct from the abstract syntax trees used in computer programming, in that their structure and elements more concretely reflect the syntax of the input language. 
*/
class IExpression {
public:
	virtual double Interpret() { return 0;}
	~IExpression(){}
};
typedef std::shared_ptr<IExpression> IExpressionPtr;

class NumberExpression : public IExpression {
public:
	NumberExpression(const double val) : m_value(val){}
	virtual double Interpret() {return m_value;}
private:
	double m_value;
};
typedef std::shared_ptr<NumberExpression> NumberExpressionPtr;

class AddExpression : public IExpression {
public:
	AddExpression(const IExpressionPtr & left, const IExpressionPtr & right) : m_left(left),m_right(right){
	}
	virtual double Interpret() { return m_left->Interpret() + m_right->Interpret();}
private:
	IExpressionPtr m_left;
	IExpressionPtr m_right;
};
class SubExpression : public IExpression {
public:
	SubExpression(const IExpressionPtr & left, const IExpressionPtr & right) : m_left(left),m_right(right){
	}
	virtual double Interpret() { return m_left->Interpret() - m_right->Interpret();}
private:
	IExpressionPtr m_left;
	IExpressionPtr m_right;
};
class MulExpression : public IExpression {
public:
	MulExpression(const IExpressionPtr & left, const IExpressionPtr & right) : m_left(left),m_right(right){
	}
	virtual double Interpret() { return m_left->Interpret() * m_right->Interpret();}
private:
	IExpressionPtr m_left;
	IExpressionPtr m_right;
};
class DivExpression : public IExpression {
public:
	DivExpression(const IExpressionPtr & left, const IExpressionPtr & right) : m_left(left),m_right(right){
	}
	virtual double Interpret() { return m_left->Interpret() / m_right->Interpret();}
private:
	IExpressionPtr m_left;
	IExpressionPtr m_right;
};

// Singleton Design Pattern 
class OperatorFactory {
public:
	static OperatorFactory & Instance() {
		static OperatorFactory instance;
		return instance;
	}
	bool IsOperator(const char c) const {
		return m_operators.find(c) !=m_operators.end();
	}
	std::shared_ptr<IExpression> GetOperator(const char  c, const IExpressionPtr & left, const IExpressionPtr & right) const {
		switch (c) {
		case '+' : return std::make_shared<AddExpression>(left,right);
		case '-' : return std::make_shared<SubExpression>(left,right);
		case '*' : return std::make_shared<MulExpression>(left,right);
		case '/' : return std::make_shared<DivExpression>(left,right);
		default:
			throw invalid_argument ("Invalid operator");
		}
	}
private:
	OperatorFactory() {
		m_operators.insert('+');
		m_operators.insert('-');
		m_operators.insert('*');
		m_operators.insert('/');
	}

	unordered_set<char> m_operators;
};

class Token {
public:
	Token(const std::string & text) {m_text = text;}
	string m_text;
};

class Tokenizer {
public:
	Tokenizer(const std::string & str) {
		std::istringstream iss(str);
		string temp("");
		while (std::getline(iss,temp,',')) {
			m_tokens.push_back(Token(temp));
		}
	}
	bool HasNext() {return !m_tokens.empty();}
	Token NextToken() {Token token = m_tokens.front();m_tokens.pop_front();return token; }
private:
	std::list<Token> m_tokens;
};

class Calculator {
	
public:
	Calculator(){}
	double Calculate(Tokenizer & tokenizer) {
		const OperatorFactory & op_factory = OperatorFactory::Instance();
		while (tokenizer.HasNext()) {
			const Token & cur_token = tokenizer.NextToken();
			if ( op_factory.IsOperator(cur_token.m_text[0]) ) {
				IExpressionPtr right = m_operands.top();
				m_operands.pop();
				IExpressionPtr left = m_operands.top();
				m_operands.pop();
				std::shared_ptr<IExpression> op = op_factory.GetOperator(cur_token.m_text[0],left,right);
				m_operands.push( std::make_shared<NumberExpression>(op->Interpret()));
			} else {
				m_operands.push( std::make_shared<NumberExpression>(std::stod(cur_token.m_text) ) ) ;
			}
		}
		return m_operands.top()->Interpret();
	}
private:
	std::stack< NumberExpressionPtr > m_operands;
};

int _tmain(int argc, _TCHAR* argv[])
{
	Tokenizer tk("4,3,2,-,1,+,*");
	Calculator cal;
	double value = cal.Calculate(tk);
	assert(value==8);

	Tokenizer tk2("3,2,5,/,+,2,4,*,-");//3+2/5-2*4
	value = cal.Calculate(tk2);
	assert(value==-4.6);
	return 0;
}

