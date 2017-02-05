struct Node;
typedef Node* NodePtr;

struct Node {
  Node(const std::stirng & text = "") : m_text(text), m_weight(text.size()){}
  std::string m_text;
  std::size_t m_weight;
  NodePtr m_left;
  NodePtr m_right;
};

class TextEditor {
public:
  TextEditor() { }
  char GetChar(std::size_t m_pos) {
    return GetChar(m_root, m_pos);
  }
  
private:
  static char GetChar(const NodePtr & root, std::size_t pos) {
    if (!root) return '';
    
    if (root->m_weight < pos) {
      return GetChar(root->right, pos - root->m_weight);
    } else {
      if (root->m_left) {
        return GetChar(root->left, pos);
      } else { // leaf node
        return root->m_text[pos];
      }
    }
  }
// Return a Rope tree based on input
  static NodePtr Build(const std::string & input) {
    const std::size_t input_size(input.size());
    if (input_size <= 0) {
      return nullptr;
    } else if( input_size == 1) {
      return std::make_shared<Node>(input);
    } else {
      NodePtr root = std::make_shared<Node>();
      root->m_left = Build(input.substr(0,input_size/2));
      root->m_right = Build(input.substr(input_size/2));
      root->m_wieght  = root->m_left->m_weight + root->m_right->m_weight;
      return root;
    }
  }
  
  static NodePtr Concat(NodePtr & left, NodePtr & right);
  static void Split(NodePtr & root, std::size_t pos, NodePtr & left, NodePtr & right);
  static void Insert(NodePtr & root, std::size_t pos, const std::string & input) {
    // Call Build to generate Rope tree for input string.
    // Split root based on position, get left and right tree.
    // Concatenate left tree with input node, then concatenate them with right tree.
  }
  
  NodePtr m_root;
  
  // Whenever execute an operation, clear m_redo first,
  // and then push operation into m_undo.
  std::stack<OperationPtr> m_undo;
  
  // Whenever redo an operation, pop that opertion out and push it
  // into m_undo.
  std::stack<OperationPtr> m_redo;
  
};
