#include <iostream>
#include <stack>
#include <map>
#include <set>

std::map<char, int> priority;
std::string RPN_expression;
std::string result;
std::set<char> operators = {'+', '-', '*', '/'};

bool prior(char lhs, char rhs)
{
    return priority[lhs] >= priority[rhs];
}

void infix(std::string IN_expression)
{
    std::stack<char> st;
    for (char ch : IN_expression)
    {
        switch (ch)
        {
        case 'a' ... 'z':
        case 'A' ... 'Z':
            RPN_expression.push_back(ch);
            break;
        case '(':
            st.push(ch);
            break;
        case ')':
            while (st.top() != '(')
            {
                RPN_expression.push_back(st.top());
                st.pop();
            }
            st.pop();
            break;
        case '+':
        case '-':
        case '*':
        case '/':
            while (!st.empty() && prior(st.top(), ch))
            {
                RPN_expression.push_back(st.top());
                st.pop();
            }
            st.push(ch);
            break;
        default:
            break;
        }
    }
    while (!st.empty())
    {
        RPN_expression.push_back(st.top());
        st.pop();
    }
}

void reverse_polish(std::string RPN_expression)
{
    std::stack<std::string> st;
    std::string rhs, lhs;
    char prev;
    for (char ch : RPN_expression)
    {
        switch (ch)
        {
        case 'a' ... 'z':
        case 'A' ... 'Z':
            st.push(std::string(1, ch));
            break;
        case '+':
        case '-':
        case '*':
        case '/':
            rhs = st.top();
            st.pop();
            lhs = st.top();
            st.pop();
            st.push(lhs + std::string(1, ch) + rhs);
            prev = ch;
            break;
        default:
            break;
        }
    }
    result = st.top();
}

struct Node
{
    char val;
    Node *left;
    Node *right;
    Node(char ch) : val(ch), left(NULL), right(NULL) {}
};

Node *expression_tree(std::string RPN_expression)
{
    std::stack<Node *> st;
    Node *node, *lhs, *rhs;
    for (char ch : RPN_expression)
    {
        node = new Node(ch);
        switch (ch)
        {
        case 'a' ... 'z':
        case 'A' ... 'Z':
            st.push(node);
            break;
        case '+':
        case '-':
        case '*':
        case '/':
            rhs = st.top();
            st.pop();
            lhs = st.top();
            st.pop();

            node->left = lhs;
            node->right = rhs;
            st.push(node);
            break;
        default:
            break;
        }
    }
    node = st.top();
    st.pop();
    return node;
}

void traversal(Node *tree, int level)
{
    if (tree)
    {
        int llv, rlv;
        switch (tree->val)
        {
        case '*':
            llv = rlv = 4;
            break;
        case '/':
            llv = 4;
            rlv = 5;
            break;
        case '+':
            llv = rlv = 1;
            break;
        case '-':
            llv = 1;
            rlv = 2;
            break;
        }
        if (operators.find(tree->val) != operators.end() && level > llv)
        {
            result.push_back('(');
        }
        traversal(tree->left, llv);
        result.push_back(tree->val);
        traversal(tree->right, rlv);
        if (operators.find(tree->val) != operators.end() && level > llv)
        {
            result.push_back(')');
        }
    }
}

int main()
{
    std::string expression;
    std::cin >> expression;

    priority['+'] = 1;
    priority['-'] = 1;
    priority['*'] = 2;
    priority['/'] = 2;

    infix(expression);
    Node *expresssion_tree = expression_tree(RPN_expression);
    traversal(expresssion_tree, 0);

    std::cout << result << std::endl;
    return 0;
}
