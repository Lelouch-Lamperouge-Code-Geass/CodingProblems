//insert(p), delete(p1, p2), highlight(p1, p2)，redo/undo, save/load update, search
//text editor需要insert，remove，highlight，需要想办法去index每次插入的object，原po说的interval tree应该就是index的方式吧。
//关键点在于text打算怎么存
//store highlight?
//他要求三天后再load这个text,需要可以undo三天前的操作. save的时候 保存成json/xml类型之类的 把之前的操作也一起存下来


class RopeNode {
public:
  RopeNode(const std::stirng & text = "") : m_text(text), m_weight(text.size()){}
  std::string m_text;
  std::size_t m_weight;
  RopeNodePtr m_left;
  RopeNodePtr m_right;
};

class Rope {
public:
  Rope(){}
  char GetChar(std::size_t pos) { return GetChar(m_root, pos); }
  void Insert(std::size_t pos, const std::string & text) { return Insert(m_root, pos, text); }
  void Delete(std::size_t from, std::size_t to) { Delete(m_root, from, to); }
private:


  static char GetChar(const RopeNodePtr & root, std::size_t pos) {
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

  static RopeNodePtr GetNewNode(const std::string & text) {
    return std::make_shared<RopeNode>(text);
  }
 /***
    A concatenation can be performed simply by creating a new root node with left = S1 and right = S2,
    which is constant time. The weight of the parent node is set to the length of the left child S1, which would take O(log N) time, if the tree is balanced.
    As most rope operations require balanced trees, the tree may need to be re-balanced after concatenation.
  ***/
  static RopeNodePtr Concat(RopeNodePtr & left, RopeNodePtr & right) {
    RopeNodePtr reval = std::make_shared<RopeNode>();
    reval->m_weight = left->m_weight + right->m_weight;
    // balancing....
    return reval;
  }

  /***
      Split the Rope into two ropes, the other rope will be stored at `other`.
   ***/
  static void Split(RopeNodePtr & root, std::size_t pos, RopeNodePtr & other);

  /***
    This operation can be done by two Split() and one Concat() operation. First, split the rope in three,
    divided by i-th and i+j-th character respectively, which extracts the string to delete in a separate node.
    Then concatenate the other two nodes.
   ***/
  static void Delete(RopeNodePtr & root, std::size_t from, std::size_t to) {
    RopeNodePtr left_part,  right_part, other;

    Split(root, from, other);
    left_part = root;


    Split(other, to - from, right_part);

    root = Concat(left_part, right_part);

    // Call balance function
  }

  static void Insert(RopeNodePtr & root, std::size_t pos, const std::string & input) {
    RopeNodePtr other;
    Split(root, pos, other);
    RopeNodePtr new_node = GetNewNode(input);

    root = Concat(root, new_node);
    root = concat(root, other);
    // Call balance function
  }
};

// Here TextEditor is the receivor
class TextEditor{
public:
  TextEditor();
  void Insert(std::size_t pos, const std::string & text) { m_rope.Insert(pos, text); }
  void Delete(std::size_t from, std::size_t to) { m_rope.Delete(from, to); }
  void Highlight(std::size_t from, std::size_t to) {}
  void DeleteHighlight(std::size_t from, std::size_t to);
  std::size_t Search(const std::string);
  void Save(const std::string & file_path);
  void Load(const std::string & file_path);
private:
  Rope m_rope;
};
typedef std::shared_ptr<TextEditor> TextEditorPtr;

// The command interface
class ICommand {
public:
  ICommand(){}
  ~ICommand(){}
  virtual void Execute() = 0;
  virtual void Undo() = 0;
  virtual void Redo() = 0;
};
typedef std::shared_ptr<ICommand> ICommandPtr;

// The concrete command
class HighlightCommand : public ICommand {
public:
  HighlightCommand(const TextEditorPtr & editor,std::size_t from, std::size_t to)
    : m_text_editor(editor),m_from(from),m_to(to){}
  void Execute() {m_text_editor->Highlight(m_from,m_to);}
  void Redo() {m_text_editor->Highlight(m_from,m_to);}
  void Undo() {m_text_editor->DeleteHighlight(m_from,m_to);}
private:
  TextEditorPtr m_text_editor;
  std::size_t m_from;
  std::size_t m_to;
};


class CommandManager {
public:
  CommandManager(){}
  void ExecuteCommand(const ICommandPtr & command) {
    m_redo_stack.clear();// don't forget to clear redo stack
    command->Execute();
    m_undo_stack.push(command);
  }
  void Undo() {
    if (m_undo_stack.empty()) return;
    m_undo_stack.top()->Undo();
    m_redo_stack.push(m_undo_stack.top());
    m_undo_stack.pop();
  }
  void Redo() {
    if (m_redo_stack.empty()) return;
    m_redo_stack.top()->Redo();
    m_undo_stack.push(m_redo_stack.top());
    m_redo_stack.pop();
  }
private:
  std::stack<ICommandPtr> m_undo_stack;
  std::stack<ICommandPtr> m_redo_stack;
};
