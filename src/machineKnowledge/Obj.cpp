#include "Obj.h"

Obj::Obj(string n, float* f, int nCriteria)
{
    this->name = n;
    for(int q = 0; q < nCriteria; q++){this->g.push_back(f[q]);}
    this->clss = f[nCriteria];
    /*
    /// print name + gi + class
    cout << "\nobjname: " << this->name;
    cout << "\nCriteria Eval: [";
    int q = 0;
    for (vector<float>::iterator it = this->g.begin(); it != this->g.end(); ++it){
        cout << *it;
        if(q < nCriteria-1) cout << ", ";
        ++q;
    }
    cout << "]";
    cout << "\tCl = " << this->clss;
    */
}

void Obj::update_GranulesOfKnowledge(vector<Obj*> remainingUniverse, vector<int> prefDir){
    for(vector<Obj*>::iterator obj_ = remainingUniverse.begin(); obj_ != remainingUniverse.end(); ++obj_){
        //if(*obj_!=this){ //compare different objects only...
            //cout << endl << this->name << " Dp " << (*obj_)->get_Name() << " ?";
            //compare values of the two objects in each criterion (XDpY if XSqY for all p belonging to P (Sq is reflexive[XSqX] and transitive))
        vector<float>::iterator thisobj_g = this->g.begin();
        vector<float>::iterator otherobj_g = (*obj_)->g.begin();
        vector<int>::iterator prefdir = prefDir.begin();
        vector<bool> XSqY;
        while(thisobj_g != this->g.end()){
            if((*thisobj_g)*(*prefdir) < (*otherobj_g)*(*prefdir)) XSqY.push_back(false);
            else  XSqY.push_back(true); // X outranks Y
            thisobj_g++;
            otherobj_g++;
            prefdir++;
        }
        /// set Pdominating and Pdominated Sets simultaneously in this object and obj_
        int countFalse = 0, countTrue = 0;
        for(vector<bool>::iterator thisSqY = XSqY.begin();  thisSqY != XSqY.end(); ++ thisSqY){
            if(*(thisSqY)) countTrue++;
            else countFalse++;
        }
        if(countTrue == this->g.size()){ /// if this object outranks obj_, then:
            this->update_PdominatedSet(*obj_);
            (*obj_)->update_PdominatingSet(this);
            //cout << endl << this->name << " outranks " << (*obj_)->get_Name();
        }
        else if(countFalse == this->g.size()){ /// if obj_ outranks this object, then:
            this->update_PdominatingSet(*obj_);
            (*obj_)->update_PdominatedSet(this);
            //cout << endl << (*obj_)->get_Name() << " outranks " << this->name;
        }
        //}
    }
}

void Obj::update_PdominatingSet(Obj* element){
    this->PdominatingSet.push_back(element);
}

void Obj::update_PdominatedSet(Obj* element){
    this->PdominatedSet.push_back(element);
}

int Obj::get_Class(){
    return this->clss;
}

void Obj::show_PdominatingSet(){
    int countElems = 0;
    cout << this->get_Name() << "\tP-dominating set: \n ";
    cout << "{\n";
    for (vector<Obj*>::iterator currentObj = this->PdominatingSet.begin(); currentObj != this->PdominatingSet.end(); ++currentObj){
        ++countElems;
        cout << "elem" << countElems << ": " << (*currentObj)->get_Name() << "\t(Cl: " << (*currentObj)->get_Class() << ")" << endl;
    }
    cout << "}\n";
}

vector<Obj*> Obj::get_PdominatingSet(){
    return this->PdominatingSet;
}

string Obj::get_Name(){ return this->name;}

Obj::~Obj()
{
    //dtor
}
