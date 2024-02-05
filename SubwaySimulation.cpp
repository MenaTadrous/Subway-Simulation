/***********************************************************************
Matr.-Nr:                     3144604
Nachname/Surname:             Tadrous
Vorname/Given name:           Mena
Uni-Email:                    mena.tadrous@stud.uni-due.de
Studiengang/Course of studis: computer engineering
***********************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
struct station {
    string name;
    int mintonext;
    station* next;
    station* prev;
};
struct train {
    string metronam;
    int minlefttonext;
    bool forward;
    station* approachednext;
};

station* generate_metro_line(int linenum, int stationum) {
    station* st = new station;
    station* head;
    station* tail;
    st->next = nullptr;
    st->prev = nullptr;
    head = st;
    tail = st;

    for (int i = 1; i <= stationum; i++) {
        station* st = new station;
        st->name = "line " + to_string(linenum) + " station " + to_string(i);
        if (i == stationum) {
            st->mintonext = 0;
        }
        else {
            st->mintonext = (rand() % 5 + 1);
        }
        st->next = nullptr;
        st->prev = tail;
        tail->next = st;
        tail = st;
    }

    return head;
}
void output(station* s) {
    station* m = s;
    while (m->next != nullptr) {
        m = m->next;
        cout << m->name;
        if (m->mintonext == 0) {
            cout << ": end station\n";
        }
        else {
            cout << ":time to next:" << m->mintonext<<" min" << endl;
        }
    }
}
void output_line(station* a) {
    output(a);

}
void init(train* mtrain, string nam, station* p) {
    mtrain->metronam = nam;
    mtrain->approachednext = p;
    mtrain->approachednext = mtrain->approachednext->next;
    mtrain->forward = true;
    mtrain->minlefttonext = 0;
}
void outputt(train* m) {
    cout << m->metronam << ":";
    
    if (m->minlefttonext == 0) {
        cout << "stop at " << m->approachednext->name<<endl;
    }
    else {
        cout << m->minlefttonext << " minutes to " << m->approachednext->name;
        if (!m->forward) {
            cout << " (on way back)";
        }
        cout << endl;
    }
}
void output_all_trains(int simulationmin, train* a[], int size) {
    cout << "time simulation:" << simulationmin << "min" << endl;

    for (int i = 0; i < size; i++) {
        outputt(a[i]);
    }
}
int main()
{
    
    int time = 0;
    station* arr[2];
    station* real[2];
    train* t[2];
    for (int i = 0; i < 2; i++) {
        arr[i] = NULL;
        t[i] = NULL;
        real[i] = NULL;
    }
    for (int i = 0; i < 2; i++) {
        arr[i] = new station;
        t[i] = new train;
        real[i] = new station;
    }
    for (int i = 0; i < 2; i++) {
        cout << "input number of stations of line " << i + 1 << ":\n";
        int k;
        cin >> k;
            arr[i] = generate_metro_line(i + 1, k);
            real[i] = arr[i];
            
            
            init(t[i], "train" + to_string(i + 1), arr[i]);
        
            
        
    }
    char c;
    bool fill = true;
    do {
        cout << "e end\nl line output\nt train output\n1 simulate 1 minute\n";

        cin >> c;
        switch (c) {
        case 'e':break;
        case 'l':cout << "which line";
            int n;
            cin >> n;
            
                output(arr[n-1]);
             break;
        case 't':output_all_trains(time,t,2); break;
        case '1':
            time += 1;
            
            for (int i = 0; i < 2; i++) {
                
                if ((t[i]->approachednext->next == NULL   )&& t[i]->minlefttonext == 0) {
                    if ((t[i]->approachednext->next == NULL)) {
                        
                        arr[i] = arr[i]->next;
                    }
                    
                    
                        t[i]->forward = false;
                    
                    
                }
                if (arr[i]->prev == real[i] && !t[i]->forward) {
                    t[i]->forward = true;
                    arr[i] = arr[i]->prev;
                    
                }
                if(t[i]->minlefttonext == 0 && t[i]->forward==false) {
                     t[i]->approachednext = t[i]->approachednext->prev;
                    arr[i] = arr[i]->prev;
                    fill = false;
                    

                }
                if ((t[i]->minlefttonext == 0) && t[i]->forward) {
                    t[i]->approachednext = t[i]->approachednext->next;
                    arr[i] = arr[i]->next;
                    fill = false;

                }
                
                if (!fill) {
                    t[i]->minlefttonext = arr[i]->mintonext+1;
                }
                t[i]->minlefttonext -= 1;
                fill = true;
            }
            output_all_trains(time, t, 2);
            break;
        }
    } while (c != 'e');
}

