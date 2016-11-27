// Abstract class for operators
class Operator {
public:
	enum OpType{
		Binary,
		Unary
	};
	explicit Operator(OpType ot) {m_op_type = ot;}
	virtual ~Operator() {}
	OpType m_op_type;
};
// Abstract class for binary operators
class BinaryOperator : public Operator {
public:
	BinaryOperator():Operator(Operator::Binary){}
	virtual ~BinaryOperator(){}
	virtual double operator() (double,double) = 0;
};

class Add : public BinaryOperator {
public:
	Add(){}
	virtual double operator() (double left, double right) { return left + right;}
};

class Sub : public BinaryOperator {
public:
	Sub(){}
	virtual double operator() (double left, double right) { return left - right;}
};

class Mul : public BinaryOperator {
public:
	Mul(){}
	virtual double operator() (double left, double right) { return left * right;}
};

class Div : public BinaryOperator {
public:
	Div(){}
	virtual double operator() (double left, double right) { return left / right;}
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
			const BinaryOperator & op = m_operators.top();
			if (op.m_op_type == Operator::Binary) {

				double right = m_operands.top(); 
				m_operands.pop();
				double left = m_operands.top();
				m_operands.pop();

				m_operands.push( op(left,right) );
			}
		}
	}
private:
	void preprocess(Tokenizer tokenizer) {
		m_operators = std::stack<Operator>();
		m_operands = std::stack<double>(); //
		while(tokenizer.has_next()) {
			const Token & tk = tokenizer.next_token();
			if ( !std::isdigit( tk.m_text[0]) ) {
				m_operators.push(get_operator(tk.m_text[0]));
			} else {
				m_operands.push(std::stod(tk.m_text));
			}
		}
	}

	static Operator get_operator(const char c) {
		switch (c) {
		case '+' : return Add();
		case '-' : return Sub();
		case '*' : return Mul();
		case '/' : return Div();
		default:
			throw invalid_argument ("Invalid operator");
		}
	}
	std::stack<Operator> m_operators;
	std::stack<double> m_operands;
};
