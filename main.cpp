#include <iostream>
#include <vector>
#include <chrono>
#include <random>
using namespace std;
using namespace std::chrono;

int randINT() {
    // Making rng static ensures that it stays the same
    // Between different invocations of the function
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,1000);
    return dist6(rng);
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

//    vector<int> unsorted;
//    for(int k=38; k>0; k--)
//    {
//        unsorted.push_back(k);
//    }
//
//
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
    int index = 0;
    while(index==0) {
        index=1;
        for (int i = 0; i < array.size()-1; i++) {
            if (array[i] > array[i + 1]) {
                swap(array, i, i + 1);
                index=0;
            }
        }
    }
    return array;
}
vector<int> InsertionSort(vector<int> array)
{
    int a,key;
    for(int i=1; i<array.size(); i++)
    {
        a=i-1;
        key=array[i];
        while(key<array[a] && a>=0)
        {
//            swap(array,a,a+1);
            array[a+1]=array[a];
            a--;
        }
        array[a+1]=key;
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
        swap(array[i],array[min]);
//        swap(array,min,i); //najmniejszy element w obszarze wstawiam w pierwsze nieposortowane miejsce w tablicy
    }
    return array;
}
vector<int> CombSort(vector<int> array)
{
    int combgap = (array.size()*10)/13;
    bool swapped = true;


    while(combgap!=1 || swapped )
    {
        swapped = false;
        for(int i=0; i < array.size()-combgap; i++){
            if(array[i]>array[i+combgap])
            {
                swap(array,i,i+combgap);
                swapped = true;
            }
        }
        combgap= combgap*10/13;
        if(combgap==0){
            combgap=1;
        }
    }
    return array;

}
vector<int> ShellSort(vector<int> array) {
    int k;
    for(int gap=array.size()/2; gap>0; gap/=2)
    {
        for(int i=gap; i<array.size(); i++)
        {
            k=i;
            bool noswap = true;
            while(k-gap>=0 && noswap)
            {
                noswap = false;
                if(array[k]<array[k-gap])
                {
                    swap(array,k,k-gap);
                    noswap = true;
                }
                k-=gap;
            }
        }
    }

    return array;
}


void testTimes()
{
    vector<int> unsorted;
    int czas;
    int i = 10000;
    int liczbapomiarow = 20;
    long int sumaShell = 0;
    long int sumaBubble = 0;
    long int sumaInsert = 0;
    long int sumaSelect = 0;
    long int sumaComb = 0;
    cout << "Liczba elementów: " << i << endl;


        for(int j=0; j<liczbapomiarow; j++)
        {
            for(int k=0; k<i; k++)
            {
                unsorted.push_back(randINT());
            }
            auto start = high_resolution_clock::now();
            BubbleSort(unsorted);
            auto stop = high_resolution_clock::now();
            czas=((duration_cast<microseconds >(stop - start)).count());
            cout << "BubbleSort: "<< czas;
            sumaBubble+=czas;

            start = high_resolution_clock::now();
            InsertionSort(unsorted);
            stop = high_resolution_clock::now();
            czas=((duration_cast<microseconds >(stop - start)).count());
            cout << "\tInsertionSort: "<< czas;
            sumaInsert+=czas;

            start = high_resolution_clock::now();
            SelectionSort(unsorted);
            stop = high_resolution_clock::now();
            czas=((duration_cast<microseconds >(stop - start)).count());
            cout << "\tSelectionSort: "<< czas;
            sumaSelect+=czas;

            start = high_resolution_clock::now();
            CombSort(unsorted);
            stop = high_resolution_clock::now();
            czas=((duration_cast<microseconds >(stop - start)).count());
            cout << "\tCombSort: "<< czas;
            sumaComb+=czas;

            start = high_resolution_clock::now();
            ShellSort(unsorted);
            stop = high_resolution_clock::now();
            czas=((duration_cast<microseconds >(stop - start)).count());
            cout << "\tShellSort: "<< czas << endl;
            sumaShell+=czas;
            unsorted.clear();
        }

        cout << "Srednie czasy: \nBubbleSort: " << sumaBubble/liczbapomiarow;
        cout << "\tInsertionSort: "<< sumaInsert/liczbapomiarow;
        cout << "\tSelectionSort: "<< sumaSelect/liczbapomiarow;
        cout << "\tCombSort: "<< sumaComb/liczbapomiarow;
        cout << "\tShellSort: "<< sumaShell/liczbapomiarow << endl;
    }

