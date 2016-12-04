//insert(p), delete(p1, p2), highlight(p1, p2)，redo/undo, save/load update, search
//text editor需要insert，remove，highlight，需要想办法去index每次插入的object，原po说的interval tree应该就是index的方式吧。
//关键点在于text打算怎么存
//store highlight?
//他要求三天后再load这个text,需要可以undo三天前的操作. save的时候 保存成xml类型之类的 把之前的操作也一起存下来

struct textNode{
    string s;
    int index;
};

struct Operations{
    string op; //op
    string time;
};

class textEditor{
    list<textNode> l;
    unordered_map<int,textNode> mp; //tree is better
    stack<Operations> st;
};
