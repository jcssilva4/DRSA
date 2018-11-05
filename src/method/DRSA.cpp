#include "DRSA.h"

DRSA::DRSA(int nObj, int nCrt, int* dirs, int nCls, float** f)
{
    this->nObj = nObj;
    this->nCriteria = nCrt;
    this->nClasses = nCls;
    for(int q = 0; q < this->nCriteria; q++){
        this->prefDir.push_back(dirs[q]);
    }
    /// create universe of objects
    for (int i = 0; i < this->nObj; i++){
        string name = "Object" + to_string(i+1);
        this->Universe.push_back(new Obj(name, f[i], this->nCriteria));
        this->Clt[(this->Universe[i])->get_Class()].push_back(this->Universe[i]);//allocate this obj to a class
    }

    /// get granules of knowledge
    vector<Obj*> remainingUniverse = this->Universe; //use this to reduce algorithm complexity (allows simultaneous update of Pdominating and Pdominated sets of two objects X and Y)
    for (vector<Obj*>::iterator currentObj = this->Universe.begin(); currentObj != this->Universe.end(); ++currentObj){ //loop over all objects of the universe
        (*currentObj)->update_GranulesOfKnowledge(remainingUniverse, this->prefDir);
        remainingUniverse.erase(remainingUniverse.begin()); //erase the first element to reduce algorithm complexity
    }

    /// get approximations of unions of classes
    for (int t = 1; t <= this->nClasses; t++){ //higher values of t give the most preferable classes (1 - is the worst class/ n>1 - is the best class)
        cout << "\nget approximations for class " << t;
        //get approximations
        cout << "\n\nP_lower_(Cl" << t << ">=)\n{\n";
        for (vector<Obj*>::iterator currentObj = this->Universe.begin(); currentObj != this->Universe.end(); ++currentObj){ //loop over all objects of the universe
            // get P-Lower approximation of Clt>=
            //(*currentObj)->show_PdominatingSet();
            if(checkApproxMembership(t, true, true, (*currentObj))){
                this->PLaprx_Clt_up[t].push_back(*currentObj);
                cout << (*currentObj)->get_Name() << endl;
            }
        }
        cout << "}\n";
    }

    ///check rough sets existence (Boundaries)

    /*
    ///Print DRSA processed data
    cout << "\n*****************************************\n";
    cout << "number of objects: " << this->nObj << endl;
    cout << "number of criteria: " << this->nCriteria << " [";
    for (int q = 0; q < this->nCriteria; q++){
        if(this->prefDir[q] > 0) cout << "max";
        else cout << "min";
        if(q < this->nCriteria-1)
            cout << ",";
    }
    cout << "]\n";
    cout << "number of classes: " << this->nCriteria;
    cout << "\n*****************************************\n";
    */
    ///Print class partitions
    for (int t = 1; t <= this->nClasses; t++){ //if s>t, s is preferable to t
        cout << "\nClass " << t << " Contains:\n";
        for (vector<Obj*>::iterator currentObj = this->Clt[t].begin(); currentObj != this->Clt[t].end(); ++currentObj){
            cout << endl << (*currentObj)->get_Name() << " /";
        }
    }
}

//check if an object x is contained in an approximation of union of classes
bool DRSA::checkApproxMembership(int t, bool isLowerAprx, bool isUpwardUnion, Obj* thisObj){
    bool contained = true;
    if(isLowerAprx){
        if(isUpwardUnion){ //check if Dp+ is contained in Clt
            vector<Obj*> PdomSet = thisObj->get_PdominatingSet();
            for (vector<Obj*>::iterator currentObj = PdomSet.begin(); currentObj != PdomSet.end(); ++currentObj){
                //cout << "\nelement: " << (*currentObj)->get_Class();
                if((*currentObj)->get_Class()<t){
                    contained = false;
                    //cout << endl << "Name: " << (*currentObj)->get_Name() << " class is " << (*currentObj)->get_Class() << " < " << t;
                    break;
                }
                else{

                }
            }
        }
    }
    return contained;
}

DRSA::~DRSA()
{
    cout << "\nDeleting DRSA vars...";
    //dtor
}
