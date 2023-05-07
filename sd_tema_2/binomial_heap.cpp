#include <fstream>
#include <list>
#include <queue>


using namespace std;
ifstream in("mergeheap.in");
ofstream out("mergeheap.out");

class BinomialHeap
{
private:
    class Node {
    public:
        int value;
        int grad;
        Node* child;
        Node* sibling;
        Node* parent;

        Node() : value(0), grad(0), child(nullptr), sibling(nullptr), parent(nullptr) {}
        Node(int val) : value(val), grad(0), child(nullptr), sibling(nullptr), parent(nullptr) {}
    };

    list <Node*> heap;


    /*Node* get_max() {

        Node* vmax = new Node;
        vmax->value = -1;

        Node* root = nullptr;
        for (Node* n : heap) {
            if (n->value > vmax->value) {
                vmax = n;
                root = n;
            }
        }
        return root;
    }*/




    Node* mergetree(Node* t1, Node* t2)
    {
        /*if (t1 == nullptr || t2 == nullptr) {
            return;
        }*/

        if (t2->value > t1->value) {
            Node* aux = t1;
            t1 = t2;
            t2 = aux;
        }

        t2->sibling = t1->child;
        t1->grad++;
        t2->parent = t1;
        t1->child = t2;

        return t1;
    }



    void adjust() {


        if (heap.size() <= 1) {
            return;
        }

        heap.sort([](Node* a, Node* b) {
            if (a->grad == b->grad) {
                return a->grad < b->grad;
            }
            else {
                return a->grad < b->grad;
            }
            });

        auto ant = heap.begin();
        auto curr = ant;
        curr++;
        auto urm = curr;
        urm++;

        do {
            if (curr != heap.end())
            {
                if (urm != heap.end()) 
                {
                    if ((*ant)->grad == (*curr)->grad && (*curr)->grad != (*urm)->grad) 
                    {
                        *ant = mergetree(*ant, *curr);
                        curr = heap.erase(curr);
                        urm++;
                    }
                    else 
                    {
                        ant++;
                        curr++;
                        urm++;
                    }
                }
                else if ((*ant)->grad == (*curr)->grad) 
                {
                    *ant = mergetree(*ant, *curr);
                    heap.pop_back();
                    curr = heap.end();
                }
                else 
                {
                    ant++;
                    curr++;
                    urm++;
                }
            }
        } while (curr != heap.end());

    }




public:
    void insert(int val) {

        Node* tree = new Node;
        tree->value = val;
        heap.push_back(tree);
        adjust();
    }


    /*int top() {
        return (*get_max()).value;
    }*/




    void MergeHeap(BinomialHeap& heap2) {
        list<Node*> heapFinal;

        Node* h1_node;
        if (heap.empty())
            h1_node = nullptr;

        else
            h1_node = heap.front();


        Node* h2_node;
        if (heap2.heap.empty())
            h2_node = nullptr;

        else
            h2_node = heap2.heap.front();


        while (h1_node != nullptr && h2_node != nullptr)
            if (h1_node->grad <= h2_node->grad)
            {
                heapFinal.push_back(h1_node);
                heap.pop_front();
                if (heap.empty())
                    h1_node = nullptr;

                else
                    h1_node = heap.front();

            }
            else
            {
                heapFinal.push_back(h2_node);
                heap2.heap.pop_front();
                if (heap2.heap.empty())
                    h2_node = nullptr;

                else
                    h2_node = heap2.heap.front();

            }


        while (h1_node != nullptr) {
            heapFinal.push_back(h1_node);
            heap.pop_front();

            if (heap.empty())
                h1_node = nullptr;

            else
                h1_node = heap.front();


        }

        while (h2_node != nullptr) {
            heapFinal.push_back(h2_node);
            heap2.heap.pop_front();

            if (heap2.heap.empty())
                h2_node = nullptr;

            else
                h2_node = heap2.heap.front();

        }

        heap = heapFinal;
        adjust();
    }


    int extract_max() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }

        Node* vmax = new Node;
        vmax->value = -1;

        Node* max_node = nullptr;
        Node* root = nullptr;
        for (Node* n : heap) {
            if (n->value > vmax->value) {
                vmax = n;
                max_node = n;
                root = n;
            }
        }

        int max_value = max_node->value;

        heap.remove(max_node);

        Node* child = max_node->child;
        while (child != nullptr) {
            Node* sibling = child->sibling;
            child->sibling = nullptr;
            heap.push_front(child);
            child = sibling;
        }

        adjust();
        return max_value;
    }




    /*void print_heap() {
        for (Node* n : heap) {
            queue<Node*> q;
            q.push(n);
            while (!q.empty()) {
                Node* curent = q.front();
                q.pop();
                out << curent->value << " ";
                if (curent->child != nullptr) {
                    q.push(curent->child);
                    Node* sibling = curent->child->sibling;
                    while (sibling != nullptr) {
                        q.push(sibling);
                        sibling = sibling->sibling;
                    }
                }
            }
            out << endl;
        }
    }*/


};

int N, Q, nop, poz1, poz2;
BinomialHeap heap[105];

int main()
{


    in >> N >> Q;
    for (int i = 1; i <= Q; i++)
    {
        in >> nop;
        if (nop == 1)
        {
            in >> poz1 >> poz2;
            heap[poz1].insert(poz2);
        }
        if (nop == 2)
        {
            in >> poz1;
            out << heap[poz1].extract_max();
            out << endl;
        }
        if (nop == 3)
        {
            in >> poz1 >> poz2;
            heap[poz1].MergeHeap(heap[poz2]);
        }
    }


    return 0;
    }