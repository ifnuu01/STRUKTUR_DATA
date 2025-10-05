#include <iostream>
#include <queue>
#include <stack>
#include <sstream>
#include <string>

using namespace std;

// ====== Struktur Node untuk Binary Tree ======
struct Node
{
    int data;
    Node *left;
    Node *right;

    // Constructor untuk inisialisasi node baru
    Node(int val)
    {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// ====== Operasi Binary Search Tree (BST) ======

// Fungsi untuk menambahkan node baru ke dalam BST
Node *insert(Node *root, int val)
{
    if (root == nullptr)
    {
        return new Node(val);
    }
    if (val < root->data)
    {
        root->left = insert(root->left, val);
    }
    else if (val > root->data)
    {
        root->right = insert(root->right, val);
    }
    return root;
}

// Fungsi untuk mencari node dalam BST
Node *search(Node *root, int val)
{
    if (root == nullptr || root->data == val)
    {
        return root;
    }
    if (val < root->data)
    {
        return search(root->left, val);
    }
    return search(root->right, val);
}

// Fungsi bantuan untuk mencari node dengan nilai terkecil di subTree kanan (untuk operasi delete)
Node *findMinValueNode(Node *node)
{
    Node *current = node;
    while (current && current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

// Fungsi untuk menghapus node dari BST
Node *deleteNode(Node *root, int val)
{
    if (root == nullptr)
    {
        return root;
    }
    if (val < root->data)
    {
        root->left = deleteNode(root->left, val);
    }
    else if (val > root->data)
    {
        root->right = deleteNode(root->right, val);
    }
    else
    {
        if (root->left == nullptr)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }
        Node *temp = findMinValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// ====== Tree Traversal ======

// In-Order Traversal: Kiri -> Akar -> Kanan
void inorderTraversal(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}

// Pre-Order Traversal: Akar -> Kiri -> Kanan
void preorderTraversal(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    cout << root->data << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// Post-Order Traversal: Kiri -> Kanan -> Akar
void postorderTraversal(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->data << " ";
}

// Level-Order Traversal (BFS) menggunakan Queue
void bfs(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        Node *current = q.front();
        q.pop();
        cout << current->data << " ";
        if (current->left != nullptr)
        {
            q.push(current->left);
        }
        if (current->right != nullptr)
        {
            q.push(current->right);
        }
    }
}

// Fungsi untuk Pre-Order Traversal (DFS iteratif)
void dfs_iterative(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    stack<Node *> s; // Buat sebuah stack
    s.push(root);    // Masukkan root ke dalam stack

    while (!s.empty())
    {
        Node *current = s.top();
        s.pop();

        cout << current->data << " ";

        // Masukkan anak kanan lebih dulu agar anak kiri diproses lebih awal
        if (current->right != nullptr)
        {
            s.push(current->right);
        }
        if (current->left != nullptr)
        {
            s.push(current->left);
        }
    }
}

// ====== Utility: height dan deleteTree ======
int treeHeight(Node *root)
{
    if (root == nullptr)
        return 0;
    return 1 + max(treeHeight(root->left), treeHeight(root->right));
}

void deleteTree(Node *node)
{
    if (node == nullptr)
        return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// ====== Visualisasi Tree (top-down, sederhana) ======
void placeNode(vector<string> &canvas, Node *node, int level, int left, int right)
{
    if (node == nullptr || left > right)
        return;
    int mid = (left + right) / 2;

    // tulis nilai node (bisa >1 char)
    stringstream ss;
    ss << node->data;
    string s = ss.str();

    // tempatkan teks berpusat di mid
    int start = mid - (int)s.length() / 2;
    if (start < left)
        start = left;
    for (size_t i = 0; i < s.length() && start + (int)i <= right; ++i)
    {
        canvas[level].replace(start + i, 1, s.substr(i, 1));
    }

    // buat garis ke anak (pada baris berikutnya)
    if (node->left)
    {
        int childMid = (left + mid - 1) / 2;
        if (childMid < 0)
            childMid = 0;
        // garis miring ke kiri antara mid-1 .. childMid
        int slashPos = mid - 1;
        if (slashPos >= 0 && level + 1 < (int)canvas.size())
        {
            canvas[level + 1].replace(slashPos, 1, "/");
        }
    }
    if (node->right)
    {
        int childMid = (mid + 1 + right) / 2;
        int slashPos = mid + 1;
        if (slashPos <= right && level + 1 < (int)canvas.size())
        {
            canvas[level + 1].replace(slashPos, 1, "\\");
        }
    }

    // rekursif ke anak pada dua tingkat berikutnya: tiap node memakai 2 baris (nilai + garis)
    placeNode(canvas, node->left, level + 2, left, mid - 1);
    placeNode(canvas, node->right, level + 2, mid + 1, right);
}

void printTree(Node *root)
{
    if (root == nullptr)
    {
        cout << "(kosong)" << endl;
        return;
    }
    int h = treeHeight(root);
    int rows = max(1, h * 2 - 1);
    // lebar canvas berbasis 2^h untuk menghindari tumpang tindih
    int width = (1 << h) * 3;
    if (width < 20)
        width = 20; // minimal lebar
    if (width > 3096)
        width = 3096;

    vector<string> canvas(rows, string(width, ' '));
    placeNode(canvas, root, 0, 0, width - 1);

    // print canvas trimming trailing spasi tiap baris
    for (string &line : canvas)
    {
        int end = (int)line.find_last_not_of(' ');
        if (end == string::npos)
            cout << "\n";
        else
            cout << line.substr(0, end + 1) << "\n";
    }
}

// ====== Fungsi Utama dengan Menu ======
int main()
{
    Node *root = nullptr;
    int pilihan = 0;
    while (true)
    {
        cout << "\n=== MENU BST ===\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. Traversal (In/Pre/Post/BFS/DFS)\n";
        cout << "5. Tampilkan Tree (visual)\n";
        cout << "6. Isi contoh cepat (50,30,70,20,40,60,80)\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        if (!(cin >> pilihan))
        {
            cin.clear();
            cin.ignore();
            continue;
        }

        if (pilihan == 0)
            break;

        int val;
        switch (pilihan)
        {
        case 1:
            cout << "Masukkan nilai yang akan di-insert: ";
            cin >> val;
            root = insert(root, val);
            cout << "Berhasil insert " << val << "\n";
            break;
        case 2:
            cout << "Masukkan nilai yang akan di-delete: ";
            cin >> val;
            root = deleteNode(root, val);
            cout << "Selesai delete (jika ada) " << val << "\n";
            break;
        case 3:
            cout << "Masukkan nilai yang dicari: ";
            cin >> val;
            if (search(root, val) != nullptr)
                cout << "Nilai " << val << " ditemukan.\n";
            else
                cout << "Nilai " << val << " tidak ditemukan.\n";
            break;
        case 4:
            cout << "In-Order: ";
            inorderTraversal(root);
            cout << "\nPre-Order: ";
            preorderTraversal(root);
            cout << "\nPost-Order: ";
            postorderTraversal(root);
            cout << "\nBFS: ";
            bfs(root);
            cout << "\nDFS: ";
            dfs_iterative(root);
            cout << "\n";
            break;
        case 5:
            cout << "\nStruktur Tree saat ini:\n\n";
            printTree(root);
            break;
        case 6:
            root = insert(root, 50);
            insert(root, 30);
            insert(root, 70);
            insert(root, 20);
            insert(root, 40);
            insert(root, 60);
            insert(root, 80);
            cout << "Contoh tree dibuat.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
            break;
        }
    }
    deleteTree(root);
    root = nullptr;
    cout << "Keluar.\n";
    return 0;
}