# SlackList for Arduino Or C++

### Include the library
```c++
#include <SlackList.h>
```

### Creating a list
```c++
// A list of integer

SlackList<int> list;
// or
SlackListUInt16<int> list_type1;
// or
SlackListUInt32<int> list_type2;
```

### Get size
```c++
int size = x.GetSize():
```

### A list of 'Vec3'
```c++
class Vec3 {
public:
    int x;
    int y;
    int z;
};

SlackList<Vec3> list;
```

### Adding elements
```c++
SlackList<int> list;
list.Add(1);

// Put Pointer
SlackList<int> list;
int * ptr = new int(5);
list.AddPtr(ptr);
```

### Get elements
```c++
int element = list.Get(0);

// Get Pointer
int * elementPtr = list.GetPtr(0);
```

### set element in a specific position
```c++
int index = 1;
int obj = 200;
list.AddAt(index, obj);

// As Ptr
int index = 1;
int * ptr = new int(200);
list.AddAt(index, &obj);
```

### Put Empty Obj
```c++
int size = 20;
list.AddEmptyNodes(size);
```

### Remove element
```c++
int position = 2;
list.RemoveAt(position);
```


### Move element
```c++
int from = 2;
int to = 1;
list.RemoveAt(from, to);
```

### Overwrite element
```c++
int index 2;
int obj = 2000;
list.OverwriteElement(index , obj);

// ptr
int index1 = 1;
int * objPtr = new int(5);
list.OverwriteElementPtr(index1, objPtr);
```

### Clear list
```c++
list.Clear();
```

### Put compare function 
```c++

SlackList<int> list;

for (int i = 1; i < 5; i++) { list.Add(i); } // add 4 elements

list.PassList([](int &fromList) {
    fromList += fromList;
});

list.PassList([](int &fromList) {
    std::cout << fromList << "\n"; // Print list
});

/* Print
 * 2
 * 4
 * 6
 * 8
 */
```

### Put compare function with input 
```c++
// Version 1
SlackList<int> list;

for (int i = 1; i < 5; i++) { list.Add(i); }

int num = 10;
list.PassListInput<int>(num, [](int &fromList, int num) {
    fromList += num;
});

list.PassList([](int &fromList) {
    std::cout << fromList << "\n"; // Print all
});

/* Print
 * 11
 * 12
 * 13
 * 14
 */
```

### Get all elements as array
```c++
SlackList<int> list;

for (int i = 1; i < 5; i++) { list.Add(i); }

SlackList<int>::SizeArray array = list.GetAll();
for (int i = 0; i < array.Size; i++) {
    std::cout << array.Array[i] << "\n"; // Print all
}

/* Print
 * 1
 * 2
 * 3
 * 4
 */
```

### Get all pointers as array 
```c++
SlackList<int> list;

for (int i = 1; i < 5; i++) { list.Add(i); }

SlackList<int>::SizeArrayPtr * array = list.GetAllPtr();
for (int i = 0; i < array->Size; i++) {
    int * x = array->Array[i];
    *x += 4;
}

list.PassList([](int &in) {
    std::cout << in << "\n"; // Print all
});

/* Print 
 * 5 
 * 6
 * 7
 * 8
 */
```



