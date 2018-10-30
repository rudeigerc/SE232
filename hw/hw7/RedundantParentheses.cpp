#include <iostream>
#include <map>
#include <set>
#include <stack>

std::map<char, int> priority = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};
std::set<char> operators = {'+', '-', '*', '/'};

std::string RPN_expression;
std::string result;

bool prior(char lhs, char rhs)
{
    return priority[lhs] >= priority[rhs];
}

// Shunting-yard algorithm
void shunting_yard(std::string IN_expression)
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

struct Element
{
    std::string val;
    int level;
};

// recover to infix expression
void reverse_polish(std::string RPN_expression)
{
    std::stack<Element> st;
    Element lhs, rhs;
    for (char ch : RPN_expression)
    {
        switch (ch)
        {
        case 'a' ... 'z':
        case 'A' ... 'Z':
            st.push(Element{std::string(1, ch), 0});
            break;
        case '+':
        case '-':
        case '*':
        case '/':
            rhs = st.top();
            st.pop();
            lhs = st.top();
            st.pop();
            st.push(Element{lhs.val + std::string(1, ch) + rhs.val});
            break;
        default:
            break;
        }
    }
    result = st.top().val;
}

// node of the expression tree
struct Node
{
    char val;
    Node *left;
    Node *right;
    Node(char ch) : val(ch), left(NULL), right(NULL) {}
};

// build a expression tree fromn RPN
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

// infix traversal
void traversal(Node *tree, int level)
{
    if (tree)
    {
        // give the priority level
        int llv, rlv;
        switch (tree->val)
        {
        case '+':
            llv = 1;
            rlv = 1;
            break;
        case '-':
            llv = 1;
            rlv = 2;
            break;
        case '*':
            llv = 3;
            rlv = 3;
            break;
        case '/':
            llv = 3;
            rlv = 4;
            break;
        default:
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

    shunting_yard(expression);

    // Method 1: Binary expression tree
    Node *expresssion_tree = expression_tree(RPN_expression);
    traversal(expresssion_tree, 0);

    // Method 2: Pure stack
    // reverse_polish(RPN_expression);

    std::cout << result << std::endl;
    return 0;
}
