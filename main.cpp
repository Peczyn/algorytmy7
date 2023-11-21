#include <iostream>
#include <vector>
#include <chrono>
#include <random>
using namespace std;
using namespace std::chrono;

int randINT() {
    // Making rng static ensures that it stays the same
    // Between different invocations of the function
    static default_random_engine rng;

    uniform_real_distribution<int> dist(1, 10000);
    return dist(rng);
}

void swap(vector<int> &array, int x, int y);
void printVec(vector<int> vec);
vector<int> BubbleSort(vector<int> array);
vector<int> InsertionSort(vector<int> array);
vector<int> SelectionSort(vector<int> array);
vector<int> CombSort(vector<int> array);
vector<int> ShellSort(vector<int> array);
void testTimes();



int main() {

    vector<int> unsorted;
//    for(int k=0; k<1000; k++)
//    {
//        unsorted.push_back(randINT());
//    }
//    vector<int> BubbleSorted = BubbleSort(unsorted);
//    vector<int> InsertionSorted = InsertionSort(unsorted);
//    vector<int> SelectionSorted = SelectionSort(unsorted);
//    vector<int> CombSorted = CombSort(unsorted);
//    vector<int> ShellSorted = ShellSort(unsorted);
//
//    printVec(unsorted);
//    printVec(BubbleSorted);
//    printVec(InsertionSorted);
//    printVec(SelectionSorted);
//    printVec(CombSorted);
//    printVec(ShellSorted);
    testTimes();
    return 0;
}



void swap(vector<int> &array, int x, int y)
{
    int temp = array[x];
    array[x]=array[y];
    array[y]=temp;
}
void printVec(vector<int> vec)
{
    for(auto &a : vec)
    {
        cout << a << '\t';
    }
    cout << endl;
}
vector<int> BubbleSort(vector<int> array)
{
    int min;
    int temp;
    for(int i=0; i<array.size(); i++)
    {
        min=i;
        for(int j=i; j<array.size(); j++)
        {
            if(array[min]>array[j])
            {
                min=j;
            }
        }
        swap(array,i,min);
    }
    return array;
}
vector<int> InsertionSort(vector<int> array)
{
    if(array[1]<array[0])
    {
        int temp = array[0];
        array[0]=array[1];
        array[1]=temp;
    }

    int a;
    for(int i=1; i<array.size(); i++)
    {
        a=i;
        while(array[a]<array[a-1] && a>0)
        {
            swap(array,a,a-1);
            a--;
        }
    }
    return array;

}
vector<int> SelectionSort(vector<int> array)
{
    int min;
    for(int i=0; i<array.size(); i++)   //zaczynam od calej tablicy
    {                                   //w drugiej iteracji od drugiego element, w trzeciej od trzeciego itd
        min = i;
        for(int j=i; j<array.size(); j++) //szukam najmniejszego elementu w nieposortowanym obszarze
        {
            if(array[min]>array[j])
            {
                min=j;
            }
        }
        swap(array,min,i); //najmniejszy element w obszarze wstawiam w pierwsze nieposortowane miejsce w tablicy
    }
    return array;
}
vector<int> CombSort(vector<int> array)
{
    int combgap = 11;
    while(combgap>array.size())
    {
        combgap/=1.3;
    }

    while(combgap>0)
    {
        for(int i=0; i<array.size()-combgap; i++)
        {
            if(array[i]>array[i+combgap])
            {
                swap(array,i,i+combgap);
            }
        }
        combgap/=1.3;
    }
    return array;

}
vector<int> ShellSort(vector<int> array) {
    int gap = array.size()/2;
    int k;
    while(gap>0)
    {
        for(int i=gap; i<array.size(); i++)
        {
            k=i;
            while(k-gap>=0)
            {
                if(array[k]<array[k-gap])
                {
                    swap(array,k,k-gap);
                }
                k-=gap;
            }
        }
        gap/=2;
    }

    return array;
}
void testTimes()
{
//    vector<int> czasBubble;
//    vector<int> czasInsert;
//    vector<int> czasSelect;
//    vector<int> czasComb;
//    vector<int> czasShell;
    vector<int> unsorted;
    int czas1,czas2,czas3,czas4,czas5;
    for(int i=10; i<100000; i*=10)
    {
//        for(int j=0; j<5; j++)
//        {
            for(int k=0; k<i; k++)
            {
                unsorted.push_back(randINT());
            }
            auto start = high_resolution_clock::now();
            BubbleSort(unsorted);
            auto stop = high_resolution_clock::now();
            czas1=((duration_cast<microseconds>(stop - start)).count());

            auto start1 = high_resolution_clock::now();
            InsertionSort(unsorted);
            auto stop1 = high_resolution_clock::now();
            czas2=((duration_cast<microseconds>(stop1 - start1)).count());

            auto start2 = high_resolution_clock::now();
            SelectionSort(unsorted);
            auto stop2 = high_resolution_clock::now();
            czas3=((duration_cast<microseconds>(stop2 - start2)).count());

            auto start3 = high_resolution_clock::now();
            CombSort(unsorted);
            auto stop3 = high_resolution_clock::now();
            czas4=((duration_cast<microseconds>(stop3 - start3)).count());

            auto start4 = high_resolution_clock::now();
            ShellSort(unsorted);
            auto stop4 = high_resolution_clock::now();
            czas5=((duration_cast<microseconds>(stop4 - start4)).count());

            cout << "Bubble: " << czas1 << "\tInsert: " << czas2 << "\tSelect: "<< czas3 << "\tComb: "<< czas4 <<"\tShell: "<< czas5 << endl;
//        }


    }
}
