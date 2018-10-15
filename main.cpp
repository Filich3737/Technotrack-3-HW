//динамический стек?
//а структура лежит на стеке или в куче?
//метод clear?
//метод stack_ok?
//правильно ли я реализовал DUMP?


#include <iostream>
#include <cmath>
#include <cassert>
#include <cstring>


using namespace std;

struct Stack
{
    unsigned count = 0;
    unsigned capacity = 0;
    double *data = nullptr;
};

int StackCtor(Stack *inpSt)
{
    assert(inpSt != nullptr);
    inpSt->count = 0;
    inpSt->capacity = 1;
    void *tmp = calloc(1, sizeof(double));
    assert(tmp != nullptr);

    inpSt->data = static_cast<double*>(tmp);
    return 1;
}

Stack StackNew()
{
    Stack outSt;
    StackCtor(&outSt);
    return outSt;
}

int StackDtor(Stack *inpSt)
{
    free(inpSt->data);
    return 1;
}

int Push_back(Stack *inpSt, double val){
    assert(inpSt != nullptr);
    assert(std::isfinite(val));
    if (inpSt->count == inpSt->capacity)
    {
        double *tmp = static_cast<double*>(calloc(inpSt->capacity * 2, sizeof(double)));
        assert(tmp != nullptr);

        void *res = memcpy(tmp, inpSt->data, sizeof(double) * inpSt->capacity);
        assert(res != nullptr);

        inpSt->data = tmp;
        inpSt->capacity *= 2;
    }
    inpSt->data[inpSt->count] = val;
    inpSt->count++;
    return 1;
}

double Pop_back(Stack *inpSt)
{
    if (inpSt->count == 0)
        return static_cast<double>(NAN);
    else if (inpSt->count - 1 == inpSt->capacity/2)
    {
        inpSt->capacity /= 2;
        inpSt->count--;
        double x = inpSt->data[inpSt->count];

        double *tmp = static_cast<double*>(calloc(inpSt->capacity, sizeof(double)));
        assert(tmp != nullptr);

        void *res = memcpy(tmp, inpSt->data, sizeof(double) * inpSt->capacity);
        assert(res != nullptr);

        inpSt->data = tmp;
        return x;
    }
    else
    {
        inpSt->count--;
        return inpSt->data[inpSt->count];
    }
}

void Stack_dump(Stack *inpSt)
{
    printf("capasity= %d, count= %d\n", inpSt->capacity, inpSt->count);
    for (unsigned i = 0; i < inpSt->count; i++)
        printf("%.2lf ", inpSt->data[i]);
    for (unsigned i = inpSt->count; i < inpSt->capacity; i++)
        printf("\x1b[31m%.2lf\x1b[0m ", inpSt->data[i]);
    puts("\n");
}

unsigned StackSize(Stack *inpSt)
{
    assert(inpSt != nullptr);
    return inpSt->count;
}

unsigned StackCapacity(Stack *inpSt)
{
    assert(inpSt != nullptr);
    return inpSt->capacity;
}

double StackTop(Stack *inpSt)
{
    assert(inpSt != nullptr);
    return inpSt->data[inpSt->count-1];
}

int main()
{
    Stack st = StackNew();
    Push_back(&st, 100);
    Push_back(&st, 101);
    Push_back(&st, 102);
    Push_back(&st, 103);
    Push_back(&st, 104);

    Stack_dump(&st);
    cout << StackSize(&st) << endl;
    cout << StackCapacity(&st) << endl;
    cout << StackTop(&st) << endl;
    Stack_dump(&st);
}
