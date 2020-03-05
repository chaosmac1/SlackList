//
// Created by chaosmac on 20.01.20.
//

#ifndef EQ_SLACKLIST_H
#define EQ_SLACKLIST_H

#include <Arduino.h>

template <class T>
class List {
    struct Node {
        T * Data;
        int ID;
        Node * Next;
    };

    Node * HeadEnd;
    Node * HeadStart;
    int Size = 0;

    Node * GetNode(int num) {
        if(Size >= 0 && num >= 0) {
            Node * n = HeadStart;
            while (true) {
                //cout << n->ID << " " <<"\n";
                if(num == n->ID) {
                    return n;
                }

                n = n->Next;

            }
        }
        else {
            return NULL;
        }
    }

    void RepairIDAt(Node * node) {
        int zahler = node->ID +1;
        node = node->Next;
        while (zahler < Size) {
            node->ID = zahler;
            node = node->Next;
            zahler++;
        }
    }

public:
    struct SizeArray {
        T ** Array;
        int Size;
    };

    T * Get(int num) {
        if(Size >= 0 && num >= 0) {
            Node * n = HeadStart;
            while (true) {
                if(num == n->ID) {
                    return n->Data;
                }

                n = n->Next;

            }
        }
    }

    T * Pop() {
        if (Size == 1) {
            Node * node = HeadStart;
            HeadStart = NULL;
            HeadEnd = NULL;
            Size = 0;
            return  node->Data;
        }
        else {
            Node * node = GetNode(Size -2);
            T * returnWert = node->Next->Data;
            HeadEnd = node;
            node->Next = NULL;
            Size--;
            return returnWert;
        }
    }

    T * Pop(int num) {
        if (num == Size -1) {
            if (Size == 1) {
                Node * node = HeadEnd;
                HeadEnd = NULL;
                HeadStart = NULL;
                Size = 0;
                return node->Data;
            }
            Node * node = GetNode(Size -2);
            T * returnWert = node->Next->Data;
            HeadEnd = node;
            node->Next = NULL;
            Size--;
            return returnWert;
        }
        else if (num == 0) {
            T * returnWert = HeadStart->Data;
            HeadStart = HeadStart->Next;
            Size--;
            HeadStart->ID = 0;
            RepairIDAt(HeadStart);
            return returnWert;
        }

        else {
            Node * oneLowerNode = GetNode(num -1);
            Node * node = oneLowerNode->Next;
            Node * oneHighNode = node->Next;

            T * returnWert = node->Data;

            oneLowerNode->Next = oneHighNode;
            Size--;
            RepairIDAt(oneLowerNode);
            return returnWert;
        }
    }

    SizeArray GetAll() {
        T * returnData [Size];

        Node * head = HeadStart;
        for(int i = 0; i < Size; i++) {
            returnData[i] = head->Data;
            head = head->Next;
        }

        SizeArray returnWert;
        returnWert.Array = returnData;
        returnWert.Size = Size;
        return returnWert;
    }

    int GetSize() { return Size; }

    void Add(T * obj) {
        if (Size == 0) {
            Node * n = new Node;
            n->ID = Size;
            n->Data = obj;
            HeadEnd = n;
            HeadStart = n;
        }

        else {
            Node * n = new Node;
            n->Data = obj;
            n->ID = Size;
            HeadEnd->Next = n;
            HeadEnd = HeadEnd->Next;

        }
        Size++;
    }

    void AddAt(int index, T * obj) {
        /// Großer als 0
        if (index > 0) {
            Node * oneLowerNode = GetNode(index -1);
            Node * splitNode = oneLowerNode->Next;

            Node * newNode = new Node;
            newNode->Data = obj;
            oneLowerNode->Next = newNode;
            newNode->Next = splitNode;

            if (Size == index) {
                HeadEnd = newNode;
            }
            Size++;

            RepairIDAt(oneLowerNode);
        }
        /// Wenn bei 0 was hinzukommen soll
        else {
            Node * newNode = new Node;
            newNode->Data = obj;
            newNode->ID = 0;
            newNode->Next = HeadStart;
            HeadStart = newNode;
            Size++;
            RepairIDAt(HeadStart);
        }
    }

    void AddEmptyNodes(int size) {
        int zahler = Size + size;
        Node * nodeRepairAt = HeadEnd;

        while(Size != zahler) {
            Node * node;
            node = new Node;
            node->ID = Size;
            HeadEnd->Next = node;
            HeadEnd = node;
            Size++;
        }
        RepairIDAt(nodeRepairAt);
    }

    void RemoveAt(int num) {
        Node * oneLowerAtNum;
        if (Size > 0 && num > 0) /* if High then 0 */ {
            oneLowerAtNum = HeadStart;
            while (true) /* Node is Found */ {
                if (oneLowerAtNum->ID +1 == num) {
                    if (Size != num +1 ) {
                        oneLowerAtNum->Next = oneLowerAtNum->Next->Next;
                        Size--;
                        uint16_t zahler = oneLowerAtNum->ID +1;
                        uint16_t zahlerEnd = Size;
                        Node * nodeHead = oneLowerAtNum->Next;

                        while(zahler != zahlerEnd) {
                            nodeHead->ID = zahler;
                            nodeHead = nodeHead->Next;
                            zahler++;
                        }
                        return;
                    }
                    oneLowerAtNum->Next = NULL;
                    return;
                }
                else /* next Node */ {
                    oneLowerAtNum = oneLowerAtNum->Next;
                    return;
                }
            }
        }
        else /* if Remove Node 0*/ {
            if (Size == 1) {
                HeadStart = NULL;
                HeadEnd = NULL;
                Size = 0;
            } else {
                HeadStart = HeadStart->Next;
                HeadStart->ID = 0;
                Size--;
                RepairIDAt(HeadStart);
            }
        }
    }

    void Push(int from, int to) {
        Node * _from = GetNode(from);
        Node * _to = GetNode(to);

        T * _fromT = _from->Data;
        T * _toT = _to->Data;

        _from->Data = _toT;
        _to->Data = _fromT;
    }

    void OverwriteElement(int index, T * obj) {
        GetNode(index)->Data = obj;
    }

    void Clear() {
        Size = 0;
        HeadStart = NULL;
        HeadEnd = NULL;
    }

    void PassList(void (*func)(T& data)) {
        int zahler = 0;
        Node * node = HeadStart;
        while (zahler != Size) {
            func(*node->Data);
            node = node->Next;
            zahler++;
        }
    }

    template<class U>
    void PassListInput(U input,void(*func)(T& data, U input)) {
        int zahler = 0;
        Node * node = HeadStart;
        while (zahler != Size) {
            func(*node->Data, input);
            node = node->Next;
            zahler++;
        }
    }
};


template <class T>
class List_uint16_t {
    struct Node {
        T * Data;
        int ID;
        Node * Next;
    };

    Node * HeadEnd;
    Node * HeadStart;
    uint16_t Size = 0;

    Node * GetNode(uint16_t num) {
        if(Size >= 0 && num >= 0) {
            Node * n = HeadStart;
            while (true) {
                //cout << n->ID << " " <<"\n";
                if(num == n->ID) {
                    return n;
                }

                n = n->Next;

            }
        }
        else {
            return NULL;
        }
    }

    void RepairIDAt(Node * node) {
        uint16_t zahler = node->ID +1;
        node = node->Next;
        while (zahler < Size) {
            node->ID = zahler;
            node = node->Next;
            zahler++;
        }
    }


public:
    struct SizeArray {
        T ** Array;
        uint16_t Size;
    };

    T * Get(uint16_t num) {
        if(Size >= 0 && num >= 0) {
            Node * n = HeadStart;
            while (true) {
                if(num == n->ID) {
                    return n->Data;
                }

                n = n->Next;

            }
        }
    }

    T * Pop() {
        if (Size == 1) {
            Node * node = HeadStart;
            HeadStart = NULL;
            HeadEnd = NULL;
            Size = 0;
            return  node->Data;
        }
        else {
            Node * node = GetNode(Size -2);
            T * returnWert = node->Next->Data;
            HeadEnd = node;
            node->Next = NULL;
            Size--;
            return returnWert;
        }
    }

    T * Pop(uint16_t num) {
        if (num == Size -1) {
            if (Size == 1) {
                Node * node = HeadEnd;
                HeadEnd = NULL;
                HeadStart = NULL;
                Size = 0;
                return node->Data;
            }
            Node * node = GetNode(Size -2);
            T * returnWert = node->Next->Data;
            HeadEnd = node;
            node->Next = NULL;
            Size--;
            return returnWert;
        }
        else if (num == 0) {
            T * returnWert = HeadStart->Data;
            HeadStart = HeadStart->Next;
            Size--;
            HeadStart->ID = 0;
            RepairIDAt(HeadStart);
            return returnWert;
        }

        else {
            Node * oneLowerNode = GetNode(num -1);
            Node * node = oneLowerNode->Next;
            Node * oneHighNode = node->Next;

            T * returnWert = node->Data;

            oneLowerNode->Next = oneHighNode;
            Size--;
            RepairIDAt(oneLowerNode);
            return returnWert;
        }
    }

    SizeArray GetAll() {
        SizeArray returnWert;

        returnWert.Array = new T * [Size];
        returnWert.Size = Size;

        Node * head = HeadStart;
        for(uint16_t i = 0; i < Size; i++) {
            returnWert.Array[i] = head->Data;
            head = head->Next;
        }

        return returnWert;
    }

    int GetSize() { return Size; }

    void Add(T * obj) {
        if (Size == 0) {
            Node * n = new Node;
            n->ID = Size;
            n->Data = obj;
            HeadEnd = n;
            HeadStart = n;
        }

        else {
            Node * n = new Node;
            n->Data = obj;
            n->ID = Size;
            HeadEnd->Next = n;
            HeadEnd = HeadEnd->Next;

        }
        Size++;
    }

    void AddAt(uint16_t index, T * obj) {
        /// Großer als 0
        if (index > 0) {
            Node * oneLowerNode = GetNode(index -1);
            Node * splitNode = oneLowerNode->Next;

            Node * newNode = new Node;
            newNode->Data = obj;
            oneLowerNode->Next = newNode;
            newNode->Next = splitNode;

            if (Size == index) {
                HeadEnd = newNode;
            }
            Size++;

            RepairIDAt(oneLowerNode);
        }
            /// Wenn bei 0 was hinzukommen soll
        else {
            Node * newNode = new Node;
            newNode->Data = obj;
            newNode->ID = 0;
            newNode->Next = HeadStart;
            HeadStart = newNode;
            Size++;
            RepairIDAt(HeadStart);
        }
    }

    void AddEmptyNodes(uint16_t size) {
        uint16_t zahler = Size + size;
        Node * nodeRepairAt;

        if (size == 0) return;

        if (Size == 0) {
            Node * node;
            node = new Node;
            node->ID = 0;
            HeadStart = node;
            HeadEnd = node;
            nodeRepairAt = node;
            Size++;
        }

        while(Size < zahler) {
            Node * node;
            node = new Node;
            node->ID = Size;
            HeadEnd->Next = node;
            HeadEnd = node;
            Size++;
        }
        RepairIDAt(nodeRepairAt);
    }

    void RemoveAt(uint16_t num) {
        Node * oneLowerAtNum;
        if (Size > 0 && num > 0) /* if High then 0 */ {
            oneLowerAtNum = HeadStart;
            while (true) /* Node is Found */ {
                if (oneLowerAtNum->ID +1 == num) {
                    if (Size != num +1 ) {
                        oneLowerAtNum->Next = oneLowerAtNum->Next->Next;
                        Size--;
                        uint16_t zahler = oneLowerAtNum->ID +1;
                        uint16_t zahlerEnd = Size;
                        Node * nodeHead = oneLowerAtNum->Next;

                        while(zahler != zahlerEnd) {
                            nodeHead->ID = zahler;
                            nodeHead = nodeHead->Next;
                            zahler++;
                        }
                        return;
                    }
                    oneLowerAtNum->Next = NULL;
                    return;
                }
                else /* next Node */ {
                    oneLowerAtNum = oneLowerAtNum->Next;
                    return;
                }
            }
        }
        else /* if Remove Node 0*/ {
            if (Size == 1) {
                HeadStart = NULL;
                HeadEnd = NULL;
                Size = 0;
            } else {
                HeadStart = HeadStart->Next;
                HeadStart->ID = 0;
                Size--;
                RepairIDAt(HeadStart);
            }
        }
    }

    void Push(uint16_t from, uint16_t to) {
        Node * _from = GetNode(from);
        Node * _to = GetNode(to);

        T * _fromT = _from->Data;
        T * _toT = _to->Data;

        _from->Data = _toT;
        _to->Data = _fromT;
    }

    void OverwriteElement(uint16_t index, T * obj) {
        GetNode(index)->Data = obj;
    }

    void Clear() {
        Size = 0;
        HeadStart = NULL;
        HeadEnd = NULL;
    }

    void PassList(void (*func)(T& data)) {
        uint16_t zahler = 0;
        Node * node = HeadStart;
        while (zahler != Size) {
            func(*node->Data);
            node = node->Next;
            zahler++;
        }
    }

    void PassList(T(*func)(T& data)) {
        uint16_t zahler = 0;
        Node * node = HeadStart;
        while (zahler != Size) {
            T data = func(*node->Data);
            node->Data = &data;
            node = node->Next;
            zahler++;
        }
    }

    template<class U>
    void PassListInput(U input,void(*func)(T& data, U input)) {
        uint16_t zahler = 0;
        Node * node = HeadStart;
        while (zahler != Size) {
            func(*node->Data, input);
            node = node->Next;
            zahler++;
        }
    }

    template<class U>
    void PassListInput(U * input,void(*func)(T& data, U * input)) {
        uint16_t zahler = 0;
        Node * node = HeadStart;
        while (zahler != Size) {
            func(*node->Data, input);
            node = node->Next;
            zahler++;
        }
    }

    template<class U>
    void PassListInput(U * input,T(*func)(T& data, U * input)) {
        uint16_t zahler = 0;
        Node * node = HeadStart;
        while (zahler != Size) {
            T data = func(*node->Data, input);
            node->Data = &data;
            node = node->Next;
            zahler++;
        }
    }
};




#endif //EQ_SLACKLIST_H

































//------------------
