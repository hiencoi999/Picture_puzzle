#include<iostream>
using namespace std;
int** GetMatx(int m, int n){
    int ** matrix = new int*[m];
    for(int i=0;i<m;i++){
        *(matrix+i) = new int[n];
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cin >> *(*(matrix+i)+j);
        }
    }
    return matrix;
}

void SolvePro(int ** matrix, int m, int n){
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cout << (*(*(matrix+i)+j) < 0 ? 0 : *(*(matrix+i)+j)) << " ";
        }
        cout << endl;
    }
}

int main(){
    int m,n;
    cin >> m >> n;
    int **Newmat = GetMatx(m,n);
    SolvePro(Newmat,m,n);
    return 0;
}
