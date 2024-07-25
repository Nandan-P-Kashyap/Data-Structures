#include <iostream>

using namespace std;
class snode{
    public:
    int row;
    int col;
    int val;
    int rindex;

};

class sparse{
    public:
    snode *sm;
    int r,c,terms,ri;
    int currterms;
    public:
    sparse(int row, int col ,int n){
        r = row;
        c = col;
        terms = n;
        sm = new snode[terms];  //creating an array 
        currterms = 0;
        ri = 0;
        


    }
    sparse & store(int i,int j,const int & v){
        // try{
        //     if(i<1 || i> row || j<1 || j> col) throw exception(currterms);
        //     if(currterms == terms) throw exception(currterms);
        // }catch(exception & e){
        //     cout<<"THE EXECUTION IS TERMINATED"<<e.num<<endl;
        // }
        sm[currterms].row = i;
        sm[currterms].col = j;
        sm[currterms].val = v;
        currterms++;
        
        return *this;



    }
    void merge(snode* arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        snode* L = new snode[n1];
        snode* R = new snode[n2];

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i].rindex <= R[j].rindex) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }

        delete[] L;
        delete[] R;
    }

    void mergeSort(snode* arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);

            merge(arr, left, mid, right);
        }
    }

    sparse &sort() {
        for (int i = 0; i < currterms; i++) {
            sm[i].rindex = (sm[i].row - 1) * c + (sm[i].col - 1);
        }
        mergeSort(sm, 0, currterms - 1);
        return *this;
    }

    sparse & add(sparse & sn, int curr2) {
    int i = 0;
    int j = 0;

    while (i < currterms && j < curr2) {
        if (sm[i].rindex == sn.sm[j].rindex) {
            sm[i].val += sn.sm[j].val;
            ++i;
            ++j;
        } else if (sm[i].rindex < sn.sm[j].rindex) {
            ++i;
        } else if (sm[i].rindex > sn.sm[j].rindex) {
            // Insert sn.sm[j] into sm at position i
            insert(sn.sm[j], i);
            ++i;
            ++j;
        }
    }

    // If there are remaining elements in S2, add them to S1
    while (j < curr2) {   //if elements in S2<S1
        insert(sn.sm[j], i);
        ++i;
        ++j;
    }

    return *this;
}

    sparse & insert(snode & s, int is) {  //only used to insert the values of sn(snode) to sm in the beginning or at the middle
        for (int i = currterms; i > is; i--) {
            sm[i] = sm[i - 1];
        }
        //cout<<"value of s is"<<s.val<<endl;
        sm[is] = s;
        //cout<<"value of sm["<<is<<"] is"<<sm[is].val<<endl;
        ++currterms;
        return *this;
    }

        
    

    void display(){
        for(int i=0 ; i<currterms ; i++){
            cout<<sm[i].row<<" "<<sm[i].col<<" "<<sm[i].val<<endl;
        }
    }
    
};

int main(){
    sparse S1(13,13,4);
    sparse S2(13,13,4);
     S1.store(1, 1, 3)  
       .store(2, 2, 5) 
       .store(3, 3, 7)
       .store(14,1,11);

     S2.store(3,3,1)
       .store(13,13,2)
       .store(1,2,78)
       .store(14,1,100);

 
    S1.sort();
    cout<<"S1 after sort"<<endl;
    S1.display();
    cout<<endl;
    S2.sort();
    cout<<"S2 after sort"<<endl;
    S2.display();
    S1.add(S2 , 4);
    cout<<"after the addition"<<endl;
    S1.display();
    return 0;
}


