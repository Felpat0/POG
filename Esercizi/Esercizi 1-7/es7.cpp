#include<iostream>

class Stage{
    public:
    int id;
    int difficulty;
    Stage *next;

    Stage(int i, int d):id(i), difficulty(d), next(nullptr){}
};

using namespace std;

int main(){
    Stage *firstElement = new Stage(-1, 0);
    Stage *iter;
    char choice;

    while(true){
        cout<<"\nWhat do you want to do?\na) Add a new stage\nr) Remove a stage\nv) View stages\nq) Quit\n";
        cin>>choice;

        switch (choice) {
        case 'a': {
            int tempId;
            int tempDifficulty;
            cout<<"Insert id and difficulty: ";
            cin>>tempId>>tempDifficulty;
            iter = firstElement;
            cout<<endl;
            while(iter->next != nullptr){
                iter = iter->next;
            }
            iter->next = new Stage(tempId, tempDifficulty);
            break;
        }
        case 'r': {
            int idToRemove;
            cout<<"\nWhat stage do you want to remove? id = ";
            cin>>idToRemove;
            if(firstElement->id == idToRemove){
                Stage *temp = firstElement;
                firstElement = temp->next;
                delete temp;
            }else{
                iter = firstElement;
                while(iter->next->id != idToRemove){
                    iter = iter->next;
                }
                Stage *temp = iter->next;
                iter->next = temp->next;
                delete temp;
            }
            break;
        }
        case 'v': {
            iter = firstElement;
            while(iter->next != nullptr){
                cout<<iter->id<<" "<<iter->difficulty<<" -->";
                iter = iter->next;
            }
            cout<<iter->id<<" "<<iter->difficulty;
            break;
        }
        case 'q': {
            //Free memory
            iter = firstElement;
            while(iter != nullptr){
                Stage *temp = iter;
                iter = temp->next;
                cout<<"\nStage with id "<<temp->id<<" deleted";
                delete temp;
            }
            break;
        }
        default:
            cout<<"\nInsert a letter from the list";
        }

        if(choice == 'q')
            break;
    }
}