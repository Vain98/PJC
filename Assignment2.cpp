#include <iostream>
#include <string>
using namespace std;
template <typename T>
struct Node {
    T data;
    Node* next;
};

template <typename T>
void showList(const Node<T>* head) {

    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;

};

template <typename T>
Node<T>* arrayToList(const T a[], size_t size){


    Node<T>* head;
    head = nullptr;
    for (int i = size-1;i > -1 ; i--){
        Node<T>* new_node  = new Node<T>;
        new_node->data = a[i];
        new_node->next = nullptr;

        if (head == nullptr) {
            head = new_node;

        }
        else
        {
            new_node->next = head;
            head = new_node;
        }
    }
    return head;
};

template <typename T, typename Pred>
Node<T>* extract(Node<T>*& head, Pred pred) {
    Node<T> *predHead = nullptr;
    Node<T> *newHead = nullptr;

    while (head != nullptr) {
        if (pred(head->data)) {
            Node<T> *new_node = new Node<T>;
            new_node->data = head->data;
            new_node->next = nullptr;
            if (predHead == nullptr) {
                predHead = new_node;

            } else {
                new_node->next = predHead;
                predHead = new_node;
            }
        } else {
            Node<T> *new_node = new Node<T>;
            new_node->data = head->data;
            new_node->next = nullptr;

            if (newHead == nullptr) {
                newHead = new_node;

            } else {
                new_node->next = newHead;
                newHead = new_node;
            }
        }
        head = head->next;
    }

    Node<T> *current = predHead;
    Node<T>* next;
    Node<T>* prev = nullptr;
    while (current != nullptr)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current= next;
    }
    predHead = prev;

    current = newHead;
    prev= nullptr;
    while (current != nullptr)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current= next;
    }
    head = prev;
    return predHead;
};

template <typename T>
void deleteList(Node<T>*& head){

    Node<T>* tmp = head;
    while (tmp->next != nullptr)
    {
        cout << "DEL: " << tmp->data << "  ";
        tmp = tmp->next;
    }
    cout << "DEL: " << tmp->data << endl;
    head = nullptr;
};

bool isLong(const std::string& s) { return s.size() >= 5; }

int main() {
    int tabi[] = {2, 1, 4, 3, 6, 5, 7, 8};
    size_t sizei = sizeof(tabi) / sizeof(tabi[0]);
    Node<int> *listAi = arrayToList(tabi, sizei);
    showList(listAi);
    Node<int> *listBi = extract(listAi,
                                [](int n) {
                                    return n % 2 == 0;
                                });
    showList(listBi);
    showList(listAi);
    deleteList(listBi);
    deleteList(listAi);

    std::string tabs[]{"Kasia", "Ola", "Ala",
                       "Zosia", "Ela", "Basia"};
    size_t sizes = sizeof(tabs) / sizeof(tabs[0]);
    Node<std::string> *listAs = arrayToList(tabs, sizes);
    showList(listAs);
    Node<std::string> *listBs = extract(listAs, isLong);
    showList(listBs);
    showList(listAs);
    deleteList(listBs);
    deleteList(listAs);
}