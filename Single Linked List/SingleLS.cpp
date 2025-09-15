#include <iostream>
using namespace std;

struct Mahasiswa
{
    string nama;
    string prodi;
    int nim;
};

struct Node
{
    Mahasiswa mhs;
    Node *next;
};

void transversal(Node *head)
{
    if (head == nullptr)
    {
        cout << "Kosong bang ga ada isinya" << endl;
    }

    Node *temp = head;
    while (temp != nullptr)
    {
        cout << "Nama : " << temp->mhs.nama << endl;
        cout << "Prodi : " << temp->mhs.prodi << endl;
        cout << "Nim : " << temp->mhs.nim << endl;
        temp = temp->next;
        cout << endl;
    }
    cout << "Dah habis bang" << endl;
}

void addFirst(Node *&head, Node *&tail, string nama, string prodi, int nim)
{
    Node *newNode = new Node;

    newNode->mhs.nama = nama;
    newNode->mhs.prodi = prodi;
    newNode->mhs.nim = nim;
    newNode->next = head;

    head = newNode;

    if (tail == nullptr)
    {
        tail = newNode;
    }
}

void addLast(Node *&head, Node *&tail, string nama, string prodi, int nim)
{
    Node *newNode = new Node;

    newNode->mhs.nama = nama;
    newNode->mhs.prodi = prodi;
    newNode->mhs.nim = nim;
    newNode->next = nullptr;

    if (tail != nullptr)
    {
        tail->next = newNode;
    }
    else
    {
        head = newNode;
    }
    tail = newNode;
}

void addSpecific(Node *&head, Node *&tail, int posisi, string nama, string prodi, int nim)
{
    if (posisi < 1)
    {
        cout << "Mana ada posisi mines bang" << endl;
        return;
    }

    if (posisi == 1)
    {
        addFirst(head, tail, nama, prodi, nim);
        return;
    }

    Node *temp = head;
    int hitung = 1;
    while (temp != nullptr && hitung < posisi - 1)
    {
        temp = temp->next;
        hitung++;
    }

    if (temp == nullptr)
    {
        cout << "Kelebihan bang posisinya dari panjang linked list" << endl;
    }
    else if (temp->next == nullptr)
    {
        addLast(head, tail, nama, prodi, nim);
    }
    else
    {
        Node *newNode = new Node;
        newNode->mhs.nama = nama;
        newNode->mhs.prodi = prodi;
        newNode->mhs.nim = nim;

        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void deleteFirst(Node *&head, Node *&tail)
{
    if (head == nullptr)
    {
        cout << "Masih kosong bang" << endl;
        return;
    }

    Node *temp = head;
    head = temp->next;
    delete temp;
    if (head == nullptr)
    {
        tail = nullptr;
    }
}

void deleteLast(Node *&head, Node *&tail)
{
    if (head == nullptr)
    {
        cout << "Masih kosong bang" << endl;
        return;
    }

    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        cout << "Berhasil kehapus" << endl;
        return;
    }

    Node *temp = head;
    while (temp->next->next != nullptr)
    {
        temp = temp->next;
    }

    tail = temp;
    delete temp->next;
    tail->next = nullptr;
    cout << "Berhasil kehapus" << endl;
}

void deleteSpecific(Node *&head, Node *&tail, int posisi)
{
    if (posisi < 1)
    {
        cout << "Mana ada posisi mines bang" << endl;
        return;
    }

    if (posisi == 1)
    {
        deleteFirst(head, tail);
        return;
    }

    Node *temp = head;
    int hitung = 1;
    while (temp != nullptr && hitung < posisi - 1)
    {
        temp = temp->next;
        hitung++;
    }

    if (temp == nullptr)
    {
        cout << "Kelebihan bang posisinya dari panjang linked list" << endl;
    }
    else if (temp->next == nullptr)
    {
        deleteLast(head, tail);
    }
    else
    {
        Node *deleteNode = temp->next;
        temp->next = deleteNode->next;
        delete deleteNode;
    }
}

void edit(Node *&head, Node *&tail, int posisi, string nama, string prodi, int nim)
{
    if (posisi < 1)
    {
        cout << "Mana ada posisi mines bang" << endl;
        return;
    }

    if (posisi == 1)
    {
        head->mhs.nama = nama;
        head->mhs.prodi = prodi;
        head->mhs.nim = nim;
        return;
    }

    Node *temp = head;
    int hitung = 1;
    while (temp != nullptr && hitung < posisi - 1)
    {
        temp = temp->next;
        hitung++;
    }

    if (temp == nullptr)
    {
        cout << "Kelebihan bang posisinya dari panjang linked list" << endl;
    }
    else
    {
        temp->next->mhs.nama = nama;
        temp->next->mhs.prodi = prodi;
        temp->next->mhs.nim = nim;
    }
}

int main()
{
    Node *tail = nullptr;
    Node *head = nullptr;

    Node *first = new Node;
    first->mhs.nama = "Ucup";
    first->mhs.prodi = "Informatika";
    first->mhs.nim = 20;
    first->next = nullptr;
    head = first;
    tail = first;

    Node *mid = new Node;

    mid->mhs.nama = "Ismail";
    mid->mhs.prodi = "Informatika";
    mid->mhs.nim = 30;
    mid->next = nullptr;
    head->next = mid;
    tail = mid;

    Node *last = new Node;

    last->mhs.nama = "Samsudin";
    last->mhs.prodi = "Informatika";
    last->mhs.nim = 30;
    last->next = nullptr;
    mid->next = last;
    tail = last;

    transversal(head);
    addFirst(head, tail, "Dwiki", "Informatika", 1);
    cout << endl;
    cout << "After" << endl;
    transversal(head);
    cout << endl;
    cout << "After Versi 2" << endl;
    addLast(head, tail, "Tedy", "Informatika", 1);
    transversal(head);
    cout << "After Versi 3" << endl;
    addSpecific(head, tail, 3, "Ricky Anggari", "Informatika", 2);
    transversal(head);
    deleteFirst(head, tail);
    deleteLast(head, tail);
    cout << "After Versi 4" << endl;
    transversal(head);
    deleteSpecific(head, tail, 2);
    cout << "After Versi 5" << endl;
    transversal(head);
    edit(head, tail, 2, "Ifnu", "Informatika", 60);
    cout << "After Versi 6" << endl;
    transversal(head);

    return 0;
}
