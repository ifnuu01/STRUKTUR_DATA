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

Node *createNode();
void display(Node *front);
void enqueue(Node *&front, Node *&rear);
void dequeue(Node *&front);

int main()
{
    Node *FRONT = NULL, *REAR = NULL;
    int menu;
    while (menu != 4)
    {
        cout << ">> Program antrian bansos <<" << endl;
        cout << "1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\nMasukan pilihan: ";
        cin >> menu;
        switch (menu)
        {
        case 1:
            enqueue(FRONT, REAR);
            break;
        case 2:
            dequeue(FRONT);
            break;
        case 3:
            display(FRONT);
            break;
        case 4:
            break;
        default:
            cout << "Pilihan tidak ada\n";
        }
    }
    return 0;
}

Node *createNode()
{
    Node *newNode = new Node();
    cout << "Masukan nama: ";
    cin >> newNode->data.nama;
    cout << "Masukan nim : ";
    cin >> newNode->data.nim;
    cout << "Masukan ipk : ";
    cin >> newNode->data.ipk;
    newNode->next = NULL;
    return newNode;
}

void display(Node *front)
{
    if (!front)
    {
        cout << "Antrian Kosong\n";
        return;
    }
    while (front)
    {
        cout << "Nama: " << front->data.nama << "\nNIM : " << front->data.nim << "\nIPK : " << front->data.ipk << "\n";
        cout << "-----------------------------\n";
        front = front->next;
    }
}

void enqueue(Node *&front, Node *&rear)
{
    Node *nodeBaru = createNode();
    if (!front)
    {
        front = nodeBaru;
    }
    else
    {
        (rear)->next = nodeBaru;
    }
    rear = nodeBaru;
}

void dequeue(Node *&front)
{
    if (!front)
    {
        cout << "Antrian Kosong\n";
        return;
    }
    Node *temp = front;
    front = (front)->next;
    delete temp;
}
