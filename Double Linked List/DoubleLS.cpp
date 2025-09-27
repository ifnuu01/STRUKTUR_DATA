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
    Node *prev;
    Node *next;
};

void transversal(Node *head)
{
    if (head == nullptr)
    {
        cout << "Double Linked List Kosong" << endl;
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

void reverseTransversal(Node *tail)
{
    if (tail == nullptr)
    {
        cout << "Double Linked List Kosong" << endl;
    }

    Node *temp = tail;
    while (temp != nullptr)
    {
        cout << "Nama : " << temp->mhs.nama << endl;
        cout << "Prodi : " << temp->mhs.prodi << endl;
        cout << "Nim : " << temp->mhs.nim << endl;
        temp = temp->prev;
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
    newNode->prev = nullptr;
    newNode->next = head;

    if (head != nullptr)
        head->prev = newNode;
    else
        tail = newNode;

    head = newNode;
}

void addLast(Node *&head, Node *&tail, string nama, string prodi, int nim)
{
    Node *newNode = new Node;
    newNode->mhs.nama = nama;
    newNode->mhs.prodi = prodi;
    newNode->mhs.nim = nim;
    newNode->next = nullptr;
    newNode->prev = tail;

    if (tail != nullptr)
        tail->next = newNode;
    else
        head = newNode;

    tail = newNode;
}

void addSpecific(Node *&head, Node *&tail, int posisi, string nama, string prodi, int nim)
{
    if (posisi < 1)
    {
        cout << "Posisi yang anda minta mines" << endl;
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
        cout << "Posisi yang diminta melebihi panjang Linked List" << endl;
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
        newNode->prev = temp;
        temp->next->prev = newNode;
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
    head = head->next;
    if (head != nullptr)
        head->prev = nullptr;
    else
        tail = nullptr;
    delete temp;
}

void deleteLast(Node *&head, Node *&tail)
{
    if (tail == nullptr)
    {
        cout << "Masih kosong bang" << endl;
        return;
    }
    Node *temp = tail;
    tail = tail->prev;
    if (tail != nullptr)
        tail->next = nullptr;
    else
        head = nullptr;
    delete temp;
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
    while (temp != nullptr && hitung < posisi)
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
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
    }
}

void edit(Node *&head, Node *&tail, int posisi, string nama, string prodi, int nim)
{
    if (posisi < 1)
    {
        cout << "Mana ada posisi mines bang" << endl;
        return;
    }
    Node *temp = head;
    int hitung = 1;
    while (temp != nullptr && hitung < posisi)
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
        temp->mhs.nama = nama;
        temp->mhs.prodi = prodi;
        temp->mhs.nim = nim;
    }
}

int main()
{

    Node *head = nullptr;
    Node *tail = nullptr;

    addLast(head, tail, "Ucup", "Informatika", 20);
    addLast(head, tail, "Ismail", "Informatika", 30);
    addLast(head, tail, "Samsudin", "Informatika", 30);

    // Menambahkan data di awal
    transversal(head);
    addFirst(head, tail, "Dwiki", "Informatika", 1);
    cout << endl
         << "Setelah ditambah di awal" << endl;
    transversal(head);

    // Menambahkan data di akhir
    cout << endl
         << "Setelah ditambah di akhir" << endl;
    addLast(head, tail, "Tedy", "Informatika", 1);
    transversal(head);

    // Menambahkan data di tengah
    cout << "Setelah ditambah di tengah" << endl;
    addSpecific(head, tail, 3, "Ricky Anggari", "Informatika", 2);
    transversal(head);

    // Menghapus data di awal
    deleteFirst(head, tail);

    // Menghapus data di akhir
    deleteLast(head, tail);
    cout << "Setelah dihapus di akhir" << endl;
    transversal(head);

    // Menghapus data di tengah
    deleteSpecific(head, tail, 2);
    cout << "Setelah dihapus di tengah" << endl;
    transversal(head);

    // edit data
    edit(head, tail, 2, "Ifnu", "Informatika", 60);
    cout << "Setelah diedit" << endl;
    transversal(head);

    cout << "Setelah dibalik" << endl;
    reverseTransversal(tail);

    return 0;
}