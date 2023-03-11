#include <iostream>
#include <string>
#include <fstream>
#include <list>

using namespace std;
//3.00~3.30
class ListNode {
public:
    ListNode* Prev;
    ListNode* Next;
    ListNode* Rand; // произвольный элемент внутри списка
    string Data;

    explicit ListNode() : Prev(nullptr), Next(nullptr), Rand(nullptr) {}

    explicit ListNode(const string &data) : Data(data), Prev(nullptr), Next(nullptr), Rand(nullptr) {}

    ListNode(ListNode *prev, ListNode *next, ListNode *rand, const string &data) : Prev(prev), Next(next), Rand(rand),
                                                                                   Data(data) {}
};


class ListRand {
public:
    ListNode* Head;
    ListNode* Tail;
    int Count = 0;

    void Serialize(string path) {
        ofstream out(path);
        ListNode* curr = Head;
        char null = '\0';
        while(true){
            out << curr->Data << null;
            curr = curr->Next;
            if(curr == nullptr) break;
        }
        out.close();
    }

    void Deserialize(string path) {
        ifstream in(path);
        ListNode* curr = Head = new ListNode(), *prev;
        string text;
        char c, null = '\0';

        in.get(c);
        while(true){
            if(c == null){
                curr->Data = text;
                prev = curr;
                text.clear();
                Count++;

                if (!in.get(c)){
                    Tail = curr;
                    break;
                }

                curr = new ListNode();
                prev->Next = curr;
                curr->Prev = prev;
            }
            else {
                text.push_back(c);
                in.get(c);
            }
        }
        in.close();

        int indexes[Count], i = -1;
        generate(indexes, &indexes[Count], [&i](){return ++i;});
        srand(time(nullptr));

        for(int size = Count; size != 0;){
            int a = rand() % size, b = rand() % size;
            ListNode* first=getNode(indexes[a]), *second=getNode(indexes[b]);

            first->Rand = second;
            if(a == b){
                cout << "Check1"<<endl;
                indexes[a] = indexes[size-1];
                size--;
            }
            else {
                cout << "Check2"<<endl;
                if(b==size-2) indexes[a] = indexes[size-1];
                else indexes[a] = indexes[size-2];

                if(a==size-1) indexes[b] = indexes[size-2];
                else indexes[b] = indexes[size-1];

                size-=2;
                second->Rand = first;
            }
        }
    }

    ListNode* getNode(int num){
        if(num>=Count || num<0){
            srand(time(nullptr));
            num = rand() % Count;
        }

        ListNode* node = Head;
        for(;num>0;num--) node = node->Next;
        return node;
    }
};

int main() {
    //--------Example------
    ListRand list;
    list.Deserialize("test_file.bin");
    list.Serialize("test_file.bin");
    return 0;
}
