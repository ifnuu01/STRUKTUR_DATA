#include <iostream>
using namespace std;

struct Mahasiswa
{
    string nama;
    int nim;
    double ipk;
};
struct Node
{
    Mahasiswa data;
    Node *next;
};

Node *createNode()
{
    Node *newNode = new Node();
    cout << "Masukan nama : ";
    cin >> newNode->data.nama;
    cout << "Masukan nim  : ";
    cin >> newNode->data.nim;
    cout << "Masukan ipk  : ";
    cin >> newNode->data.ipk;
    return newNode;
}

void push(Node **top)
{
    Node *nodeBaru = createNode();
    nodeBaru->next = *top;
    *top = nodeBaru;
}

void pop(Node **top)
{
    if (*top == NULL)
    {
        cout << "Stack underflow\n";
        return;
    }
    Node *temp = *top;
    *top = (*top)->next;
    delete temp;
}
void display(Node *top)
{
    if (!top)
    {
        cout << "Stack kosong\n";
        return;
    }
    while (top)
    {
        cout << "Nama : " << top->data.nama << "\n";
        cout << "NIM  : " << top->data.nim << "\n";
        cout << "IPK  : " << top->data.ipk << "\n";
        cout << "-----------------------------\n";
        top = top->next;
    }
}

int main()
{
    Node *TOP = NULL;
    int menu;

    do
    {
        cout << "1. Push\n2. Pop\n3. Display\n4. Exit\nMasukan pilihan: ";
        cin >> menu;
        switch (menu)
        {
        case 1:
            push(&TOP);
            break;
        case 2:
            pop(&TOP);
            break;
        case 3:
            display(TOP);
            break;
        case 4:
            break;
        default:
            cout << "Pilihan tidak ada\n";
        }
    } while (menu != 4);

    return 0;
}
