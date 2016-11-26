// Abstract class for operators
class Operator {
public:
  enum OpType{
    Binary,
    Unary
  };
  
  explicit Operator(OpType ot) {m_op_type = ot;}
  virtual double get_result() = 0;
private:
  OpType m_op_type;
};
// Abstract class for binary operators
Class BinaryOperator : public Operator {
 public:
  BinaryOperator():OpType(Operator::Binary){}
}

class Add : public BinaryOperator {
public:
  Add(){}
};

class Sub : public BinaryOperator {
public:
  Sub(){}
};

class Mul : public BinaryOperator {
public:
  Mul(){}
};

class Div : public BinaryOperator {
public:
  Div(){}
};

class Token {
public:
  Token(const std::string & text) {m_text = text;}
private:
  string m_text;
};

class Tokenizer {
public:
  Tokenizer(const std::string & str) {
    std::size_t index(0);
    typedef std::string::npos end;
    while (index!=end) {
      if (str[index]==' ') { //ignore whitespaces
        index = str.find_first_not_of(" ",index+1);
      } else if( std::isdigit(str[index])) { // number
        std::size_t found  = str.find_first_not_of("0123456789",index);
        m_tokens.push_back( str.substr(index,found-index) );
        index = found;
      } else { // +,-,*,/
        m_tokens.push_backtr.substr(index,1));
        ++ index;
      }
    }
  }
  bool has_next() {return !m_tokens.empty();}
  Token next_token() {Token token = m_tokens.front();m_tokens.pop_front();return token; }
private:
  std::list<Token> m_tokens;
};
