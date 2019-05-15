#pragma once
#include "Node.h"

//以下为所有的操作类型，均继承Node
class Constant : public Node{
public:
    using Node::Node;
    void cal();
    bool notconst(){
        return false;
    }
};

class Placeholder : public Node{
public:
    using Node::Node;
    void cal();
    bool notconst(){
        return true;
    }
};

class Variable : public Node{
public:
    using Node::Node;
    void cal();
    bool notconst(){
        return false;
    }
};

class Add : public Node{
public:
    using Node::Node;
    void cal();
    bool notconst(){
        return true;
    }
};

class Sub : public Node{
public:
    using Node::Node;
    void cal();
    bool notconst(){
        return true;
    }
};

class Mul : public Node{
public:
    using Node::Node;
    void cal();
    bool notconst(){
        return true;
    }
};

class Div : public Node{
public:
    using Node::Node;
    void cal();
    bool notconst(){
        return true;
    }
};

class Print : public Node{
public:
    using Node::Node;
    void cal();
    bool notconst(){
        return true;
    }
};

class Cond : public Node{
public:
    using Node::Node;
    void cal();
    bool notconst(){
        return true;
    }
};

class Sin : public Node{
public:
    using Node::Node;
    void cal();
    bool notconst(){
        return true;
    }
};

class Log : public Node{
public:
    using Node::Node;
    void cal();
    bool notconst(){
        return true;
    }
};

class Exp : public Node{
public:
    using Node::Node;
    void cal();
    bool notconst(){
        return true;
    }
};

class Tanh : public Node{
public:
    using Node::Node;
    void cal();
    bool notconst(){
        return true;
    }
};

class Sigmoid : public Node{
public:
    using Node::Node;
    void cal();
    bool notconst(){
        return true;
    }
};

class Greater : public Node{
public:
    using Node::Node;
    void cal();
    bool notconst(){
        return true;
    }
};

class Lesser : public Node{
public:
    using Node::Node;
    void cal();
    bool notconst(){
        return true;
    }
};

class Greater_e : public Node{
public:
    using Node::Node;
    void cal();
    bool notconst(){
        return true;
    }    
};

class Lesser_e : public Node{
public:
    using Node::Node;
    void cal();
    bool notconst(){
        return true;
    }
};

class Equal : public Node{
public:
    using Node::Node;
    void cal();
    bool notconst(){
        return true;
    }
};