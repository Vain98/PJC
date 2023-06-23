#include <iostream>
#include <utility> // swap (may be useful)
#include <string>

template <typename T>
class DLL
{
    struct Node
    {
        T data;
        Node *next;
        Node *prev;
    };
    Node *sent; // sentinel
public:
    DLL() : sent(new Node{T(), nullptr, nullptr})
    {
        sent->next = sent->prev = sent;
        sent->data = "empty";
    }

    bool empty()
    {
        if (sent->data != "empty")
            return false;
        return true;
    }

    void push_front(const T &t)
    {
        using std::cout;
        using std::endl;
        using std::string;
        if (empty())
        {
            Node *tmp = sent;
            tmp->data = t;
            tmp->next = nullptr;
            tmp->prev = nullptr;
            return;
        }
        Node *tmp = sent;
        Node *new_Node = new Node;
        new_Node->data = t;

        new_Node->next = sent;
        new_Node->prev = nullptr;

        if (tmp != NULL)
            tmp->prev = new_Node;

        sent = new_Node;
    };

    void push_back(const T &t)
    {
        using std::cout;
        using std::endl;
        using std::string;
        if (empty())
        {
            Node *tmp = sent;
            tmp->data = t;
            tmp->next = nullptr;
            tmp->prev = nullptr;
            return;
        }
        Node *tmp = sent;
        Node *newNode = new Node;
        newNode->data = t;
        Node *last = sent;

        newNode->next = nullptr;

        if (tmp == nullptr)
        {
            newNode->prev = nullptr;
            tmp = newNode;
            return;
        }

        while (last->next != nullptr)
            last = last->next;

        last->next = newNode;
        newNode->prev = last;
    };

    void print_fwd(std::ostream &str = std::cout)
    {
        using std::cout;
        using std::endl;
        using std::string;
        Node *tmp = sent;
        while (tmp->next != nullptr)
        {
            cout << tmp->data << "  ";
            tmp = tmp->next;
        }
        cout << tmp->data << endl;
    };

    void print_rev(std::ostream &str = std::cout)
    {
        using std::cout;
        using std::endl;
        using std::string;
        Node *tmp = sent;
        while (tmp->next != nullptr)
        {
            tmp = tmp->next;
        }

        Node *last = tmp;
        while (last)
        {
            cout << last->data << "  ";
            last = last->prev;
        }
    };
    Node *find_first(const T &e)
    {
        Node *tmp = sent;
        while (tmp->data != e)
        {
            tmp = tmp->next;
        }
        return tmp;
    }
    Node *find_last(const T &e)
    {
        Node *tmp = sent;
        while (tmp->next != nullptr)
        {
            tmp = tmp->next;
        }

        Node *last = tmp;
        while (last->data != e)
        {
            last = last->prev;
        }
        return last;
    }
    void insert_after(Node *a, const T &t)
    {
        Node *newNode = new Node;
        newNode->data = t;
        newNode->next = a->next;
        a->next = newNode;
        newNode->prev = a;
        if (newNode->next != nullptr)
            newNode->next->prev = newNode;
    }
    void insert_before(Node *b, const T &t)
    {
        Node *new_node = new Node;
        new_node->data = t;
        new_node->prev = b->prev;
        b->prev = new_node;
        new_node->next = b;
        if (new_node->prev != NULL)
            new_node->prev->next = new_node;
        else
            sent = new_node;
    }
    void delete_node(const Node *d)
    {
        using std::cout;
        using std::endl;
        using std::string;
        d->prev->next = d->next;
        d->next->prev = d->prev;
        cout << "DEL: " << d->data << "  ";
    }
    void reverse()
    {
        Node *tmp = nullptr;
        Node *current = sent;

        while (current != nullptr)
        {
            tmp = current->prev;
            current->prev = current->next;
            current->next = tmp;
            current = current->prev;
        }

        if (tmp != NULL)
            sent = tmp->prev;
    }
    void clear()
    {
        using std::cout;
        using std::endl;
        using std::string;
        Node *tmp = sent;
        while (tmp->next != nullptr)
        {
            cout << "DEL: " << tmp->data << "  ";
            tmp = tmp->next;
        }
        cout << "DEL: " << tmp->data << endl;
        sent = new Node;
        sent->data = "empty";
    }
    ~DLL()
    {
        clear();
        sent = new Node;
        sent->data = "empty";
    }
};

int main()
{
    using std::cout;
    using std::endl;
    using std::string;
    DLL<std::string> *listStr = new DLL<std::string>();
    listStr->push_back("X");
    listStr->push_back("E");
    listStr->push_front("C");
    listStr->push_front("X");
    listStr->push_front("A");
    cout << "List printed in both directions:" << endl;
    listStr->print_fwd();
    listStr->print_rev();
    cout << endl;
    listStr->delete_node(listStr->find_first("X"));
    listStr->delete_node(listStr->find_last("X"));
    cout << "\nList after deleting X's:" << endl;
    listStr->print_fwd();

    listStr->insert_after(listStr->find_first("A"), "B");
    listStr->insert_before(listStr->find_last("E"), "D");
    cout << "List after inserting B and D:" << endl;
    listStr->print_fwd();

    listStr->reverse();
    cout << "List after reversing:" << endl;
    listStr->print_fwd();

    std::cout << "Is list empty? " << std::boolalpha
              << listStr->empty() << std::endl;

    std::cout << "Clearing the list" << std::endl;
    listStr->clear();

    std::cout << "Adding one element (Z)" << std::endl;
    listStr->push_front("Z");
    std::cout << "Deleting the list" << std::endl;
    delete listStr;
}